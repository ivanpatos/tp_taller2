#ifndef _SERVICE_CREATOR_H_
#define _SERVICE_CREATOR_H_

#include "Service.h"


class ServiceCreator{

public:
	virtual ~ServiceCreator(){}
	virtual Service* create() const = 0;
	virtual std::string getResource() const = 0;
	virtual std::string getMethod() const = 0;

};

#endif
