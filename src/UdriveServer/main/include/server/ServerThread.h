#ifndef _SERVER_THREAD_H_
#define _SERVER_THREAD_H_

#include <pthread.h>
#include "Server.h"
#include "../database/Database.h"

/**
 * Clase que encapsula la ejecución del servidor.
 */
class ServerThread{
private:
	Server server;
	pthread_t thread;

public:
	/**
	 * Constructor.
	 * @param userDB Base de datos de usuarios.
	 * @param folderDB Base de datos de carpetas.
	 * @param fileDB Base de datos de archivos.
	 * @param dataDB Base de datos de versiones de archivos.
	 */
	ServerThread(Database& userDB, Database& folderDB, Database& fileDB, Database& dataDB);

	~ServerThread();

	/**
	 * Crear el thread y dispara el servidor.
	 */
	void start();

	/**
	 * Para el servidor y joinea el thread.
	 */
	void join();

	/**
	 * Arranca el servidor.
	 */
	static void* startServer(void* serverThread);
};


#endif
