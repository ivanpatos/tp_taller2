#include "../../include/server/RestServer.h"
#include "../../include/server/HttpResponse.h"

#include <iostream>
RestServer::RestServer(){
	this->server = mg_create_server(this, RestServer::handleEvent);
	mg_set_option(this->server, "listening_port", "8080");
}

RestServer::~RestServer(){
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

	std::string response = "";

	std::string method = connection->request_method;
	std::string resource = connection->uri;
	resource = resource.substr(1);

	std::string username = this->getValueFromHttpRequestHeader(connection, "username");
	std::string token = this->getValueFromHttpRequestHeader(connection, "token");
	std::string data = "";

	if (method == "GET")
		data = this->getQueryStringFromHttpRequest(connection);
	else
		data = this->getDataFromHttpRequest(connection);

	Service* service = this->serviceFactory.createService(resource, method);
	if (service){
		response = service->execute(username, token, data);
		delete service;
	}
	else
		response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_INVALID_REQUEST);

	mg_printf_data(connection, response.c_str());
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

std::string RestServer::getQueryStringFromHttpRequest(mg_connection *connection){
	return connection->query_string ? connection->query_string : "";
}

