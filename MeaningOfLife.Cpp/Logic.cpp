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

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

using namespace std;


wstring MeaningOfLife::Cpp::Logic::Get(string text) const
{
	cout << text << endl;
	
	WebsocketCore core = WebsocketCore("echo.websocket.org", "80");

	core.init("echo.websocket.org", "80", "Привет из Беларуси");

	int id = -10;
	string two = "Дароу";

	wstring wide = string_to_wstring(two);
	
	wstring res = wide + L" conn id: " + to_wstring(id);
	return res;
}
