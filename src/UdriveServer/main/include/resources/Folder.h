#ifndef _FOLDER_H_
#define _FOLDER_H_

#include <string>
#include "../../others/json/json.h"
#include "../database/Database.h"
#include "File.h"

/**
 * Define una carpeta.
 */
class Folder{

private:
	std::string id;
	std::string name;
	std::vector<File*> fileChildren;
	std::vector<Folder*> folderChildren;

public:
	/**
	 * Inicializa una carpeta a partir de un json.
	 * @param json Json de la carpeta a crear.
	 */
	Folder(const Json::Value& json);

	/**
	 * Inicializa una carpeta a partir de un json en forma de cadena de caracteres.
	 * @param jsonString String del json de la carpeta a crear.
	 * @param userDB Base de datos de usuarios.
	 * @param folderDB Base de datos de carpetas.
	 * @param fileDB Base de datos de archivos.
	 */
	Folder(const std::string& jsonString, Database &userDB, Database &folderDB, Database &fileDB);
	~Folder();

	/**
	 * @return Id de la carpeta.
	 */
	std::string getId() const;

	/**
	 * @return Nombre de la carpeta.
	 */
	std::string getName() const;

	/**
	 * @return Vector con todas las carpetas que contiene la carpeta.
	 */
	std::vector<Folder*> getFolderChildren() const;

	/**
	 * @return Vector con todos los archivos que contiene la carpeta.
	 */
	std::vector<File*> getFileChildren() const;

	/**
	 * @return Json de la carpeta.
	 */
	Json::Value getJson() const;

	/**
	 * @return String del json de la carpeta.
	 */
	std::string getJsonString() const;

	/**
	 * Actualiza el nombre de la carpeta.
	 * @param name Nombre a setear.
	 */
	void setName(const std::string& name);

	/**
	 * Agrega una carpeta hija a la carpeta.
	 * @param folder Carpeta hija a agregar.
	 */
	void addFolderChildren(Folder *folder);

	/**
	 * Agrega un archivo hijo a la carpeta.
	 * @param file Archivo hijo a agregar.
	 */
	void addFileChildren(File *file);

	/**
	 * Elimina un archivo hijo de la carpeta.
	 * @param file Archivo hijo a eliminar.
	 */
	void removeFileChildren(File *file);

	/**
	 * Verifica si la carpeta contiene una carpeta con el nombre folderName.
	 * @param folderName Nombre de la carpeta a verificar si es contenida por la carpeta.
	 */
	bool hasFolder(const std::string& folderName) const;

	/**
	 * Verifica si la carpeta contiene un archivo con el nombre fileName y extensión fileExtension.
	 * @param fileName Nombre del archivo a verificar si es contenido por la carpeta.
	 * @param fileExtension Extensión del archivo a verificar si es contenido por la carpeta.
	 */
	bool hasFile(const std::string& fileName, const std::string& fileExtension) const;

};


#endif
