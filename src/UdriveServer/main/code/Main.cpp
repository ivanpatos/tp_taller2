#include "../include/server/Server.h"
#include "../include/database/RocksDatabase.h"


int main() {

	RocksDatabase userDB("./userDB");
	RocksDatabase folderDB("./folderDB");
	RocksDatabase fileDB("./fileDB");
	RocksDatabase dataDB("./dataDB");

	Server server(userDB,folderDB,fileDB,dataDB);
	server.start();

	return 0;
}
