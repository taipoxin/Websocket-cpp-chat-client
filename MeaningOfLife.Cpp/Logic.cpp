// Logic.cpp
#include "Logic.h"

#include "Poco/MD5Engine.h"
#include "Poco/DigestStream.h"
#include "ws_client_orig.h"
#include "boost/lexical_cast.hpp"

//#include "websocketpp/client.hpp" 
//#include "websocketpp/config/asio_no_tls_client.hpp"

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

const char* MeaningOfLife::Cpp::Logic::Get(const char* text) const
{
	//client cl;
	std::cout << text << endl;

	Poco::MD5Engine md5;
	Poco::DigestOutputStream ds(md5);
	ds << "abcdefghijklmnopqrstuvwxyz";
	ds.close();
	std::cout << Poco::DigestEngine::digestToHex(md5.digest()) << std::endl;


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
	
	std::cout << id << std::endl;
	const char* id_ch = (std::to_string(id)).c_str();
	
	
	std::string res = "айди: " + to_string(id);
	std::cout << res.c_str() << std::endl;
	std::cout << res << std::endl;

	const char* one = "айди: ";
	const char* two = i2cc(id);
	// calculate the required buffer size (also accounting for the null terminator):
	int bufferSize = strlen(one) + strlen(two) + 1;
	// allocate enough memory for the concatenated string:
	char* concatString = new char[bufferSize];
	// copy strings one and two over to the new buffer:
	strcpy(concatString, one);
	strcat(concatString, two);
	// delete buffer:
	//delete[] concatString;

	cout << concatString << endl;

	const char* b = res.c_str();
	//return res.c_str();
	const char* a = "мдаа пиздец";
	return concatString;


	//std::string buf(res);
	//buf.append(id_ch);
	
	//std::cout << buf.c_str() << std::endl;
	//std::cout << res.c_str() << std::endl;

	//return L"aaa";
	//wchar_t* r = str_to_wchar(res);
	//cout << r << endl;
	//return "дарова блять";
	//return res.to; 
}
