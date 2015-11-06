#ifndef _GET_FILE_SERVICE_H_
#define _GET_FILE_SERVICE_H_

#include <string>
#include "Service.h"
#include "../../database/Database.h"


/**
 * Servicio encargado de devolver ya sea los metadatos como los datos físicos de un archivo.
 */
class GetFileService : public Service{
private:
	Database &userDB, &folderDB, &fileDB, &dataDB;

public:
	GetFileService(Database &userDB, Database &folderDB, Database &fileDB, Database &dataDB);
	~GetFileService();
	std::string execute(const std::string& username, const std::string& token, const std::string& data, const std::string& query) const;
        const char* name() const;
};


#endif
