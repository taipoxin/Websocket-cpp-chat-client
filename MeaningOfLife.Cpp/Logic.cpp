
#include "Logic.h"
#include "CastCoreUtils.h"
#include "WS_async.h"

using namespace std;


wstring MeaningOfLife::Cpp::Logic::Get(string text) const
{
	cout << text << endl;

	try {

		// The io_context is required for all I/O
		boost::asio::io_context ioc;

		// Launch the asynchronous operation
		std::make_shared<WS_async>(ioc)->run("echo.websocket.org", "80", text.c_str());

		// Run the I/O service. The call will return when
		// the socket is closed.
		ioc.run();
	}
	catch (std::exception const& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return string_to_wstring(e.what());
	}

	int id = -10;
	string two = "Дароу";

	wstring wide = string_to_wstring(two);
	
	wstring res = wide + L" conn id: " + to_wstring(id);
	return res;
}
