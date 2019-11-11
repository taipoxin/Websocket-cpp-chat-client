// Logic.cpp
#include "Logic.h"

#include "Poco/MD5Engine.h"
#include "Poco/DigestStream.h"
#include "ws_client_orig.h"

//#include "websocketpp/client.hpp" 
//#include "websocketpp/config/asio_no_tls_client.hpp"

#include <iostream>

//typedef websocketpp::client<websocketpp::config::asio_client> client;

const char* MeaningOfLife::Cpp::Logic::Get() const
{
	//client cl;
	Poco::MD5Engine md5;
	Poco::DigestOutputStream ds(md5);
	ds << "abcdefghijklmnopqrstuvwxyz";
	ds.close();
	std::cout << Poco::DigestEngine::digestToHex(md5.digest()) << std::endl;


	websocket_endpoint endpoint;
	std::string s = "wss://echo.websocket.org";
	std::cout << "a" << std::endl;
	int id = endpoint.connect(s);

	
	//return id; // Really, what else did you expect?
	return "kek"; // Really, what else did you expect?
}
