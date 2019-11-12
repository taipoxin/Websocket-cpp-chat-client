// Logic.cpp

#define _CRT_SECURE_NO_WARNINGS
#include "Logic.h"

#include "ws_client_orig.h"
#include "boost/lexical_cast.hpp"

#include <iostream>


using namespace std;

wchar_t* str_to_wchar(std::string str) {
	wstring w = wstring(str.begin(), str.end());
	return &w[0];
}

const char* i2cc(int i, char* buf = NULL, int szbuf = 0);
const char* i2cc(int i, char* buf, int szbuf)
{
	static char s_buf[32] = { '\0' };
	char* p = NULL;
	int neg = 0;
	if (szbuf > 0 && buf != NULL)
		p = buf + szbuf - 1;
	else
		p = s_buf + sizeof(buf) - 1;
	*p = '\0';
	if (i == 0) return "0";
	if (i < 0)
	{
		neg = 1;
		i = -i;
	}
	while (i > 0)
	{
		*(--p) = '0' + (char)(i % 10);
		i /= 10;
	}
	if (neg)
		*(--p) = '-';
	return p;

}

const char* concat_chars(const char* one, const char* two)
{
	int bufferSize = strlen(one) + strlen(two) + 1;
	char* concatString = new char[bufferSize];
	strcpy(concatString, one);
	strcat(concatString, two);
	return concatString;
}

const char* MeaningOfLife::Cpp::Logic::Get(const char* text) const
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
	//const char* two = metadata.get()->get_status()
	//const char* two = static_cast<const char*> (metadata.get()->get_status().c_str());;
	//cout << two << endl;

	const char* one = "айди: ";
	const char* two = i2cc(id);
	const char* result = concat_chars(one, two);
	

	cout << result << endl;

	return result;
}
