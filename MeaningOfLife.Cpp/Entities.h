// Logic.h
#pragma once

#include <string>

namespace MeaningOfLife
{	
	namespace Cpp
	{
	using namespace std;
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

          const char* time() const { return _Id; } 
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
          GetChannelUsers(const char* sender, 
            vector<User> users,
            const char* channel,
            const char* channel,
            );
          
          const char* login;
          const char* type;
      };



		};
	}
}
