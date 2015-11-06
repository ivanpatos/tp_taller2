#ifndef _VERSION_H_
#define _VERSION_H_

#include <string>
#include "../../others/json/json.h"

/**
 * Modela una versión de un archivo a guardar en el servidor.
 */
class Version{

private:
	std::string id;
	std::string data;

public:
	/**
	 * Inicializa una versión de un archivo a partir de un id y los datos de la respectiva versión.
	 * @param id Id de la versión.
	 * @param data Datos de la versión.
	 */
	Version(const std::string& id, const std::string& data);
	~Version();

	/**
	 * @return Devuelve los datos de la versión.
	 */
	std::string getData() const;

	/**
	 * @return Devuelve el Id de la versión.
	 */
	std::string getId() const;

	/**
	 * @return Devuelve json de la versión.
	 */
	Json::Value getJson() const;
};


#endif
