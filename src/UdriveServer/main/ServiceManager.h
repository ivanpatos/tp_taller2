#ifndef _SERVICE_MANAGER_H_
#define _SERVICE_MANAGER_H_

#include <string>
#include "json/json.h"
#include "User.h"
#include "DataManager.h"
#include "HttpResponse.h"


class ServiceManager{

private:
	bool authenticateRequest(const User& user, const std::string& token);

public:
	ServiceManager();
	~ServiceManager();

	std::string createUser(const std::string& data);
	std::string getUser(const std::string& username, const std::string& token, const std::string& queryUsername);

};

#endif
