#ifndef _USER_H_
#define _USER_H_

#include "json/json.h"

using namespace std;

class User {

private:
	string username;
	string name;
	string mail;
	string profilePicture;
	string lastLocation;
	string password;
	string token;

public:
	User(const string& username, const string& name, const string& mail, const string& profilePicture, const string& password);
	User(const Json::Value& json);
	User(const string& jsonString);
	~User();

	string getUsername() const;
	string getPassword() const;
	string getToken() const;
	string getJsonString() const;				// devuelve string de json con todos los atributos
	Json::Value getJsonProfile() const;			// devuelve json sin password y token


};


#endif
