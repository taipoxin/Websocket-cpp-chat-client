
#pragma once

#include "Entities.h"

using namespace std;
using namespace MeaningOfLife::Cpp;

Entities::AddUser::AddUser() {}
Entities::AddUser::AddUser(string sender, string user,
	string channel, string fullname, bool success, string type) 
{
	this->sender = sender;
	this->user = user;
	this->channel = channel;
	this->fullname = fullname;
	this->success = success;
	this->type = type;
}

Entities::User::User() {}
Entities::User::User(string login, string type) {
	this->login = login;
	this->type = type;
}

Entities::GetChannelUsers::GetChannelUsers() {}
Entities::GetChannelUsers::GetChannelUsers(string sender, string channel,
	vector<User> users, string type) 
{
	this->sender = sender;
	this->channel = channel;
	this->users = users;
	this->type = type;
}

Entities::GetOnlineUsers::GetOnlineUsers() {}
Entities::GetOnlineUsers::GetOnlineUsers(string sender, vector<string> users, string type)
{
	this->sender = sender;
	this->users = users;
	this->type = type;
}


Entities::NewChannelRequest::NewChannelRequest() {}
Entities::NewChannelRequest::NewChannelRequest(string name, string fullname,
	string admin, string type) 
{
	this->name = name;
	this->fullname = fullname;
	this->admin = admin;
	this->type = type;
}

Entities::NewChannelResponse::NewChannelResponse() {}
Entities::NewChannelResponse::NewChannelResponse(string name, string fullname,
	string admin, string type, bool success) 
{
	this->name = name;
	this->fullname = fullname;
	this->admin = admin;
	this->type = type;
	this->success = success;
}


Entities::GetChannelMessagesReq::GetChannelMessagesReq() {}
Entities::GetChannelMessagesReq::GetChannelMessagesReq(string from, string channel,
	long time, string type) 
{
	this->from = from;
	this->channel = channel;
	this->time = time;
	this->type = type;
}

Entities::ChannelRequest::ChannelRequest() {}
Entities::ChannelRequest::ChannelRequest(string type, string name, string from)
{
	this->from = from;
	this->name = name;
	this->from = from;
}

Entities::RegRequest::RegRequest() {}
Entities::RegRequest::RegRequest(string type, string user, string email, string password)
{
	this->type = type;
	this->user = user;
	this->email = email;
	this->password = password;
}

Entities::RegResponse::RegResponse() {}
Entities::RegResponse::RegResponse(string type, bool success) 
{
	this->type = type;
	this->success = success;
}

Entities::AuthResponse::AuthResponse() {}
Entities::AuthResponse::AuthResponse(string type, bool success, vector<string> online)
{
	this->type = type;
	this->success = success;
	this->online = online;
}
		
Entities::AuthRequest::AuthRequest() {}
Entities::AuthRequest::AuthRequest(string type, string user, string password)
{
	this->type = type;
	this->user = user;
	this->password = password;
}

Entities::MessageResponse::MessageResponse() {}
Entities::MessageResponse::MessageResponse(string type, string message,
	string from, long time, string channel)
{
	this->type = type;
	this->message = message;
	this->from = from;
	this->time = time;
	this->time = time;
	this->channel = channel;
}
