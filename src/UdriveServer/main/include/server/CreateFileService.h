#ifndef _CREATE_FILE_SERVICE_H_
#define _CREATE_FILE_SERVICE_H_

#include <string>
#include "Service.h"
#include "ServiceCreator.h"


class CreateFileService : public Service{
public:
	CreateFileService();
	~CreateFileService();
	std::string execute(const std::string& username, const std::string& token, const std::string& data) const;
};


class CreateFileServiceCreator : public ServiceCreator{
public:
	Service* create() const;
	std::string getResource() const;
	std::string getMethod() const;
private:
	static const std::string resource;
	static const std::string method;
};


#endif
