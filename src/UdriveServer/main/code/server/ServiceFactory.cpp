#include "../../include/server/ServiceFactory.h"
#include "../../include/server/LoginService.h"
#include "../../include/server/LogoutService.h"
#include "../../include/server/CreateUserService.h"
#include "../../include/server/GetUserService.h"
#include "../../include/server/UpdateUserService.h"
#include "../../include/server/CreateFolderService.h"
#include "../../include/server/GetFolderService.h"
#include "../../include/server/CreateFileService.h"


ServiceFactory::ServiceFactory(){
	this->serviceCreatorVector.push_back(new LoginServiceCreator());
	this->serviceCreatorVector.push_back(new LogoutServiceCreator());
	this->serviceCreatorVector.push_back(new CreateUserServiceCreator());
	this->serviceCreatorVector.push_back(new GetUserServiceCreator());
	this->serviceCreatorVector.push_back(new UpdateUserServiceCreator());
	this->serviceCreatorVector.push_back(new CreateFolderServiceCreator());
	this->serviceCreatorVector.push_back(new GetFolderServiceCreator());
	this->serviceCreatorVector.push_back(new CreateFileServiceCreator());
}

ServiceFactory::~ServiceFactory(){
	for(std::vector<ServiceCreator*>::const_iterator it = this->serviceCreatorVector.begin(); it != this->serviceCreatorVector.end(); ++it)
		delete *it;
}

Service* ServiceFactory::createService(const std::string& resource, const std::string& method) const{
	for(std::vector<ServiceCreator*>::const_iterator it = this->serviceCreatorVector.begin(); it != this->serviceCreatorVector.end(); ++it) {
		if ((*it)->getResource() == resource && (*it)->getMethod() == method)
			return (*it)->create();
	}
	return NULL;
}
