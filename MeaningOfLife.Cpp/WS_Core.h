
#pragma once

#include <iostream>
#include "ws_client_orig.h"
#include "CastCoreUtils.h"
#include <stdio.h>
#include <time.h>
#include <string>
#include <vector>

namespace MeaningOfLife
{
	namespace Cpp
	{
		using namespace std;
		
		class __declspec(dllexport) WS_Core
		{
		public:
			WS_Core();
			WS_Core(string host);
			int id;
			websocket_endpoint endpoint;
			string host;
			string logTitle = "WS_Core: ";
			int connectWS(double timeoutS);
			void send(string message);
			void reconnect();
			void close();
			bool isAlive();
			std::vector<std::string> getMessages();
		};
	}
}