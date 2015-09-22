#ifndef _DELETE_FILE_SERVICE_H_
#define _DELETE_FILE_SERVICE_H_

#include <string>
#include "Service.h"
#include "../../resources/Folder.h"
#include "../../database/Database.h"


class DeleteFileService : public Service{
private:
	Database &userDB, &folderDB, &fileDB;

	void deleteFileFromOwner(Folder* folder, File *file) const;

public:
	DeleteFileService(Database &userDB, Database &folderDB, Database &fileDB);
	~DeleteFileService();
	std::string execute(const std::string& username, const std::string& token, const std::string& data, const std::string& query) const;
};


#endif
