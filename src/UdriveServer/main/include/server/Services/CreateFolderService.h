#ifndef _CREATE_FOLDER_SERVICE_H_
#define _CREATE_FOLDER_SERVICE_H_

#include <string>
#include "Service.h"
#include "../../database/Database.h"


class CreateFolderService : public Service{
private:
	Database &userDB, &folderDB, &fileDB;

public:
	CreateFolderService(Database &userDB, Database &folderDB, Database &fileDB);
	~CreateFolderService();
	std::string execute(const std::string& username, const std::string& token, const std::string& data, const std::string& query) const;
};


#endif
