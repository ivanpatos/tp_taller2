#include <tr1/functional>
#include "../../include/resources/User.h"
#include "../../include/utilities/Time.h"


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

void User::updateProfile(const std::string& jsonString){
	Json::Value json(Json::objectValue);
	Json::Reader reader;
	reader.parse(jsonString, json);
	this->name = json.get("name", "").asCString();
	this->mail = json.get("mail", "").asCString();
	this->profilePicture = json.get("profilePicture", "").asCString();
	this->lastLocation = json.get("lastLocation", "").asCString();
	this->password = json.get("password", "").asCString();
}

void User::generateToken(){
	std::string tokenSource = this->getUsername() + this->getPassword() + Time::getCurrentTime();
	std::tr1::hash<std::string> hasher;
	std::stringstream stringStream;
	stringStream << hasher(tokenSource);
	this->token = stringStream.str();
}

bool User::authenticateToken(const std::string& token){
	return (this->token.compare(token) == 0);
}
