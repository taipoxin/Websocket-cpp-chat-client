// Logic.cpp

#include <iostream>
#include "Logic.h"
#include "ws_client_orig.h"
#include "CastCoreUtils.h"
#include <stdio.h>
#include <time.h>

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
	cout << "a" << endl;

	int id = -10;
	id = connectWS(endpoint, s, 0.5);

	connection_metadata::ptr metadata = endpoint.get_metadata(id);
	if (metadata) {
		cout << *metadata << endl;
	}

	string message = "Привет из Беларуси";
	endpoint.send(id, message);

	
	cout << *metadata << endl;

	string two = "Русские вперед " + metadata.get()->get_status();
	wstring wide = string_to_wstring(two);
	
	wstring res = wide + L" conn id: " + to_wstring(id);
	return res;
}
