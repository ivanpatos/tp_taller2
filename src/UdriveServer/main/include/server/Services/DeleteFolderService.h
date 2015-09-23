#ifndef _DELETE_FOLDER_SERVICE_H_
#define _DELETE_FOLDER_SERVICE_H_

#include <string>
#include "Service.h"
#include "../../resources/Folder.h"
#include "../../database/Database.h"


class DeleteFolderService : public Service{
private:
	Database &userDB, &folderDB, &fileDB;

	void deleteAllTree(Folder *folder, const std::string& username, const std::string& token, const std::string& data, const std::string& query) const;


public:
	DeleteFolderService(Database &userDB, Database &folderDB, Database &fileDB);
	~DeleteFolderService();
	std::string execute(const std::string& username, const std::string& token, const std::string& data, const std::string& query) const;
};


#endif
