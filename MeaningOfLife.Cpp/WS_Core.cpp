#include "WS_Core.h"
#include <fstream>

using namespace std;
using namespace MeaningOfLife::Cpp;

int WS_Core::connectWS(double timeoutS) {
	try {
		int id = -10;
		clock_t this_time = clock();
		clock_t last_time = this_time;
		cout << "try to connect..." << endl;
		id = endpoint.connect(this->host);
		connection_metadata::ptr metadata = endpoint.get_metadata(id);
		while ((metadata.get()->get_status() != "Open") || (timeoutS * CLOCKS_PER_SEC > (double)(this_time - last_time))) {
			this_time = clock();
		}
		cout << "here";
		if (timeoutS * CLOCKS_PER_SEC < (double)(this_time - last_time)) {
			cout << "Connection Timeout" << endl;
		}
		return id;
	}
	catch (std::exception const& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		cout << e.what();
		return -10;
	}
}

void WS_Core::reconnect() {
	bool reconnected = false;
	while (!this->isAlive()) {
		cout << "Connection lost. Try to reconnect..." << endl;
		this->id = connectWS(10);
		reconnected = true;
	}
	if (reconnected) {
		cout << "Connection established fine" << endl;
	}
}

void WS_Core::send(string message) {
	if (!this->isAlive()) {
		reconnect();
	}
	cout << endl;
	endpoint.send(this->id, message);
}
std::vector<std::string> WS_Core::getMessages() {
	cout << endl;
	connection_metadata::ptr metadata = endpoint.get_metadata(this->id);
	return metadata.get()->get_messages();
}

void WS_Core::close() {
	cout << endl;
	int close_code = websocketpp::close::status::normal;
	endpoint.close(this->id, close_code, "normal");
}

bool WS_Core::isAlive() {
	cout << endl;
	connection_metadata::ptr metadata = endpoint.get_metadata(this->id);
	cout << *metadata << endl;
	string status = metadata.get()->get_status();
	return (status == "Open");
}

WS_Core::WS_Core(string host) {
	cout << endl;
	this->host = host;
	this->id = connectWS(10);
	
	if (!isAlive()) {
		reconnect();
	}
	cout << id;
	cout << "id set: " << id << endl;
	// Return good connect output to UI
	ofstream writer;
	writer.open("output.txt");
	writer << "connected";
}

WS_Core::WS_Core() {
}
