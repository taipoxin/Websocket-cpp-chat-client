#include "WS_async.h"
#include <fstream>
#include <cstdio>
#include <boost/thread.hpp>
#include <thread>

using namespace MeaningOfLife::Cpp;


// Report a failure
void
fail(boost::system::error_code ec, char const* what)
{
	std::cerr << what << ": " << ec.message() << "\n";
}

// Start the asynchronous operation
void
	WS_async::run(
		char const* host,
		char const* port,
		char const* text)
{
	// Save these for later
	host_ = host;
	text_ = text;

	// Look up the domain name
	resolver_.async_resolve(
		host,
		port,
		std::bind(
			&WS_async::on_resolve,
			shared_from_this(),
			std::placeholders::_1,
			std::placeholders::_2));
}

void
	WS_async::on_resolve(
		boost::system::error_code ec,
		tcp::resolver::results_type results)
{
	if (ec)
		return fail(ec, "resolve");

	// Make the connection on the IP address we get from a lookup
	boost::asio::async_connect(
		ws_.next_layer(),
		results.begin(),
		results.end(),
		std::bind(
			&WS_async::on_connect,
			shared_from_this(),
			std::placeholders::_1));
}

void
	WS_async::on_connect(boost::system::error_code ec)
{
	if (ec)
		return fail(ec, "connect");

	// Perform the websocket handshake
	ws_.async_handshake(host_, "/",
		std::bind(
			&WS_async::on_handshake,
			shared_from_this(),
			std::placeholders::_1));
}

void a(websocket::stream<tcp::socket>* ws_, string text, std::shared_ptr<MeaningOfLife::Cpp::WS_async> pt) {
	cout << "новый тред" << endl;
	cout << text << endl;
	
	ws_->async_write(
		boost::asio::buffer(text),
		std::bind(
			&WS_async::on_write,
			pt,
			std::placeholders::_1,
			std::placeholders::_2));
	cout << "Вызвано" << endl;
}

void
	WS_async::on_handshake(boost::system::error_code ec)
{
	if (ec)
		return fail(ec, "handshake");

	// Send the message
	ws_.binary(true);
	double timeoutS = 1;
	clock_t this_time = clock();
	clock_t last_time = this_time;
	while (true) {
		this_time = clock();
		if ((timeoutS * CLOCKS_PER_SEC < (double)(this_time - last_time))) {
			cout << "re" << endl;
			last_time = clock();
			ifstream inFile;
			inFile.open("input.txt");
			if (!inFile) {
				continue;
			}
			string sum;
			string x;
			while (inFile >> x) {
				sum = sum + x;
			}
			cout << "read: " << endl;
			cout << sum << endl;
			inFile.close();
			if (remove("input.txt") != 0) {
				cout << "Error deleting file" <<endl;
			}
			//sum = "дарова ебать";
			//std::thread thread_object(a, &ws_, sum, shared_from_this());
			
			ws_.async_write(
				boost::asio::buffer(sum),
				std::bind(
					&WS_async::on_write,
					shared_from_this(),
					std::placeholders::_1,
					std::placeholders::_2));
			break;
				
			//thread_object.join();
		}
	}
}

void
	WS_async::on_write(
		boost::system::error_code ec,
		std::size_t bytes_transferred)
{
	cout << "on_write: " << endl;
	cout << bytes_transferred << endl;
	boost::ignore_unused(bytes_transferred);
	if (ec)
		return fail(ec, "write");

	// Read a message into our buffer
	ws_.async_read(
		buffer_,
		std::bind(
			&WS_async::on_read,
			shared_from_this(),
			std::placeholders::_1,
			std::placeholders::_2));
}

void
	WS_async::on_read(
		boost::system::error_code ec,
		std::size_t bytes_transferred)
{
	boost::ignore_unused(bytes_transferred);

	if (ec)
		return fail(ec, "read");

	// Close the WebSocket connection
	ws_.async_close(websocket::close_code::normal,
		std::bind(
			&WS_async::on_close,
			shared_from_this(),
			std::placeholders::_1));
}

void
	WS_async::on_close(boost::system::error_code ec)
{
	if (ec)
		return fail(ec, "close");

	// If we get here then the connection is closed gracefully

	// The buffers() function helps print a ConstBufferSequence
	std::cout << "Message from ws_server: " << boost::beast::buffers(buffer_.data()) << std::endl;
}

/*
//------------------------------------------------------------------------------

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