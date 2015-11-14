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
	this->space = 1073741824;
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
	this->space = json.get("space", 0).asInt();
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

std::string User::getEmail() const{
	return this->mail;
}

int User::getSpace() const{
	return this->space;
}

void User::setUserName(const std::string& str){
	this->username = str;
}

void User::setPassword(const std::string& str){
	this->password = str;
}

void User::setSpace(const int& space){
	this->space = space;
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
	json["space"] = this->space;
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
}

void User::generateToken(){
	std::string tokenSource = this->getUsername() + this->getPassword() + Time::getCurrentTime();
	std::tr1::hash<std::string> hasher;
	std::stringstream stringStream;
	stringStream << hasher(tokenSource);
	this->token = stringStream.str();
}

bool User::authenticateToken(const std::string& token) const{
	return (this->token.compare(token) == 0);
}
