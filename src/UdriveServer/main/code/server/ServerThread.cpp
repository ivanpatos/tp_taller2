#include "../../include/server/ServerThread.h"


ServerThread::ServerThread(Database& userDB,
		Database& folderDB,
		Database& fileDB,
		Database& dataDB
		) : server(userDB, folderDB, fileDB, dataDB), thread(0){
}

ServerThread::~ServerThread(){
}

void ServerThread::start(){
	pthread_create(&this->thread, NULL, this->startServer, this);
}

void ServerThread::join(){
	this->server.stop();
	pthread_join(this->thread, NULL);
}

void* ServerThread::startServer(void* serverThread){
	ServerThread* thread = (ServerThread*) serverThread;
	thread->server.start();
	return NULL;
}
