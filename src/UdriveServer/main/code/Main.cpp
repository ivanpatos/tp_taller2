#include "../include/server/ServerThread.h"
#include "../include/database/RocksDatabase.h"
#include <iostream>

int main() {

	RocksDatabase userDB("./userDB");
	RocksDatabase folderDB("./folderDB");
	RocksDatabase fileDB("./fileDB");
	RocksDatabase dataDB("./dataDB");

	ServerThread server(userDB,folderDB,fileDB,dataDB);
	server.start();
	bool finish = false;
	std::string input;
	while (!finish) {
		std::cin >> input;
		if (input == "stop")
			finish = true;
	}
	server.join();

	return 0;
}
