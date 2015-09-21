#ifndef _GET_USER_SERVICE_H_
#define _GET_USER_SERVICE_H_

#include <string>
#include "Service.h"
#include "../../database/Database.h"


class GetUserService : public Service{
private:
	Database &userDB;

public:
	GetUserService(Database &userDB);
	~GetUserService();
	std::string execute(const std::string& username, const std::string& token, const std::string& data, const std::string& query) const;
};


#endif
