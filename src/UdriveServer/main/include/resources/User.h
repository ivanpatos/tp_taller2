#ifndef _USER_H_
#define _USER_H_

#include <string>
#include "../../others/json/json.h"

/**
 * Define un usuario.
 */
class User {

private:
	std::string username;
	std::string name;
	std::string mail;
	std::string profilePicture;
	std::string lastLocation;
	std::string password;
	std::string token;
	int space;

public:
	/**
	 * Inicializa un usuario a partir de un json.
	 * @param json Json del usuario a crear.
	 */
	User(const Json::Value& json);

	/**
	 * Inicializa un usuario a partir de un json en forma de cadena de caracteres.
	 * @param jsonString String del json del usuario a crear.
	 */
	User(const std::string& jsonString);
	~User();

	/**
	 * Actualiza el token del usuario.
	 * @param token String del token a setear.
	 */
	void setToken(const std::string& token);

	/**
	 * @return Devuelve el username del usuario.
	 */
	std::string getUsername() const;

	/**
	 * @return Devuelve el password del usuario.
	 */
	std::string getPassword() const;

	/**
	 * @return Devuelve el token del usuario.
	 */
	std::string getToken() const;

	/**
	 * @return Devuelve el mail del usuario.
	 */
	std::string getEmail() const;

	/**
	 * @return Devuelve el espacio de servidor utilizado por el usuario.
	 */
	int getSpace() const;

	/**
	 * Setea el username del usuario.
	 * @param str Username a asignarle al usuario.
	 */
	void setUserName(const std::string& str);

	/**
	 * Setea el password del usuario.
	 * @param str Password a asignarle al usuario.
	 */
	void setPassword(const std::string& str);

	/**
	 * Setea el espacio a utilizar por el usuario.
	 * @param space Espacio a asignarle al usuario.
	 */
	void setSpace(const int& space);

	/**
	 * @return Devuelve json en formato string con todos los atributos.
	 */
	std::string getJsonString() const;

	/**
	 * @return Devuelve json sin password y token.
	 */
	Json::Value getJsonProfile() const;

	/**
	 * @return Devuelve json sin password.
	 */
	Json::Value getJsonProfileWithToken() const;

	/**
	 * Actualiza profile del usuario a partir de json en formato string.
	 * @param space Espacio a asignarle al usuario.
	 */
	void updateProfile(const std::string& jsonString);

	/**
	 * Genera y asigna un nuevo token al usuario.
	 */
	void generateToken();

	/**
	 * Verifica si el token pasado coincide con el token del usuario.
	 * @param token Token a comparar.
	 */
	bool authenticateToken(const std::string& token) const;
};


#endif
