#ifndef _REST_SERVER_H_
#define _REST_SERVER_H_

#include <string>
#include "../../others/mongoose.h"
#include "ServiceFactory.h"


class RestServer{

private:
	mg_server *server;
	ServiceFactory serviceFactory;

	static int handleEvent(mg_connection *connection, mg_event event);
	void handleConnection(mg_connection *connection);

	std::string getValueFromHttpRequestHeader(mg_connection *connection, std::string name);
	std::string getDataFromHttpRequest(mg_connection *connection);
	std::string getQueryStringFromHttpRequest(mg_connection *connection);


public:
	RestServer();
	~RestServer();

	void start();
};


#endif
