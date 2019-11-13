// Logic.cpp

#define _CRT_SECURE_NO_WARNINGS
#include "Logic.h"
#include "ws_client_orig.h"

#include <iostream>

#include <locale>
#include <codecvt>
#include <string>


using namespace std;

#include <AtlBase.h>
#include <atlconv.h>

wstring utf8toUtf16(string str) {
	//string s = "some string";
	CA2W ca2w(str.c_str());
	wstring w = ca2w;
	printf("%s = %ls", str.c_str(), w.c_str());
	return w;
}

/*
#include <stdexcept>
#include <vector>
#include <windows.h>

using std::runtime_error;
using std::string;
using std::vector;
using std::wstring;

wstring utf8toUtf16(const string & str)
{
	if (str.empty())
		return wstring();

	size_t charsNeeded = ::MultiByteToWideChar(CP_UTF8, 0,
		str.data(), (int)str.size(), NULL, 0);
	if (charsNeeded == 0)
		throw runtime_error("Failed converting UTF-8 string to UTF-16");

	vector<wchar_t> buffer(charsNeeded);
	int charsConverted = ::MultiByteToWideChar(CP_UTF8, 0,
		str.data(), (int)str.size(), &buffer[0], buffer.size());
	if (charsConverted == 0)
		throw runtime_error("Failed converting UTF-8 string to UTF-16");

	return wstring(&buffer[0], charsConverted);
}


wstring string_to_wstring(string str)
{
	wstring a;
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::string narrow = converter.to_bytes(a);
	std::wstring wide = converter.from_bytes(str);
	return wide;
}

std::wstring s2ws(const std::string& str)
{
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.from_bytes(str);
}
*/

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
	
	//wstring wide = string_to_wstring(two);
	//wstring wide = s2ws(two);
	wstring wide = utf8toUtf16(two);
	
	wstring res = wide + L" conn id: " + to_wstring(id);
	return res;
}
