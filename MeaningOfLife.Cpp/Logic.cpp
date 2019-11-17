#include "Logic.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <fstream>

#include "ws_client_orig.h"
#include "CastCoreUtils.h"
#include "WS_Core.h"
#include "str_switch.h"

using namespace std;

#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>


void processFile(string file, std::vector<std::string>* vector) {
	ifstream inFile;
	inFile.open(file);
	if (!inFile) {
		return;
	}
	string str;
	string s;
	while (std::getline(inFile, s)) {
		str = str + s;
	}
	cout << "read in processFile: " << endl;
	std::string command = str.substr(0, str.find(":::"));
	std::string body = str.substr(str.find(":::") + 3);
	cout << "command: " << command << endl;
	cout << "data: " << body << endl;
	vector->push_back(command);
	vector->push_back(body);
	cout << vector->at(0) << endl;
	cout << vector->at(1) << endl;
	inFile.close();
	if (remove(file.c_str()) != 0) {
		cout << "Error deleting file" << endl;
	}
	return;
}

void MeaningOfLife::Cpp::Logic::wsCoreLoop() {
	string host = "ws://echo.websocket.org";
	double repeat = 1;

	try {
		cout << "Thread start" << endl;
		WS_Core* core;
		core = nullptr;
		clock_t this_time = clock();
		clock_t last_time = this_time;
		std::vector<std::string> vec;
		while (true) {
			this_time = clock();
			if ((repeat * CLOCKS_PER_SEC < (double)(this_time - last_time))) {
				cout << "." << endl;
				last_time = clock();
				if (core == nullptr) {
					processFile("init.txt", &vec);
					if (vec.size() == 0)
						continue;
					string body = vec.at(1);
					core = new WS_Core(body);
					vec.clear();
				}
				processFile("input.txt", &vec);
				if (vec.size() == 0)
					continue;
				std::string command = vec.at(0);
				std::string body = vec.at(1);
				vec.clear();
				// TODO: here write command call
				SWITCH (command) {
					CASE("init") :
						core = new WS_Core(body);
					break;	
					CASE("connect") :
						core->connectWS(stod(body));
					break;
					CASE("send") :
						core->send(body);
					break;
					CASE("close") :
						core->close();
					break;
					CASE("isalive") :
						core->isAlive();
					break;
				}
			}
		}
	}
	catch (std::exception const& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		cout <<e.what();
	}
}

wstring MeaningOfLife::Cpp::Logic::Get(string text) const
{
	cout << text << endl;
	string host = "ws://echo.websocket.org";
	
	try {
		WS_Core core(host);
		core.send("Дарова");
		core.send("Hi there");
		core.send("Как дела?");

		waitSec(3);
		//core.close();
		vector<string> messages = core.getMessages();
		for (auto i = messages.begin(); i != messages.end(); ++i) {
			cout << *i << "; ";
		}
		cout << endl;
	}
	catch (std::exception const& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return string_to_wstring(e.what());
	}
	int id = -10;
	string two = "Привет ыыы ";
	wstring wide = string_to_wstring(two);

	wstring res = wide + L" conn id: " + to_wstring(id);
	return res;
}