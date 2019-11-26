#pragma once

#include <string>
#include "Entities.h"
#include "Config.h"
#include "FileLogger.h"
#include "WsController.h"
#include <boost/any.hpp>

using namespace std;

namespace MeaningOfLife
{
	namespace Cpp
	{
		class __declspec(dllexport) Utils
		{
		private:
			//   = new FileLogger(Config::logFileName)
			static FileLogger l;
		public:
			// return true if successfully sended

			// object -> boost
			static bool sendRequest(boost::any const& obj, WsController c);

			static void sendAddUserRequest(string user, string channel, string fullname, WsController c);
			static void sendGetOnlineUsersRequest(WsController c);

			static void sendGetChannelUsersRequest(string channel, WsController c);




			/// <summary>
			/// we retrieve long time from server and view it in message grids
			/// </summary>
			static string longToDateTime(long time);

			/// <summary>
			/// current date and time
			/// </summary>
			static string getCurrentDatenTime();
			/// <summary>
			/// current time
			/// </summary>
			static string getCurrentTime();


			/// <summary>
			/// return center position 
			/// </summary>
			/// <param name="resolution">is the full length of pixels</param>
			/// <param name="actual">size of app in pixels</param>
			static double getCenter(double resolution, double actual);

			// dynamic -> boost:any
			static Entities::MessageResponse dynamicToMessageResponse(boost::any const& obj);

			static Entities::NewChannelResponse dynamicToNewChannelResponse(boost::any const& obj);

		};
	}
}

