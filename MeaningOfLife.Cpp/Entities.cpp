
#pragma once

#include "Entities.h"

using namespace std;

MeaningOfLife::Cpp::Entities::AddUser::AddUser() {}
MeaningOfLife::Cpp::Entities::AddUser::AddUser(const char* sender, const char* user,
	const char* channel, const char* fullname, bool success, const char* type) 
{
	this->sender = sender;
	this->user = user;
	this->channel = channel;
	this->fullname = fullname;
	this->success = success;
	this->type = type;
}

MeaningOfLife::Cpp::Entities::User::User() {}
MeaningOfLife::Cpp::Entities::User::User(const char* login, const char* type) {
	this->login = login;
	this->type = type;
}

MeaningOfLife::Cpp::Entities::GetChannelUsers::GetChannelUsers() {}
MeaningOfLife::Cpp::Entities::GetChannelUsers::GetChannelUsers(const char* sender, const char* channel,
	vector<User> users, const char* type) 
{
	this->sender = sender;
	this->channel = channel;
	this->users = users;
	this->type = type;
}

MeaningOfLife::Cpp::Entities::GetOnlineUsers::GetOnlineUsers() {}
MeaningOfLife::Cpp::Entities::GetOnlineUsers::GetOnlineUsers(const char* sender, vector<const char*> users, const char* type)
{
	this->sender = sender;
	this->users = users;
	this->type = type;
}


MeaningOfLife::Cpp::Entities::NewChannelRequest::NewChannelRequest() {}
MeaningOfLife::Cpp::Entities::NewChannelRequest::NewChannelRequest(const char* name, const char* fullname,
	const char* admin, const char* type) 
{
	this->name = name;
	this->fullname = fullname;
	this->admin = admin;
	this->type = type;
}

MeaningOfLife::Cpp::Entities::NewChannelResponse::NewChannelResponse() {}
MeaningOfLife::Cpp::Entities::NewChannelResponse::NewChannelResponse(const char* name, const char* fullname,
	const char* admin, const char* type, bool success) 
{
	this->name = name;
	this->fullname = fullname;
	this->admin = admin;
	this->type = type;
	this->success = success;
}


MeaningOfLife::Cpp::Entities::GetChannelMessagesReq::GetChannelMessagesReq() {}
MeaningOfLife::Cpp::Entities::GetChannelMessagesReq::GetChannelMessagesReq(const char* from, const char* channel,
	long time, const char* type) 
{
	this->from = from;
	this->channel = channel;
	this->time = time;
	this->type = type;
}

MeaningOfLife::Cpp::Entities::ChannelRequest::ChannelRequest() {}
MeaningOfLife::Cpp::Entities::ChannelRequest::ChannelRequest(const char* type, const char* name, const char* from)
{
	this->from = from;
	this->name = name;
	this->from = from;
}

MeaningOfLife::Cpp::Entities::RegRequest::RegRequest() {}
MeaningOfLife::Cpp::Entities::RegRequest::RegRequest(const char* type, const char* user, const char* email, const char* password)
{
	this->type = type;
	this->user = user;
	this->email = email;
	this->password = password;
}

MeaningOfLife::Cpp::Entities::RegResponse::RegResponse() {}
MeaningOfLife::Cpp::Entities::RegResponse::RegResponse(const char* type, bool success) 
{
	this->type = type;
	this->success = success;
}

MeaningOfLife::Cpp::Entities::AuthResponse::AuthResponse() {}
MeaningOfLife::Cpp::Entities::AuthResponse::AuthResponse(const char* type, bool success, vector<const char*> online)
{
	this->type = type;
	this->success = success;
	this->online = online;
}
		
MeaningOfLife::Cpp::Entities::AuthRequest::AuthRequest() {}
MeaningOfLife::Cpp::Entities::AuthRequest::AuthRequest(const char* type, const char* user, const char* password)
{
	this->type = type;
	this->user = user;
	this->password = password;
}

MeaningOfLife::Cpp::Entities::MessageResponse::MessageResponse() {}
MeaningOfLife::Cpp::Entities::MessageResponse::MessageResponse(const char* type, const char* message,
	const char* from, long time, const char* channel)
{
	this->type = type;
	this->message = message;
	this->from = from;
	this->time = time;
	this->time = time;
	this->channel = channel;
}
