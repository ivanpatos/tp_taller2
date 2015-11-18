#ifndef _FILE_H_
#define _FILE_H_

#include <string>
#include "../../others/json/json.h"
#include "../database/Database.h"
#include "User.h"

#include "../../include/utilities/easylogging++.h"

/**
 * Define un archivo.
 */
class File{

private:
	std::string id;
	std::string name;
	bool deleted;
	User *owner;
	std::string lastModified;
	User *lastUser;
	std::vector<User*> users;
	std::vector<std::string> labels;
	std::string extension;
	int version;

public:
	/**
	 * Inicializa un archivo a partir de un json.
	 * @param json Json del archivo a crear.
	 */
	File(const Json::Value& json, Database &userDB);

	/**
	 * Inicializa un archivo a partir de un json en forma de cadena de caracteres.
	 * @param jsonString String del json del archivo a crear.
	 * @param userDB Base de datos de usuarios.
	 */
	File(const std::string& jsonString, Database &userDB);
	~File();

	/**
	 * @return Id del archivo.
	 */
	std::string getId() const;

	/**
	 * @return Nombre del archivo.
	 */
	std::string getName() const;

	/**
	 * @return Extensión del archivo.
	 */
	std::string getExtension() const;

	/**
	 * @return Bool indicando si el archivo fue borrado.
	 */
	bool getDeleted() const;

	/**
	 * @return Int indicando última versión del archivo.
	 */
	int getVersion() const;

	/**
	 * @return Owner del archivo.
	 */
	User* getOwner() const;

	/**
	 * @return Vector del archivo.
	 */
	std::vector<User*> getUsers() const;

	/**
	 * Verifica si el usuario pasado es el owner del archivo.
	 * @param user usuario a comparar.
	 * @return Bool indicando si el usuario pasado es el owner del archivo.
	 */
	bool isOwner(const User& user) const;

	/**
	 * Incrementa en uno la versión del archivo.
	 */
	void increaseVersion();

	/**
	 * Verifica si el archivo tiene asignado alguna de las etiquetas pasadas.
	 * @param labels Vector de etiquetas.
	 * @return Bool indicando si el archivo tiene alguna etiqueta.
	 */
	bool hasAnyLabel(const std::vector<std::string>& labels) const;

	/**
	 * Verifica si el usuario pasado tiene permisos sobre el archivo.
	 * @param user Usuario a verificar permisos sobre el archivo.
	 * @return Bool indicando si usuario pasado tiene permisos sobre el archivo.
	 */
	bool hasPermission(const User& user) const;

	/**
	 * Setea el borrado lógico del archivo.
	 * @param state Bool a asignarle al archivo indicando si fue borrado.
	 */
	void setDeleted(const bool& state);

	/**
	 * Actualiza el nombre del archivo.
	 * @param name Nombre a asignarle al archivo.
	 */
	void setName(const std::string& name);

	/**
	 * Actualiza la extensión del archivo.
	 * @param extension Extensión a asignarle al archivo.
	 */
	void setExtension(const std::string& extension);

	/**
	 * Actualiza las etiquetas del archivo.
	 * @param labels Etiquetas a asignarle al archivo.
	 */
	void setLabels(const std::vector<std::string> &labels);

	/**
	 * Agrega un usuario al archivo, indicando que tiene privilegios sobre el mismo.
	 * @param user Usuario con el que se comparte el archivo.
	 */
	void addUser(User *user);

	/**
	 * Elimina los privilegios de un usuario sobre el archivo.
	 * @param user Usuario con el que no se comparte más el archivo.
	 */
	void removeUser(const User& user);

	/**
	 * @return Json del archivo.
	 */
	Json::Value getJson() const;

	/**
	 * @return String del json del archivo.
	 */
	std::string getJsonString() const;

};


#endif
