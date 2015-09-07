#ifndef _SERVICE_MANAGER_H_
#define _SERVICE_MANAGER_H_

#include <string>
#include "../resources/User.h"


class ServiceManager{

private:
	bool authenticateRequest(const User& user, const std::string& token);
	void generateToken(User *user);

public:
	ServiceManager();
	~ServiceManager();

	std::string login(const std::string& username, const std::string& password);
	std::string logout(const std::string& username, const std::string& token);
	std::string createUser(const std::string& data);
	std::string getUser(const std::string& username, const std::string& token, const std::string& queryUsername);

};

#endif
