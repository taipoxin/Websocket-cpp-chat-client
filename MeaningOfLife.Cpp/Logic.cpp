
#include <iostream>
#include "Logic.h"
#include "ws_client_orig.h"
#include "CastCoreUtils.h"
#include <stdio.h>
#include <time.h>
#include "WS_Core.h"

using namespace std;

int connectWS(websocket_endpoint &endpoint, string s, double timeoutS) {
	int id = -10;
	clock_t this_time = clock();
	clock_t last_time = this_time;
	id = endpoint.connect(s);
	connection_metadata::ptr metadata = endpoint.get_metadata(id);

	while ((metadata.get()->get_status() != "Open") || (timeoutS * CLOCKS_PER_SEC > (double)(this_time - last_time))) {
		this_time = clock();
	}
	if (timeoutS * CLOCKS_PER_SEC < (double)(this_time - last_time)) {
		cout << "Connection Timeout" << endl;
	}
	return id;
}


wstring MeaningOfLife::Cpp::Logic::Get(string text) const
{
	cout << text << endl;

	websocket_endpoint endpoint;
	string s = "ws://echo.websocket.org";
	
	int id = -10;
	//wsAll(s);
	try {

		WS_Core core("ws://echo.websocket.org");
		cout << "here" << endl;
		core.send("Дарова");
		auto messages = core.getMessages();
		cout << messages.front() << endl;
	}
	catch (std::exception const& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return string_to_wstring(e.what());
	}
	/*
	string message = "Дарова";
	endpoint.send(id, message);

	connection_metadata::ptr metadata = endpoint.get_metadata(id);

	cout << *metadata << endl;

	*/
	//string two = "Привет ыыы " + metadata.get()->get_status();
	string two = "Привет ыыы ";
	wstring wide = string_to_wstring(two);

	wstring res = wide + L" conn id: " + to_wstring(id);
	return res;
}