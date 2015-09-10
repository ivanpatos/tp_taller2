#include "../../include/server/RestServer.h"


RestServer::RestServer(){
	serviceManager = new ServiceManager();
	this->server = mg_create_server(this, RestServer::handleEvent);
	mg_set_option(this->server, "listening_port", "8080");
}

RestServer::~RestServer(){
	delete this->serviceManager;
	mg_destroy_server(&server);
}

void RestServer::start(){
	printf("Starting on port %s\n", mg_get_option(this->server, "listening_port"));
	for (;;)
		mg_poll_server(server, 1000);
}

int RestServer::handleEvent(mg_connection *connection, mg_event event){
	RestServer *server = (RestServer*) connection->server_param;
	switch (event) {
			case MG_AUTH:
				return MG_TRUE;
			case MG_REQUEST:
				server->handleConnection(connection);
				return MG_TRUE;
			default:
				return MG_FALSE;
		}
}

void RestServer::handleConnection(mg_connection *connection){
	std::string uri(connection->uri);
	std::string method(connection->request_method);

	if (uri == "/user"){
		if (method == "GET" && connection->query_string)
			this->getUserRequest(connection);
		else if (method == "GET")
			this->getAllUsersRequest(connection);
		else if (method == "POST")
			this->createUserRequest(connection);
		else if (method == "PUT")
			this->updateUserRequest(connection);
	}
	else if (uri == "/login" && method == "POST")
			this->loginRequest(connection);
	else if (uri == "/logout" && method == "POST")
			this->logoutRequest(connection);
}

std::string RestServer::getValueFromHttpRequestHeader(mg_connection *connection, std::string name){
	const char* header = mg_get_header(connection, name.c_str());
	if (header){
		std::string value(header);
		return value;
	}
	else
		return "";
}

std::string RestServer::getDataFromHttpRequest(mg_connection *connection){
	if (connection->content_len != 0){
		std::string data(connection->content, connection->content_len);
		return data;
	}
	else
		return "";
}

void RestServer::loginRequest(mg_connection *connection){
	std::string username = this->getValueFromHttpRequestHeader(connection, "username");
	std::string password = this->getValueFromHttpRequestHeader(connection, "password");
	std::string response = this->serviceManager->login(username, password);
	mg_printf_data(connection, response.c_str());
}

void RestServer::logoutRequest(mg_connection *connection){
	std::string username = this->getValueFromHttpRequestHeader(connection, "username");
	std::string token = this->getValueFromHttpRequestHeader(connection, "token");
	std::string response = this->serviceManager->logout(username, token);
	mg_printf_data(connection, response.c_str());
}

void RestServer::createUserRequest(mg_connection *connection){

	std::string data = this->getDataFromHttpRequest(connection);
	std::string response = this->serviceManager->createUser(data);
	mg_printf_data(connection, response.c_str());
}

void RestServer::getUserRequest(mg_connection *connection){

	std::string username = this->getValueFromHttpRequestHeader(connection, "username");
	std::string token = this->getValueFromHttpRequestHeader(connection, "token");

	std::string query("username=");
	std::string queryString(connection->query_string);
	std::string queryUsername = queryString.substr(queryString.find(query)+query.length());

	std::string response = this->serviceManager->getUser(username, token, queryUsername);
	mg_printf_data(connection, response.c_str());
}

void RestServer::getAllUsersRequest(mg_connection *connection){

	std::string username = this->getValueFromHttpRequestHeader(connection, "username");
	std::string token = this->getValueFromHttpRequestHeader(connection, "token");
	std::string response = this->serviceManager->getAllUsers(username, token);
	mg_printf_data(connection, response.c_str());
}

void RestServer::updateUserRequest(mg_connection *connection){

	std::string username = this->getValueFromHttpRequestHeader(connection, "username");
	std::string token = this->getValueFromHttpRequestHeader(connection, "token");
	std::string data = this->getDataFromHttpRequest(connection);
	std::string response = this->serviceManager->updateUser(username, token, data);
	mg_printf_data(connection, response.c_str());
}
