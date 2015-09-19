#ifndef _SERVICE_FACTORY_H_
#define _SERVICE_FACTORY_H_

#include <vector>
#include "Services/Service.h"
#include "../database/Database.h"


class ServiceFactory{
private:
	Database &userDB, &folderDB, &fileDB, &dataDB;

public:
	ServiceFactory(Database &userDB, Database &folderDB, Database &fileDB, Database &dataDB);
	~ServiceFactory();
	Service* createService(const std::string& resource, const std::string& method) const;
};

#endif
