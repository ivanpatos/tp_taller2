#ifndef _CREATE_FILE_SERVICE_H_
#define _CREATE_FILE_SERVICE_H_

#include <string>
#include "Service.h"
#include "../../database/Database.h"


class CreateFileService : public Service{
private:
	Database &userDB, &folderDB, &fileDB, &dataDB;

public:
	CreateFileService(Database &userDB, Database &folderDB, Database &fileDB, Database &dataDB);
	~CreateFileService();
	std::string execute(const std::string& username, const std::string& token, const std::string& data, const std::string& query) const;
        const char* name() const;
};


#endif
