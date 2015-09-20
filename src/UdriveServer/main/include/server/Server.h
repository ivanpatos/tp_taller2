#ifndef _SERVER_H_
#define _SERVER_H_

#include <string>
#include "../../others/mongoose.h"
#include "../database/Database.h"
#include "ServiceFactory.h"


class Server{

private:
	mg_server *server;
	ServiceFactory serviceFactory;
	Database userDB, folderDB, fileDB, dataDB;

	static int handleEvent(mg_connection *connection, mg_event event);
	void handleRequest(mg_connection *connection);
	std::string getValueFromRequestHeader(mg_connection *connection, const std::string& name);
	std::string getDataFromRequest(mg_connection *connection);
	std::string getQueryStringFromRequest(mg_connection *connection);

public:
	Server();
	~Server();

	void start();
};


#endif