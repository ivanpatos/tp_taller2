#ifndef _SERVICE_FACTORY_H_
#define _SERVICE_FACTORY_H_

#include <vector>
#include "Service.h"
#include "ServiceCreator.h"


class ServiceFactory{

private:
	std::vector<ServiceCreator*> serviceCreatorVector;

public:
	ServiceFactory();
	~ServiceFactory();
	Service* createService(const std::string& resource, const std::string& method) const;

};

#endif
