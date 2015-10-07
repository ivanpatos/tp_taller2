#ifndef _GET_FILE_SERVICE_H_
#define _GET_FILE_SERVICE_H_

#include <string>
#include "Service.h"
#include "../../database/Database.h"


class GetFileService : public Service{
private:
	Database &userDB, &fileDB, &dataDB;

public:
	GetFileService(Database &userDB, Database &fileDB, Database &dataDB);
	~GetFileService();
	std::string execute(const std::string& username, const std::string& token, const std::string& data, const std::string& query) const;
        const char* name() const;
};


#endif
