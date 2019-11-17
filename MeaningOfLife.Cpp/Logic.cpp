#include "Logic.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <time.h>

#include "ws_client_orig.h"
#include "CastCoreUtils.h"
#include "WS_Core.h"

using namespace std;

wstring MeaningOfLife::Cpp::Logic::Get(string text) const
{
	cout << text << endl;
	string host = "ws://echo.websocket.org";
	
	try {
		WS_Core core(host);
		core.send("Дарова");
		core.send("Hi there");
		core.send("Как дела?");

		waitSec(3);
		//core.close();
		vector<string> messages = core.getMessages();
		for (auto i = messages.begin(); i != messages.end(); ++i) {
			cout << *i << "; ";
		}
		cout << endl;
	}
	catch (std::exception const& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return string_to_wstring(e.what());
	}
	int id = -10;
	string two = "Привет ыыы ";
	wstring wide = string_to_wstring(two);

	wstring res = wide + L" conn id: " + to_wstring(id);
	return res;
}