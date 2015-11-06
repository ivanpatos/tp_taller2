#ifndef _UPDATE_USER_SERVICE_H_
#define _UPDATE_USER_SERVICE_H_

#include <string>
#include "Service.h"
#include "../../database/Database.h"


/**
 * Servicio encargado de actualizar el perfil de un usuario.
 */
class UpdateUserService : public Service{
public:
	UpdateUserService(Database &userDB);
	~UpdateUserService();
	std::string execute(const std::string& username, const std::string& token, const std::string& data, const std::string& query) const;
        const char* name() const;

private:
	Database &userDB;
};


#endif
