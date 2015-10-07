#ifndef _LOGOUT_SERVICE_H_
#define _LOGOUT_SERVICE_H_

#include <string>
#include "Service.h"
#include "../../database/Database.h"


class LogoutService : public Service{
private:
	Database &userDB;

public:
	LogoutService(Database &userDB);
	~LogoutService();
	std::string execute(const std::string& username, const std::string& token, const std::string& data, const std::string& query) const;
        const char* name() const;
};


#endif
