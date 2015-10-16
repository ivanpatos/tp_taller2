#include "../../include/server/Server.h"
#include "../../include/server/HttpResponse.h"


Server::Server() : userDB("./userDB"), folderDB("./folderDB"), fileDB("./fileDB"), dataDB("./dataDB"),
	serviceFactory(userDB, folderDB, fileDB, dataDB){
	this->server = mg_create_server(this, Server::handleEvent);
	mg.setOption(this->server, "listening_port", "8080");
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

	std::string uri = connection->uri;
	std::string method = connection->request_method;
	std::string resource = uri.substr(1, uri.find("/",1)-1);

	std::string username = this->getValueFromRequestHeader(connection, "username");
	std::string token = this->getValueFromRequestHeader(connection, "token");
	std::string data = this->getDataFromRequest(connection);
	std::string query = this->getQueryStringFromRequest(connection);

	Service* service = this->serviceFactory.createService(resource, method);
	std::string response = service->execute(username, token, data, query);
	mg.mgprintfData(connection, response.c_str());
	delete service;
}

std::string Server::getValueFromRequestHeader(mg_connection *connection, const std::string& name){
	const char* header = mg.getHeader(connection, name.c_str());
	if (header){
		std::string value(header);
		return value;
	}
	else
		return "";
}

std::string Server::getDataFromRequest(mg_connection *connection){
	if (mg.contentLen(connection)!= 0){
		std::string data(connection->content, connection->content_len);
		return data;
	}
	else
		return "";
}

std::string Server::getQueryStringFromRequest(mg_connection *connection){
	std::string query;
	std::string uri = connection->uri;
	if (uri.find("/",1) != std::string::npos){
		query = uri.substr(uri.find("/",1)+1);
		if (mg.queryString(connection))
			query = query + "?" + mg.queryString(connection);
	}
	else
	if (mg.queryString(connection)){
		query = mg.queryString(connection);
		query = "?" + query;
	}
	else
		query = "";
	return query;
}

//WARNING: only for test
void Server::setWrapperMongoose(WrapperMongoose &mg_w){
	mg = mg_w;
}

