// Logic.cpp

#include <iostream>
#include "Logic.h"
#include "ws_client_orig.h"
#include "CastCoreUtils.h"


using namespace std;


std::wstring MeaningOfLife::Cpp::Logic::Get(const char* text) const
{
	std::cout << text << endl;

	websocket_endpoint endpoint;
	std::string s = "ws://echo.websocket.org";
	std::cout << "a" << std::endl;

	int id = -10;
	id = endpoint.connect(s);
	for (int j = 0; j < 10000000; j++) {
		std::cout << "";
	}
	connection_metadata::ptr metadata = endpoint.get_metadata(id);
	if (metadata) {
		std::cout << *metadata << std::endl;
	}

	string two = "Русские вперед " + metadata.get()->get_status();
	wstring wide = string_to_wstring(two);
	
	wstring res = wide + L" conn id: " + to_wstring(id);
	return res;
}
