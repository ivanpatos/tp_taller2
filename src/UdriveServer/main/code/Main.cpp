#include "../include/server/ServerThread.h"
#include "../include/database/RocksDatabase.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "../include/utilities/easylogging++.h"
INITIALIZE_EASYLOGGINGPP
#define ELPP_THREAD_SAFE

bool exists (const std::string& name) {
    std::ifstream f(name.c_str());
    if (f.good()) {
        f.close();
        return true;
    } else {
        f.close();
        return false;
    }
}

int main(int argc, char *argv[]) {

	if ( !exists("conf.conf") ) {
		LOG(WARNING) << "No hay archivo de configuracion para logs. Se procede a utilizar default." ;
	} else {

			char buff[255];
			int length = readlink("/proc/self/exe", buff, 254);

			char configName[] = "conf.conf";
			std::string str(buff);

			std::string::size_type t = str.find_last_of("/");
			str = str.substr(0,t);
			str.append("/");
			str.append(configName);

			// Load configuration from file
			el::Configurations conf(str);
			// Actually reconfigure all loggers instead
			el::Loggers::reconfigureAllLoggers(conf);
			// Now all the loggers will use configuration from file

			LOG(INFO) << "Archivo de configuracion de logs: " + str ;
	}

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
