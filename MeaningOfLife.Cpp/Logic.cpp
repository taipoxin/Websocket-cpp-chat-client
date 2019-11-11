// Logic.cpp
#include "Logic.h"

#include "Poco/MD5Engine.h"
#include "Poco/DigestStream.h"

#include <websocketpp/client.hpp> 
#include <websocketpp/config/asio_no_tls_client.hpp>

#include <iostream>

typedef websocketpp::client<websocketpp::config::asio_client> client;

int MeaningOfLife::Cpp::Logic::Get() const
{
	client cl;
	Poco::MD5Engine md5;
	Poco::DigestOutputStream ds(md5);
	ds << "abcdefghijklmnopqrstuvwxyz";
	ds.close();
	std::cout << Poco::DigestEngine::digestToHex(md5.digest()) << std::endl;
	return 42; // Really, what else did you expect?
}
