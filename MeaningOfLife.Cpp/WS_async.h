#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

using tcp = boost::asio::ip::tcp;               // from <boost/asio/ip/tcp.hpp>
namespace websocket = boost::beast::websocket;  // from <boost/beast/websocket.hpp>
using namespace std;

namespace MeaningOfLife
{
	namespace Cpp
	{

		// Sends a WebSocket message and prints the response
		class __declspec(dllexport) WS_async : public std::enable_shared_from_this<WS_async>
		{

			tcp::resolver resolver_;
			websocket::stream<tcp::socket> ws_;
			boost::beast::multi_buffer buffer_;
			std::string host_;
			std::string text_;

		public:
			// Resolver and socket require an io_context
			explicit
				WS_async(boost::asio::io_context& ioc)
				: resolver_(ioc)
				, ws_(ioc) {}

			// Start the asynchronous operation
			void
				run(
					char const* host,
					char const* port,
					char const* text);

			void on_resolve(
					boost::system::error_code ec,
					tcp::resolver::results_type results);

			void on_connect(boost::system::error_code ec);

			void on_handshake(boost::system::error_code ec);

			void on_write(
					boost::system::error_code ec,
					std::size_t bytes_transferred);

			void on_read(
					boost::system::error_code ec,
					std::size_t bytes_transferred);

			void on_close(boost::system::error_code ec);
		};
	}
}



//------------------------------------------------------------------------------
/*
int main(int argc, char** argv)
{
	// Check command line arguments.
	if (argc != 4)
	{
		std::cerr <<
			"Usage: websocket-client-async <host> <port> <text>\n" <<
			"Example:\n" <<
			"    websocket-client-async echo.websocket.org 80 \"Hello, world!\"\n";
		return EXIT_FAILURE;
	}
	auto const host = argv[1];
	auto const port = argv[2];
	auto const text = argv[3];

	// The io_context is required for all I/O
	boost::asio::io_context ioc;

	// Launch the asynchronous operation
	std::make_shared<WS_async>(ioc)->run(host, port, text);

	// Run the I/O service. The call will return when
	// the socket is closed.
	ioc.run();

	return EXIT_SUCCESS;
}
*/