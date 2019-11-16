#define _WIN32_WINNT 0x0600
#define _CRT_SECURE_NO_WARNINGS

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <iostream>
#include <chrono>
#include <ctime>   
#include <fstream>
#include "WebsocketCore.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

using namespace std;
using namespace MeaningOfLife::Cpp;



WebsocketCore::WebsocketCore(string target)
{
	this->target = target;
}

void WebsocketCore::saveJSON(string json) {
	string file = "input.json";
	ofstream writer;
	//ofstream writer(this->file);
	writer.open(file, ios::app);
	writer << json;
}


