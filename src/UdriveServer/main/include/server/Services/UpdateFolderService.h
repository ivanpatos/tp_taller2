#ifndef _UPDATE_FOLDER_SERVICE_H_
#define _UPDATE_FOLDER_SERVICE_H_

#include <string>
#include "Service.h"
#include "../../database/Database.h"
#include "../../../include/resources/Folder.h"


class UpdateFolderService : public Service{
private:
	Database &userDB, &folderDB, &fileDB, &dataDB;

	void updateAllTree(Folder *folder, const std::string& username, const std::string& token, const std::string& data, const std::string& query) const;

public:
	UpdateFolderService(Database &userDB, Database &folderDB, Database &fileDB, Database &dataDB);
	~UpdateFolderService();
	std::string execute(const std::string& username, const std::string& token, const std::string& data, const std::string& query) const;
        const char* name() const;
};


#endif
