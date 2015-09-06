#include "RestServer.h"


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
	string uri(connection->uri);
	string method(connection->request_method);
	//string queryString(connection->query_string);

	if (uri == "/user"){
		if (method == "GET"){
			this->getUserRequest(connection);
			return;
		}
		else if (method == "POST"){
			this->createUserRequest(connection);
			return;
		}
	}
}

string RestServer::getValueFromHttpRequestHeader(mg_connection *connection, string name){
	const char* header = mg_get_header(connection, name.c_str());
	if (header){
		string value(header);
		return value;
	}
	else
		return "";
}

string RestServer::getDataFromHttpRequest(mg_connection *connection){
	if (connection->content_len != 0){
		string data(connection->content, connection->content_len);
		return data;
	}
	else
		return "";
}

void RestServer::createUserRequest(mg_connection *connection){

	string data = this->getDataFromHttpRequest(connection);
	string response = this->serviceManager->createUser(data);
	mg_printf_data(connection, response.c_str());
}

void RestServer::getUserRequest(mg_connection *connection){

	string username = this->getValueFromHttpRequestHeader(connection, "user");
	string token = this->getValueFromHttpRequestHeader(connection, "token");

	string query("username=");
	string queryString(connection->query_string);
	string queryUsername = queryString.substr(queryString.find(query)+query.length());

	string response = this->serviceManager->getUser(username, token, queryUsername);
	mg_printf_data(connection, response.c_str());
}
