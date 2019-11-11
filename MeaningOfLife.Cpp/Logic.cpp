// Logic.cpp
#include "Logic.h"

#include "Poco/MD5Engine.h"
#include "Poco/DigestStream.h"
#include "ws_client_orig.h"

//#include "websocketpp/client.hpp" 
//#include "websocketpp/config/asio_no_tls_client.hpp"

#include <iostream>

const char* MeaningOfLife::Cpp::Logic::Get() const
{
	//client cl;
	Poco::MD5Engine md5;
	Poco::DigestOutputStream ds(md5);
	ds << "abcdefghijklmnopqrstuvwxyz";
	ds.close();
	std::cout << Poco::DigestEngine::digestToHex(md5.digest()) << std::endl;


	websocket_endpoint endpoint;
	std::string s = "ws://echo.websocket.org";
	std::cout << "a" << std::endl;

	int id = -10;
	
	//id = endpoint.connect(s);
	
	for (int j = 0; j < 10000000; j++) {
		std::cout << "";
	}
	/*
	connection_metadata::ptr metadata = endpoint.get_metadata(id);
	if (metadata) {
		std::cout << *metadata << std::endl;
	}
	*/
	std::cout << id << std::endl;
	std::string res = "id: " + id;
	
	return res.c_str(); // Really, what else did you expect?
	//return "kek"; // Really, what else did you expect?
}
