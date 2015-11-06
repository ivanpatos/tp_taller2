#ifndef _SERVICE_FACTORY_H_
#define _SERVICE_FACTORY_H_

#include <vector>
#include "Services/Service.h"
#include "../database/Database.h"

/**
 * Clase que encapsula la instanciación de un servicio a partir del recurso y el método solicitados.
 */
class ServiceFactory{
private:
	Database &userDB, &folderDB, &fileDB, &dataDB;

public:
	/**
	 * Constructor.
	 * @param userDB Base de datos de usuarios.
	 * @param folderDB Base de datos de carpetas.
	 * @param fileDB Base de datos de archivos.
	 * @param dataDB Base de datos de versiones de archivos.
	 */
	ServiceFactory(Database &userDB, Database &folderDB, Database &fileDB, Database &dataDB);
	~ServiceFactory();

	/**
	 * Devuelve una instancia de servicio a partir del recurso y el método.
	 * @param resource Recurso definido en la restful api.
	 * @param method Método definido en la restful api.
	 * @return Servicio solicitado.
	 */
	Service* createService(const std::string& resource, const std::string& method) const;
};

#endif
