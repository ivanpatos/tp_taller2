#ifndef _LOGIN_SERVICE_H_
#define _LOGIN_SERVICE_H_

#include <string>
#include "Service.h"
#include "../../database/Database.h"


class LoginService : public Service{
private:
	Database &userDB;

public:
	LoginService(Database &userDB);
	~LoginService();
	std::string execute(const std::string& username, const std::string& token, const std::string& data, const std::string& query) const;
};


#endif
