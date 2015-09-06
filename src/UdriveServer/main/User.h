#ifndef _USER_H_
#define _USER_H_

#include <string>
#include "json/json.h"


class User {

private:
	std::string username;
	std::string name;
	std::string mail;
	std::string profilePicture;
	std::string lastLocation;
	std::string password;
	std::string token;

public:
	User(const std::string& username, const std::string& name, const std::string& mail, const std::string& profilePicture, const std::string& password);
	User(const Json::Value& json);
	User(const std::string& jsonString);
	~User();

	void setToken(const std::string& token);
	std::string getUsername() const;
	std::string getPassword() const;
	std::string getToken() const;
	std::string getJsonString() const;				// devuelve string de json con todos los atributos
	Json::Value getJsonProfile() const;				// devuelve json sin password y token
	Json::Value getJsonProfileWithToken() const;	// devuelve json sin password


};


#endif
