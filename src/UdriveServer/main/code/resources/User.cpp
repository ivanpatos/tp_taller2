#include "../../include/resources/User.h"

User::User(const std::string& username, const std::string& name, const std::string& mail, const std::string& profilePicture, const std::string& password){
	this->username = username;
	this->name = name;
	this->mail = mail;
	this->profilePicture = profilePicture;
	this->lastLocation = "";
	this->password = password;
	this->token = "";
}

User::User(const Json::Value& json){
	this->username = json.get("username", "").asCString();
	this->name = json.get("name", "").asCString();
	this->mail = json.get("mail", "").asCString();
	this->profilePicture = json.get("profilePicture", "").asCString();
	this->lastLocation = "";
	this->password = json.get("password", "").asCString();
	this->token = "";
}

User::User(const std::string& jsonString){
	Json::Value json(Json::objectValue);
	Json::Reader reader;
	reader.parse(jsonString, json);
	this->username = json.get("username", "").asCString();
	this->name = json.get("name", "").asCString();
	this->mail = json.get("mail", "").asCString();
	this->profilePicture = json.get("profilePicture", "").asCString();
	this->lastLocation = json.get("lastLocation", "").asCString();
	this->password = json.get("password", "").asCString();
	this->token = json.get("token", "").asCString();
}

User::~User(){
}

void User::setToken(const std::string& token){
	this->token = token;
}

std::string User::getUsername() const{
	return this->username;
}

std::string User::getPassword() const{
	return this->password;
}

std::string User::getToken() const{
	return this->token;
}

std::string User::getJsonString() const{
	Json::Value json = this->getJsonProfile();
	json["password"] = this->password;
	json["token"] = this->token;
	Json::StreamWriterBuilder builder;
	builder.settings_["indentation"] = "\t";
	return Json::writeString(builder,json);
}

Json::Value User::getJsonProfile() const{
	Json::Value json = Json::Value();
	json["username"] = this->username;
	json["name"] = this->name;
	json["mail"] = this->mail;
	json["profilePicture"] = this->profilePicture;
	json["lastLocation"] = this->lastLocation;
	return json;
}

Json::Value User::getJsonProfileWithToken() const{
	Json::Value json = this->getJsonProfile();
	json["token"] = this->token;
	return json;
}
