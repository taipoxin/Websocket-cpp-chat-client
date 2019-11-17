#include "WS_Core.h"

using namespace std;
using namespace MeaningOfLife::Cpp;

int WS_Core::connectWS(double timeoutS) {
	int id = -10;
	clock_t this_time = clock();
	clock_t last_time = this_time;
	id = endpoint.connect(host);
	connection_metadata::ptr metadata = endpoint.get_metadata(id);

	while ((metadata.get()->get_status() != "Open") || (timeoutS * CLOCKS_PER_SEC > (double)(this_time - last_time))) {
		this_time = clock();
	}
	if (timeoutS * CLOCKS_PER_SEC < (double)(this_time - last_time)) {
		cout << "Connection Timeout" << endl;
	}
	return id;
}


void WS_Core::send(string message) {
	endpoint.send(this->id, message);
}
std::vector<std::string> WS_Core::getMessages() {
	connection_metadata::ptr metadata = endpoint.get_metadata(this->id);
	return metadata.get()->get_messages();
}

void WS_Core::close() {
	int close_code = websocketpp::close::status::normal;
	endpoint.close(this->id, close_code, "normal");
}

WS_Core::WS_Core(string host) {
	this->host = host;
	this->id = connectWS(5);
	cout << "id set: " << id << endl;
}
