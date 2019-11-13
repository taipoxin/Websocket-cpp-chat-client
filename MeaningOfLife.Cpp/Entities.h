// Logic.h
#pragma once

#include <string>
#include<vector>

using namespace std;

namespace MeaningOfLife
{	
	namespace Cpp
	{
		// This is our native implementation
		// It's marked with __declspec(dllexport) 
		// to be visible from outside the DLL boundaries
		class __declspec(dllexport) Entities
		{

      class MessageEntity {
        public:
          const int Id() const { return _Id; } 
          void Id(const int id) { _Id = id; } 

          const char* from() const { return _from; } 
          void from(const char* from) { _from = from; } 

          const char* time() const { return _time; }
          void time(const char* time) { _time = time; } 
        private:
          int _Id;
          const char* _from;
          const char* _message;
          const char* _time;
      };

      class AddUser {
        public:
          AddUser();
          AddUser(const char* sender, const char* user, 
            const char* channel, const char* fullname, bool success, const char* type);
          
          const char* sender;
          const char* user;
          const char* channel;
          const char* fullname;
          bool success;
          const char* type;
      };


      class User {
        public:
          User();
          User(const char* login, const char* type);
          
          const char* login;
          const char* type;
      };


      class GetChannelUsers {
        public:
          GetChannelUsers();
          GetChannelUsers(const char* sender, const char* channel,
            vector<User> users, const char* type);
          
          const char* sender;
          const char* channel;
		  vector<User> users;
		  // get_channel_users
          const char* type;
      };

	  // universal (for req(w/o users) and resp)
	  class GetOnlineUsers
	  {
	  public:
		  GetOnlineUsers();
		  GetOnlineUsers(const char* sender, vector<const char*> users, const char* type);

		  const char* sender;
		  vector<const char*> users;
		  // "get_online_users"
		  const char* type;
	  };


	  // only for checking response type
	  class CommonResponse
	  {
	  public:
		  const char* type;
	  };


	  class NewChannelRequest
	  {
	  public:
		  NewChannelRequest();
		  NewChannelRequest(const char* name, const char* fullname, 
			  const char* admin, const char* type);

		  const char* name;
		  const char* fullname;
		  const char* admin;
		  const char* type;
	  };

	  class NewChannelResponse
	  {
	  public:
		  NewChannelResponse();
		  NewChannelResponse(const char* name, const char* fullname, 
			  const char* admin, const char* type, bool success);
		  const char* name;
		  const char* fullname;
		  const char* admin;
		  const char* type;
		  bool success;
	  };

	  class GetChannelMessagesReq
	  {
		  GetChannelMessagesReq();

		  GetChannelMessagesReq(const char* from, const char* channel, 
			  long time, const char* type);

		  const char* from;
		  const char* channel;
		  long time;
		  // "get_channel_messages"
		  const char* type;

	  };


	  class ChannelRequest
	  {
	  public:
		  ChannelRequest();

		  ChannelRequest(const char* type, const char* name, const char* from);

		  const char* type;
		  // if name == '*' return all channels
		  const char* name;
		  const char* from;
	  };

	  class RegRequest
	  {
	  public:
		  RegRequest();

		  RegRequest(const char* type, const char* user, const char* email, const char* password);

		  const char* type;
		  const char* user;
		  const char* email;
		  const char* password;
	  };

	  class RegResponse
	  {
	  public:
		  RegResponse();

		  RegResponse(const char* type, bool success);

		  const char* type;
		  bool success;
	  };

	  class AuthResponse
	  {
	  public:
		  AuthResponse();

		  AuthResponse(const char* type, bool success, vector<const char*> online);

		  const char* type;
		  bool success;
		  vector<const char*> online;
	  };

	  class AuthRequest
	  {
	  public:
		  AuthRequest();
		  AuthRequest(const char* type, const char* user, const char* password);

		  const char* type;
		  const char* user;
		  const char* password;
	  };

	  class MessageResponse
	  {
	  public:
		  MessageResponse();

		  MessageResponse(const char* type, const char* message, 
			  const char* from, long time, const char* channel);

		  const char* from;
		  const char* message;
		  const char* channel;
		  // ms from 1970
		  long time;
		  const char* type;

	  };

		};
	}
}
