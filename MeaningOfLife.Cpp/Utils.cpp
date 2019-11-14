
#include <iostream>
#include "Utils.h"
#include <typeinfo>
//#include <boost/any.hpp>

using namespace std;
using namespace MeaningOfLife::Cpp;


FileLogger Utils::l = FileLogger(Config::logFileName);

bool Utils::sendRequest(boost::any const& obj, WsController c) {
	WebSocket ws = c.getWs();
	if (typeid(ws).name() == "WebSocket")
	{
		/*
		auto i = boost::any_cast<const int*>(obj);
		ws.Send(JsonConvert.SerializeObject(obj));
		*/
		return true;
	}
	return false;
}

void Utils::sendAddUserRequest(string user, string channel, string fullname, WsController c) {
	Entities::AddUser req = Entities::AddUser();
	req.sender = Config::userName;
	req.user = user;
	req.channel = channel;
	req.fullname = fullname;
	req.type = "add_user";
	l.log("try send add user " + user + " to " + channel + " request");
	if (Utils::sendRequest(req, c))
	{
		l.log("sended");
	}
	else
	{
		l.log("sending aborted");
	}
}

void Utils::sendGetOnlineUsersRequest(WsController c) {
	auto ws = c.getWs();
	if (typeid(ws).name() == "WebSocket")
	{
		l.log("sending online users request");
		Entities::GetOnlineUsers req = Entities::GetOnlineUsers();
		req.sender = Config::userName;
		req.type = "get_online_users";
		/*
		ws.Send(JsonConvert.SerializeObject(req));
		*/
	}
}

void Utils::sendGetChannelUsersRequest(string channel, WsController c) {
	auto ws = c.getWs();
	if (typeid(ws).name() == "WebSocket")
	{
		l.log("sending get channel users request");
		Entities::GetChannelUsers req = Entities::GetChannelUsers();
		req.sender = Config::userName;
		req.type = "get_channel_users";
		req.channel = channel;
		/*
		ws.Send(JsonConvert.SerializeObject(req));
		*/
	}
}

/// <summary>
/// we retrieve long time from server and view it in message grids
/// </summary>
string Utils::longToDateTime(long time) {
	return "";
	//return new DateTime(time * 10000).ToString(@"dd\.MM HH\:mm");
}

/// <summary>
/// current date and time
/// </summary>
string Utils::getCurrentDatenTime() {
	return "";
	//return DateTime.Now.ToString(@"dd\.MM HH\:mm");
}

/// <summary>
/// current time
/// </summary>
string Utils::getCurrentTime() {
	return "";
	//return DateTime.Now.ToString(@"HH\:mm");
}


/// <summary>
/// return center position 
/// </summary>
/// <param name="resolution">is the full length of pixels</param>
/// <param name="actual">size of app in pixels</param>
double Utils::getCenter(double resolution, double actual) {
	return (resolution - actual) / 2;
}

// dynamic -> boost
Entities::MessageResponse Utils::dynamicToMessageResponse(boost::any const& obj) {
	auto objCast = boost::any_cast<Entities::MessageResponse>(obj);
	string from = objCast.from;
	string type = objCast.type;
	long time = objCast.time;
	string message = objCast.message;
	string channel = objCast.channel;
	return Entities::MessageResponse(type, message, from, time, channel);
}

Entities::NewChannelResponse Utils::dynamicToNewChannelResponse(boost::any const& obj) {
	auto ch = Entities::NewChannelResponse();
	auto objCast = boost::any_cast<Entities::NewChannelResponse>(obj);
	ch.name = objCast.name;
	ch.fullname = objCast.fullname;
	ch.admin = objCast.admin;
	ch.success = objCast.success;
	ch.type = objCast.type;
	return ch;
}
