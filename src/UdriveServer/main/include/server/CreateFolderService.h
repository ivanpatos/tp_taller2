#ifndef _CREATE_FOLDER_SERVICE_H_
#define _CREATE_FOLDER_SERVICE_H_

#include <string>
#include "Service.h"
#include "ServiceCreator.h"


class CreateFolderService : public Service{
public:
	CreateFolderService();
	~CreateFolderService();
	std::string execute(const std::string& username, const std::string& token, const std::string& data) const;
};


class CreateFolderServiceCreator : public ServiceCreator{
public:
	Service* create() const;
	std::string getResource() const;
	std::string getMethod() const;
private:
	static const std::string resource;
	static const std::string method;
};


#endif
