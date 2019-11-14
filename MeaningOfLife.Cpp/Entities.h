// Logic.h
#pragma once

#include <string>
#include <vector>

using namespace std;

namespace MeaningOfLife
{	
	namespace Cpp
	{

	class __declspec(dllexport) Entities
	{
	public:
      class MessageEntity {
        public:
          const int Id() const { return _Id; } 
          void Id(const int id) { _Id = id; } 

          string from() const { return _from; } 
          void from(string from) { _from = from; } 

          string time() const { return _time; }
          void time(string time) { _time = time; } 
        private:
          int _Id;
          string _from;
          string _message;
          string _time;
      };

      class AddUser {
        public:
          AddUser();
          AddUser(string sender, string user, 
            string channel, string fullname, bool success, string type);
          
          string sender;
          string user;
          string channel;
          string fullname;
          bool success;
          string type;
      };


      class User {
        public:
          User();
          User(string login, string type);
          
          string login;
          string type;
      };


      class GetChannelUsers {
        public:
          GetChannelUsers();
          GetChannelUsers(string sender, string channel,
            vector<User> users, string type);
          
          string sender;
          string channel;
		  vector<User> users;
		  // get_channel_users
          string type;
      };

	  // universal (for req(w/o users) and resp)
	  class GetOnlineUsers
	  {
	  public:
		  GetOnlineUsers();
		  GetOnlineUsers(string sender, vector<string> users, string type);

		  string sender;
		  vector<string> users;
		  // "get_online_users"
		  string type;
	  };


	  // only for checking response type
	  class CommonResponse
	  {
	  public:
		  string type;
	  };


	  class NewChannelRequest
	  {
	  public:
		  NewChannelRequest();
		  NewChannelRequest(string name, string fullname, 
			  string admin, string type);

		  string name;
		  string fullname;
		  string admin;
		  string type;
	  };

	  class NewChannelResponse
	  {
	  public:
		  NewChannelResponse();
		  NewChannelResponse(string name, string fullname, 
			  string admin, string type, bool success);
		  string name;
		  string fullname;
		  string admin;
		  string type;
		  bool success;
	  };

	  class GetChannelMessagesReq
	  {
		  GetChannelMessagesReq();

		  GetChannelMessagesReq(string from, string channel, 
			  long time, string type);

		  string from;
		  string channel;
		  long time;
		  // "get_channel_messages"
		  string type;

	  };


	  class ChannelRequest
	  {
	  public:
		  ChannelRequest();

		  ChannelRequest(string type, string name, string from);

		  string type;
		  // if name == '*' return all channels
		  string name;
		  string from;
	  };

	  class RegRequest
	  {
	  public:
		  RegRequest();

		  RegRequest(string type, string user, string email, string password);

		  string type;
		  string user;
		  string email;
		  string password;
	  };

	  class RegResponse
	  {
	  public:
		  RegResponse();

		  RegResponse(string type, bool success);

		  string type;
		  bool success;
	  };

	  class AuthResponse
	  {
	  public:
		  AuthResponse();

		  AuthResponse(string type, bool success, vector<string> online);

		  string type;
		  bool success;
		  vector<string> online;
	  };

	  class AuthRequest
	  {
	  public:
		  AuthRequest();
		  AuthRequest(string type, string user, string password);

		  string type;
		  string user;
		  string password;
	  };

	  class MessageResponse
	  {
	  public:
		  MessageResponse();

		  MessageResponse(string type, string message, 
			  string from, long time, string channel);

		  string from;
		  string message;
		  string channel;
		  // ms from 1970
		  long time;
		  string type;

	  };

	};
	}
}
