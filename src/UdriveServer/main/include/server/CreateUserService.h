#ifndef _CREATE_USER_SERVICE_H_
#define _CREATE_USER_SERVICE_H_

#include <string>
#include "Service.h"
#include "ServiceCreator.h"
#include "../resources/User.h"


class CreateUserService : public Service{
public:
	CreateUserService();
	~CreateUserService();
	std::string execute(const std::string& username, const std::string& token, const std::string& data) const;

private:
	bool initUserFolders(const User& user) const;

};


class CreateUserServiceCreator : public ServiceCreator{
public:
	Service* create() const;
	std::string getResource() const;
	std::string getMethod() const;
private:
	static const std::string resource;
	static const std::string method;
};


#endif
