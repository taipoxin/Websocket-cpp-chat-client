#pragma once
#include <string>
#include <boost/any.hpp>
#include "Entities.h"

using namespace std;

namespace MeaningOfLife
{
	namespace Cpp
	{
		class __declspec(dllexport) Dispatcher
		{
		public:
			Dispatcher();
			bool onAuthorize;

			bool onMessage;
			Entities::MessageResponse messageObject;

			bool onRegister;

			bool onGetChannel;
			vector<boost::any> chList;
			vector<int> counts;

			bool onNewChannel;
			Entities::NewChannelResponse newChannels;

			bool onGetChannelMessages;
			string ch;
			vector<boost::any> chMessages;

			bool onGetOnlineUsers;
			Entities::GetOnlineUsers onlineUsersObj;

			bool onAddUser;
			Entities::AddUser addUserObj;
			int addUserSolution;

			bool onGetChannelUsers;
			Entities::GetChannelUsers getChannelUsers;

		};
	}
}
