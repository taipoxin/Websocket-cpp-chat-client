// Logic.cpp

#include <iostream>
#include "Logic.h"
#include "ws_client_orig.h"
#include "CastCoreUtils.h"


using namespace std;


wstring MeaningOfLife::Cpp::Logic::Get(string text) const
{
	cout << text << endl;

	websocket_endpoint endpoint;
	string s = "ws://echo.websocket.org";
	cout << "a" << endl;

	int id = -10;
	id = endpoint.connect(s);
	for (int j = 0; j < 10000000; j++) {
		cout << "";
	}
	connection_metadata::ptr metadata = endpoint.get_metadata(id);
	if (metadata) {
		cout << *metadata << endl;
	}

	string two = "Русские вперед " + metadata.get()->get_status();
	wstring wide = string_to_wstring(two);
	
	wstring res = wide + L" conn id: " + to_wstring(id);
	return res;
}
