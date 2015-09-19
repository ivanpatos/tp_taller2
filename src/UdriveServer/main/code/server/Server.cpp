#include "../../include/server/Server.h"
#include "../../include/server/HttpResponse.h"


Server::Server(){
	this->server = mg_create_server(this, Server::handleEvent);
	mg_set_option(this->server, "listening_port", "8080");
}

Server::~Server(){
	mg_destroy_server(&server);
}

void Server::start(){
	printf("Starting on port %s\n", mg_get_option(this->server, "listening_port"));
	for (;;)
		mg_poll_server(server, 1000);
}

int Server::handleEvent(mg_connection *connection, mg_event event){
	Server *server = (Server*) connection->server_param;
	switch (event) {
			case MG_AUTH:
				return MG_TRUE;
			case MG_REQUEST:
				server->handleRequest(connection);
				return MG_TRUE;
			default:
				return MG_FALSE;
		}
}

void Server::handleRequest(mg_connection *connection){

	std::string response = "";

	std::string method = connection->request_method;
	std::string resource = connection->uri;
	resource = resource.substr(1);

	std::string username = this->getValueFromRequestHeader(connection, "username");
	std::string token = this->getValueFromRequestHeader(connection, "token");
	std::string data = "";

	if (method == "GET")
		data = this->getQueryStringFromRequest(connection);
	else
		data = this->getDataFromRequest(connection);

	Service* service = this->serviceFactory.createService(resource, method);
	if (service){
		response = service->execute(username, token, data);
		delete service;
	}
	else
		response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_INVALID_REQUEST);

	mg_printf_data(connection, response.c_str());
}

std::string Server::getValueFromRequestHeader(mg_connection *connection, std::string name){
	const char* header = mg_get_header(connection, name.c_str());
	if (header){
		std::string value(header);
		return value;
	}
	else
		return "";
}

std::string Server::getDataFromRequest(mg_connection *connection){
	if (connection->content_len != 0){
		std::string data(connection->content, connection->content_len);
		return data;
	}
	else
		return "";
}

std::string Server::getQueryStringFromRequest(mg_connection *connection){
	return connection->query_string ? connection->query_string : "";
}

