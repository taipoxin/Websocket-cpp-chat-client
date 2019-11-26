#include "ws_client_orig.h"
#include "CastCoreUtils.h"


using namespace std;

// connection_metadata

connection_metadata::connection_metadata(int id, websocketpp::connection_hdl hdl, std::string uri)
	: m_id(id)
	, m_hdl(hdl)
	, m_status("Connecting")
	, m_uri(uri)
	, m_server("N/A")
{
	handler = new MessageHandler("output.txt");
}

void connection_metadata::on_open(client * c, websocketpp::connection_hdl hdl) {
	m_status = "Open";
	client::connection_ptr con = c->get_con_from_hdl(hdl);
	m_server = con->get_response_header("Server");
	cout << "Opened successfully" << endl;
}

void connection_metadata::on_fail(client * c, websocketpp::connection_hdl hdl) {
	m_status = "Failed";
	client::connection_ptr con = c->get_con_from_hdl(hdl);
	cout << con->get_ec().message() << endl;

	m_server = con->get_response_header("Server");
	m_error_reason = con->get_ec().message();
}

void connection_metadata::on_close(client * c, websocketpp::connection_hdl hdl) {
	m_status = "Closed";
	client::connection_ptr con = c->get_con_from_hdl(hdl);
	std::stringstream s;
	s << "close code: " << con->get_remote_close_code() << " ("
		<< websocketpp::close::status::get_string(con->get_remote_close_code())
		<< "), close reason: " << con->get_remote_close_reason();
	m_error_reason = s.str();
}

void connection_metadata::on_message(websocketpp::connection_hdl, client::message_ptr msg) {
	cout << "inside on_message" << endl;
	//cout << msg->get_payload() << endl;
	m_messages.push_back(msg->get_payload());
	handler->handle(msg->get_payload());
}

websocketpp::connection_hdl connection_metadata::get_hdl() const {
	return m_hdl;
}

int connection_metadata::get_id() const {
	return m_id;
}

std::string connection_metadata::get_status() const {
	return m_status;
}
std::vector<std::string> connection_metadata::get_messages() {
	return m_messages;
}
std::vector<std::string> connection_metadata::get_messages_sent() {
	return m_messages_sent;
}

void connection_metadata::record_sent_message(std::string message) {
	m_messages_sent.push_back(message);
}

// END connection_metadata


// websocket_endpoint

websocket_endpoint::websocket_endpoint() : m_next_id(0) {
	m_endpoint.clear_access_channels(websocketpp::log::alevel::all);
	m_endpoint.clear_error_channels(websocketpp::log::elevel::all);

	m_endpoint.init_asio();
	m_endpoint.start_perpetual();
	m_endpoint.set_open_handshake_timeout(10000);
	m_thread = websocketpp::lib::make_shared<websocketpp::lib::thread>(&client::run, &m_endpoint);
}

websocket_endpoint::~websocket_endpoint() {
	m_endpoint.stop_perpetual();

	for (con_list::const_iterator it = m_connection_list.begin(); it != m_connection_list.end(); ++it) {
		if (it->second->get_status() != "Open") {
			// Only close open connections
			continue;
		}

		std::cout << "> Closing connection " << it->second->get_id() << std::endl;

		websocketpp::lib::error_code ec;
		m_endpoint.close(it->second->get_hdl(), websocketpp::close::status::going_away, "", ec);
		if (ec) {
			std::cout << "> Error closing connection " << it->second->get_id() << ": "
				<< ec.message() << std::endl;
		}
	}

	m_thread->join();
}

int websocket_endpoint::connect(std::string const & uri) {
	websocketpp::lib::error_code ec;

	client::connection_ptr con = m_endpoint.get_connection(uri, ec);

	//cout << "here" << endl;
	if (ec) {
		std::cout << "> Connect initialization error: " << ec.message() << std::endl;
		return -1;
	}

	int new_id = m_next_id++;
	connection_metadata::ptr metadata_ptr = websocketpp::lib::make_shared<connection_metadata>(new_id, con->get_handle(), uri);

	m_connection_list[new_id] = metadata_ptr;

	con->set_open_handler(websocketpp::lib::bind(
		&connection_metadata::on_open,
		metadata_ptr,
		&m_endpoint,
		websocketpp::lib::placeholders::_1
	));
	con->set_fail_handler(websocketpp::lib::bind(
		&connection_metadata::on_fail,
		metadata_ptr,
		&m_endpoint,
		websocketpp::lib::placeholders::_1
	));
	con->set_close_handler(websocketpp::lib::bind(
		&connection_metadata::on_close,
		metadata_ptr,
		&m_endpoint,
		websocketpp::lib::placeholders::_1
	));
	con->set_message_handler(websocketpp::lib::bind(
		&connection_metadata::on_message,
		metadata_ptr,
		websocketpp::lib::placeholders::_1,
		websocketpp::lib::placeholders::_2
	));

	try {
		m_endpoint.connect(con);
	}
	catch (std::exception const& e)
	{
		std::cerr << "Error is : " << e.what() << std::endl;
		cout << "error:" << e.what() << endl;
	}

	return new_id;
}

void websocket_endpoint::close(int id, websocketpp::close::status::value code, std::string reason) {
	websocketpp::lib::error_code ec;

	cout << "Endpoint close" << endl;
	con_list::iterator metadata_it = m_connection_list.find(id);
	if (metadata_it == m_connection_list.end()) {
		std::cout << "> No connection found with id " << id << std::endl;
		return;
	}

	m_endpoint.close(metadata_it->second->get_hdl(), code, reason, ec);
	if (ec) {
		std::cout << "> Error initiating close: " << ec.message() << std::endl;
	}
}

void websocket_endpoint::send(int id, std::string message) {
	websocketpp::lib::error_code ec;
	std::cout << "> Send: " << message << endl;
	string base64_message = base64_encode(message);
	cout << "base64 send: " << base64_message << endl;
	con_list::iterator metadata_it = m_connection_list.find(id);
	if (metadata_it == m_connection_list.end()) {
		std::cout << "> No connection found with id " << id << std::endl;
		return;
	}

	m_endpoint.send(metadata_it->second->get_hdl(), base64_message, websocketpp::frame::opcode::binary, ec);
	if (ec) {
		std::cout << "> Error sending message: " << ec.message() << std::endl;
		return;
	}

	metadata_it->second->record_sent_message(message);
}

connection_metadata::ptr websocket_endpoint::get_metadata(int id) const {
	con_list::const_iterator metadata_it = m_connection_list.find(id);
	if (metadata_it == m_connection_list.end()) {
		return connection_metadata::ptr();
	}
	else {
		return metadata_it->second;
	}
}

// END websocket_endpoint


std::ostream & operator<< (std::ostream & out, connection_metadata const & data) {
	out << "> URI: " << data.m_uri << "\n"
		<< "> Status: " << data.m_status << "\n"
		<< "> Remote Server: " << (data.m_server.empty() ? "None Specified" : data.m_server) << "\n"
		<< "> Error/close reason: " << (data.m_error_reason.empty() ? "N/A" : data.m_error_reason) << "\n";
	out << "> Messages Processed: (" << data.m_messages.size() << ") \n";

	std::vector<std::string>::const_iterator it;
	for (it = data.m_messages.begin(); it != data.m_messages.end(); ++it) {
		out << *it << "\n";
	}

	return out;
}


int main() {
	bool done = false;
	std::string input;
	websocket_endpoint endpoint;

	while (!done) {
		std::cout << "Enter Command: ";
		std::getline(std::cin, input);

		if (input == "quit") {
			done = true;
		}
		else if (input == "help") {
			std::cout
				<< "\nCommand List:\n"
				<< "connect <ws uri>\n"
				<< "send <connection id> <message>\n"
				<< "close <connection id> [<close code:default=1000>] [<close reason>]\n"
				<< "show <connection id>\n"
				<< "help: Display this help text\n"
				<< "quit: Exit the program\n"
				<< std::endl;
		}
		else if (input.substr(0, 7) == "connect") {
			int id = endpoint.connect(input.substr(8));
			if (id != -1) {
				std::cout << "> Created connection with id " << id << std::endl;
			}
		}
		else if (input.substr(0, 4) == "send") {
			std::stringstream ss(input);

			std::string cmd;
			int id;
			std::string message;

			ss >> cmd >> id;
			std::getline(ss, message);

			endpoint.send(id, message);
		}
		else if (input.substr(0, 5) == "close") {
			std::stringstream ss(input);

			std::string cmd;
			int id;
			int close_code = websocketpp::close::status::normal;
			std::string reason;

			ss >> cmd >> id >> close_code;
			std::getline(ss, reason);

			endpoint.close(id, close_code, reason);
		}
		else if (input.substr(0, 4) == "show") {
			int id = atoi(input.substr(5).c_str());

			connection_metadata::ptr metadata = endpoint.get_metadata(id);
			if (metadata) {
				std::cout << *metadata << std::endl;
			}
			else {
				std::cout << "> Unknown connection id " << id << std::endl;
			}
		}
		else {
			std::cout << "> Unrecognized Command" << std::endl;
		}
	}

	return 0;
}