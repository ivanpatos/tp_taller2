#include "../include/server/Server.h"

#include "../include/utilities/easylogging++.h"

INITIALIZE_EASYLOGGINGPP

int main() {

	Server server;
	LOG(INFO) << "Server UP and RUNNING";
	server.start();

	return 0;
}
