// Logic.cpp

#define _CRT_SECURE_NO_WARNINGS
#include "Logic.h"
#include "ws_client_orig.h"

#include <iostream>

#include <locale>
#include <codecvt>
#include <string>


using namespace std;

wstring string_to_wstring(string str)
{
	wstring a;
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::string narrow = converter.to_bytes(a);
	std::wstring wide = converter.from_bytes(str);
	return wide;
}

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


	string two = metadata.get()->get_status();
	wstring a;
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::string narrow = converter.to_bytes(a);
	std::wstring wide = converter.from_bytes(two);
	
	wstring res = wide + L" conn id: " + to_wstring(id);
	return res;
}
