#ifndef _USER_H_
#define _USER_H_

#include <string>
#include "../../others/json/json.h"


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
	User(const Json::Value& json);
	User(const std::string& jsonString);
	~User();

	void setToken(const std::string& token);
	std::string getUsername() const;
	std::string getPassword() const;
	std::string getToken() const;
	std::string getJsonString() const;					// devuelve string de json con todos los atributos
	Json::Value getJsonProfile() const;					// devuelve json sin password y token
	Json::Value getJsonProfileWithToken() const;		// devuelve json sin password
	void updateProfile(const std::string& jsonString);	// actualiza profile a partir de json string
	void generateToken();
	bool authenticateToken(const std::string& token) const;
	std::string getEmail() const;
	void setUserName(const std::string& str);
	void setPassword(const std::string& str);
};


#endif
