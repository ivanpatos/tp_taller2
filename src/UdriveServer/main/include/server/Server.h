#ifndef _SERVER_H_
#define _SERVER_H_

#include <string>
#include "../../others/mongoose.h"
#include "../database/Database.h"
#include "../utilities/WrapperMongoose.h"
#include "ServiceFactory.h"

#include "../../include/utilities/easylogging++.h"
/**
 * Define el servidor http con interfaz del tipo restful api.
 */
class Server{

private:
	mg_server *server;
	ServiceFactory serviceFactory;
	Database &userDB, &folderDB, &fileDB, &dataDB;
	WrapperMongoose mg;
	bool finish;

	static int handleEvent(mg_connection *connection, mg_event event);
	void handleRequest(mg_connection *connection);
	std::string getValueFromRequestHeader(mg_connection *connection, const std::string& name);
	std::string getDataFromRequest(mg_connection *connection);
	std::string getQueryStringFromRequest(mg_connection *connection);

public:
	/**
	 * Constructor.
	 * @param userDB Base de datos de usuarios.
	 * @param folderDB Base de datos de carpetas.
	 * @param fileDB Base de datos de archivos.
	 * @param dataDB Base de datos de versiones de archivos.
	 */
	Server(Database& userDB,Database& folderDB,Database& fileDB,Database& dataDB);

	~Server();

	/**
	 * Wrapper de Mongoose
	 */
	void setWrapperMongoose(WrapperMongoose &mg_w);

	/**
	 * Arranca el servidor. Verifica que hayan requests a procesar.
	 */
	void start();

	/**
	 * Para el servidor.
	 */
	void stop();
};


#endif

