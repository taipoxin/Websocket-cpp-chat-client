#define _WIN32_WINNT 0x0600
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <chrono>
#include <ctime>   
#include <fstream>
#include <string>
#include "WebsocketCore.h"

using namespace std;
using namespace MeaningOfLife::Cpp;




WebsocketCore::WebsocketCore(string host, string port)
{
	this->host = host;
	this->port = port;
}

WebsocketCore::WebsocketCore()
{
}

void WebsocketCore::saveJSON(string json) {
	string file = "input.json";
	ofstream writer;
	//ofstream writer(this->file);
	writer.open(file, ios::app);
	writer << json;
}

// Sends a WebSocket message and prints the response
websocket::stream<tcp::socket>&  WebsocketCore::init()
{

	// The io_context is required for all I/O
	net::io_context ioc;
	// These objects perform our I/O
	tcp::resolver resolver{ ioc };
	websocket::stream<tcp::socket> ws{ ioc };
	// Look up the domain name
	auto const results = resolver.resolve(this->host, this->port);
	// Make the connection on the IP address we get from a lookup
	net::connect(ws.next_layer(), results.begin(), results.end());

	ws.handshake_ex(this->host, "/", [](websocket::request_type& req)
	{
		req.set(http::field::user_agent,
			std::string(BOOST_BEAST_VERSION_STRING) +
			" websocket-client-coro");
	});
	return ws;
}



// Sends a WebSocket message and prints the response
int  WebsocketCore::init(string host, string port, string text)
{
	try
	{
		// The io_context is required for all I/O
		net::io_context ioc;
		// These objects perform our I/O
		tcp::resolver resolver{ ioc };
		websocket::stream<tcp::socket> ws{ ioc };
		// Look up the domain name
		auto const results = resolver.resolve(host, port);
		// Make the connection on the IP address we get from a lookup
		net::connect(ws.next_layer(), results.begin(), results.end());

		ws.handshake_ex(host, "/", [](websocket::request_type& req)
		{
			req.set(http::field::user_agent,
				std::string(BOOST_BEAST_VERSION_STRING) +
				" websocket-client-coro");
		});

		// Send the message
		ws.binary(true);
		ws.write(boost::asio::buffer(std::string(text)));

		// This buffer will hold the incoming message
		beast::multi_buffer buffer;

		// Read a message into our buffer
		ws.read(buffer);

		// Close the WebSocket connection
		ws.close(websocket::close_code::normal);

		// If we get here then the connection is closed gracefully
		// The make_printable() function helps print a ConstBufferSequence
		std::cout << boost::beast::buffers(buffer.data()) << std::endl;
	}
	catch (std::exception const& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}


