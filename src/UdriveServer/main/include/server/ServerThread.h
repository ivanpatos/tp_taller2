#ifndef _SERVER_THREAD_H_
#define _SERVER_THREAD_H_

#include <pthread.h>
#include "Server.h"
#include "../database/Database.h"

class ServerThread{

private:
	Server server;
	pthread_t thread;

public:
	ServerThread(Database& userDB, Database& folderDB, Database& fileDB, Database& dataDB);
	~ServerThread();
	void start();
	void join();
	static void* startServer(void* serverThread);
};


#endif
