#include "../include/server/Server.h"

#include "../include/utilities/easylogging++.h"

#include "../include/database/RocksDatabase.h"

INITIALIZE_EASYLOGGINGPP

int main() {

	RocksDatabase userDB("./userDB");
	RocksDatabase folderDB("./folderDB");
	RocksDatabase fileDB("./fileDB");
	RocksDatabase dataDB("./dataDB");

	Server server(userDB,folderDB,fileDB,dataDB);
	LOG(INFO) << "Server UP and RUNNING";
	server.start();

	return 0;
}
