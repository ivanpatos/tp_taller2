#ifndef _GET_FOLDER_SERVICE_H_
#define _GET_FOLDER_SERVICE_H_

#include <string>
#include "Service.h"
#include "../../database/Database.h"


/**
 * Servicio encargado de devolver el contenido de una carpeta (metadatos).
 */
class GetFolderService : public Service{
private:
	Database &userDB, &folderDB, &fileDB;

public:
	GetFolderService(Database &userDB, Database &folderDB, Database &fileDB);
	~GetFolderService();
	std::string execute(const std::string& username, const std::string& token, const std::string& data, const std::string& query) const;
        const char* name() const;
};


#endif
