#define _WIN32_WINNT 0x0600
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

#include <iostream>
#include "Logic.h"
#include "CastCoreUtils.h"
#include <stdio.h>
#include <time.h>
#include "WebsocketCore.h"
#include "WS_async_example.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

using namespace std;


wstring MeaningOfLife::Cpp::Logic::Get(string text) const
{
	cout << text << endl;

	try {

		// The io_context is required for all I/O
		boost::asio::io_context ioc;

		// Launch the asynchronous operation
		std::make_shared<session>(ioc)->run("echo.websocket.org", "80", "Дратути");

		// Run the I/O service. The call will return when
		// the socket is closed.
		ioc.run();
		/*
		WebsocketCore core;
		core.init("echo.websocket.org", "80", "Дратути");
		*/
		/*
		WebsocketCore core("echo.websocket.org", "80");
		websocket::stream<tcp::socket>& ws = core.init();
		ws.binary(true);
		try {
			ws.write(boost::asio::buffer(std::string("Драсте")));
		}
		catch (std::exception const& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
			ws.write(boost::asio::buffer(std::string("Драсте")));
		}
		// This buffer will hold the incoming message
		beast::multi_buffer buffer;
		// Read a message into our buffer
		ws.read(buffer);

		// Close the WebSocket connection
		ws.close(websocket::close_code::normal);

		// If we get here then the connection is closed gracefully
		// The make_printable() function helps print a ConstBufferSequence
		std::cout << boost::beast::buffers(buffer.data()) << std::endl;
	*/
	}
	catch (std::exception const& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return L"Error";
	}

	int id = -10;
	string two = "Дароу";

	wstring wide = string_to_wstring(two);
	
	wstring res = wide + L" conn id: " + to_wstring(id);
	return res;
}
