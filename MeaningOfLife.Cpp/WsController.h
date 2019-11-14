#pragma once


#include <string>
#include <vector>
#include "FileLogger.h"
#include "Entities.h"
#include <boost/any.hpp>

using namespace std;

// заглушки
struct WebSocket {};
struct Signin {};
struct Signup {};
struct MainWindow {};


namespace MeaningOfLife
{
	namespace Cpp
	{

		class __declspec(dllexport) WsController
		{
		private:
			// core low level ws client
			WebSocket ws;
			// change to static
			static FileLogger l;

			// links for view classes
			Signin signinWindow;
			Signup signupWindow;
			MainWindow mainWindow;

			void initWs();

			/// <summary>
			/// initialise webSocket client with all configured listeners
			/// </summary>
			/// <returns>ws object</returns>
			WebSocket initWebSocket();

			// dynamic -> string
			vector<Entities::MessageEntity> listDynamicToMessageEntities(vector<boost::any> ll);

			void tryToConnect(WebSocket ws);

		public:
			/// <summary>
			/// initialise webSocket in another thread
			/// </summary>
			WsController();

			WebSocket getWs();

			void setSigninWindow(Signin w);

			void setSignupWindow(Signup w);

			void setMainWindow(MainWindow w);

		};
	}
}
