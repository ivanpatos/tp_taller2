#ifndef _UPDATE_FILE_SERVICE_H_
#define _UPDATE_FILE_SERVICE_H_

#include <string>
#include "Service.h"
#include "../../database/Database.h"

/**
 * Servicio encargado de actualizar ya sea metadatos como datos físicos de un archivo.
 */
class UpdateFileService : public Service{
private:
	Database &userDB, &folderDB, &fileDB, &dataDB;

public:
	UpdateFileService(Database &userDB, Database &folderDB, Database &fileDB, Database &dataDB);
	~UpdateFileService();
	std::string execute(const std::string& username, const std::string& token, const std::string& data, const std::string& query) const;
        const char* name() const;
};


#endif
