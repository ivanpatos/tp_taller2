#ifndef _UPDATE_USER_SERVICE_H_
#define _UPDATE_USER_SERVICE_H_

#include <string>
#include "Service.h"
#include "ServiceCreator.h"


class UpdateUserService : public Service{
public:
	UpdateUserService();
	~UpdateUserService();
	std::string execute(const std::string& username, const std::string& token, const std::string& data) const;
};


class UpdateUserServiceCreator : public ServiceCreator{
public:
	Service* create() const;
	std::string getResource() const;
	std::string getMethod() const;
private:
	static const std::string resource;
	static const std::string method;
};


#endif
