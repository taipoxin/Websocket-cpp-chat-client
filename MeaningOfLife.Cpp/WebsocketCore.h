
#pragma once

#include <boost/any.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <string>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

using namespace std;

namespace MeaningOfLife
{
	namespace Cpp
	{
		class __declspec(dllexport) WebsocketCore
		{
		public:
			WebsocketCore();
			WebsocketCore(string host, string port);
			void saveJSON(string json);
			int init(string host, string port, string text);
			websocket::stream<tcp::socket>& init();
		private:
			//websocket::stream<tcp::socket>& ws;
			string host;
			string port;
		};
	}
}
