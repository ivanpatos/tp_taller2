#ifndef _SERVICE_H_
#define _SERVICE_H_

#include <string>
#include "../../../include/utilities/easylogging++.h"

/**
 * Interfaz de servicio ofrecido por el servidor.
 */
class Service{
public:
	virtual ~Service(){}
	/**
	 * Ejecuta el servicio
	 * @param username Username del usuario que solicitió el servicio.
	 * @param token Token del usuario que solicitió el servicio.
	 * @param data Data a ser procesada por el servicio.
	 * @param query Query a ser procesado por el servicio.
	 * @return Mensaje generado por el servicio.
	 */
	virtual std::string execute(const std::string& username, const std::string& token, const std::string& data, const std::string& query) const = 0;

	/**
	 * @return Devuelve nombre del servicio.
	 */
    virtual const char* name() const = 0;
};

#endif
