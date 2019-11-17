#include "Logic.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <fstream>

#include "ws_client_orig.h"
#include "CastCoreUtils.h"
#include "WS_Core.h"

using namespace std;

void MeaningOfLife::Cpp::Logic::wsCoreLoop() {
	string host = "ws://echo.websocket.org";
	double timeoutS = 1;

	try {
		cout << "Thread start" << endl;
		WS_Core core(host);
		clock_t this_time = clock();
		clock_t last_time = this_time;
		while (true) {
			this_time = clock();
			if ((timeoutS * CLOCKS_PER_SEC < (double)(this_time - last_time))) {
				cout << "." << endl;
				last_time = clock();
				
				ifstream inFile;
				inFile.open("input.txt");
				if (!inFile) {
					continue;
				}
				
				string str;
				while (std::getline(inFile, str)) {
					cout << "read: " << endl;
					cout << str << endl;
					// TODO: here write command call
				}
				inFile.close();
				if (remove("input.txt") != 0) {
					cout << "Error deleting file" << endl;
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