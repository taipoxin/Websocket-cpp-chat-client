#include <iostream>
#include <chrono>
#include <ctime>   
#include <fstream>
#include "MessageHandler.h"
#include "str_switch.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;
using namespace MeaningOfLife::Cpp;

MessageHandler::MessageHandler(string file)
{
	this->file = file;
}

string MessageHandler::castType(string type) {
	if (type == "new_channel") {
		return "new_ch";
	}
	if (type == "get_channel") {
		return "get_ch";
	}
	if (type == "new_channel") {
		return "new_ch";
	}
	if (type == "get_channel_messages") {
		return "get_ch_m";
	}
	if (type == "get_online_users") {
		return "gt_on_us";
	}
	if (type == "get_channel_users") {
		return "gt_ch_us";
	}
	return type;
}

// method for all processing json from server
void MessageHandler::handle(string message) {
	try {
		auto j = json::parse(message);
		cout << "handle: new message: " << message << endl;
		if (j.find("type") != j.end()) {
			string type = j["type"];
			type = castType(type);
			SWITCH(type) {
				CASE("register") :
					break;
				CASE("authorize") :
					cout << "type is authorize" << endl;
					break;
				CASE("message") :
					break;
				CASE("add_user") :
					break;
				CASE("new_ch") :
					break;
				CASE("get_ch") :
					break;
				CASE("get_ch_m") :
					break;
				CASE("gt_on_us") :
					break;
				CASE("gt_ch_us") :
					break;
			}
		}
		else {
			cout << "json hasn't type param" << endl;
		}
		ofstream writer;
		writer.open(this->file);
		writer << message;	
		writer.flush();
	}
	catch (std::exception const& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		cout << e.what();
	}

}


