#ifndef _CREATE_USER_SERVICE_H_
#define _CREATE_USER_SERVICE_H_

#include <string>
#include "Service.h"
#include "../../database/Database.h"
#include "../../resources/User.h"


class CreateUserService : public Service{
private:
	Database &userDB, &folderDB;

	bool initUserFolders(const User& user) const;

public:
	CreateUserService(Database &userDB, Database &folderDB);
	~CreateUserService();
	std::string execute(const std::string& username, const std::string& token, const std::string& data) const;
};


#endif
