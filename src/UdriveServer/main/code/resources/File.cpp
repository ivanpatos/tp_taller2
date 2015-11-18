#include "../../include/resources/File.h"


File::File(const Json::Value& json, Database &userDB){

	this->id = json.get("id", "").asCString();
	this->owner = new User(userDB.getValue(json.get("username", "").asCString()));
	this->name = json.get("name", "").asCString();
	this->deleted = false;
	this->lastModified = "",
	this->lastUser = NULL;
	this->extension = json.get("extension", "").asCString();
	this->version = 1;
	Json::Value labels = json.get("labels","");
	for(Json::ValueIterator it = labels.begin() ; it != labels.end() ; it++) {
		this->labels.push_back((*it)["description"].asString());
	}
}

File::File(const std::string& jsonString, Database &userDB){

	Json::Value json;
	Json::Reader reader;
	reader.parse(jsonString, json);

	this->id = json.get("id", "").asCString();
	this->name = json.get("name", "").asCString();
	this->deleted = json.get("deleted", "").asBool();
	this->lastModified = json.get("lastModified", "").asCString();
	this->extension = json.get("extension", "").asCString();
	this->version = json.get("version", "").asInt();

	this->owner= new User(userDB.getValue(json.get("owner", "").asCString()));
	this->lastUser= new User(userDB.getValue(json.get("lastUser", "").asCString()));

	Json::Value jsonLabels = json["labels"];
	for(Json::ValueIterator it = jsonLabels.begin() ; it != jsonLabels.end() ; it++) {
		std::string label = (*it).get("description", "").asCString();
		this->labels.push_back(label);
	}

	Json::Value jsonUsers = json["users"];
	for(Json::ValueIterator it = jsonUsers.begin() ; it != jsonUsers.end() ; it++) {
		User* user = new User(userDB.getValue((*it).get("username", "").asCString()));
		this->users.push_back(user);
	}
}

File::~File(){
	delete this->owner;
	if (this->lastUser != NULL)
		delete this->lastUser;
	for(std::vector<User*>::iterator it = this->users.begin(); it != this->users.end(); ++it)
		delete *it;
}

std::string File::getId() const{
	return this->id;
}

std::string File::getName() const{
	return this->name;
}

std::string File::getExtension() const{
	return this->extension;
}

bool File::getDeleted() const{
	return this->deleted;
}

int File::getVersion() const{
	return this->version;
}

User * File::getOwner() const{
	return this->owner;
}

std::vector<User*> File::getUsers() const{
	return this->users;
}

bool File::isOwner(const User& user) const{
	if (this->owner->getUsername() == user.getUsername())
			return true;
	return false;
}

void File::increaseVersion(){
	++this->version;
	LOG(TRACE) << this->id << " nueva version: " << this->version;
}

bool File::hasAnyLabel(const std::vector<std::string>& labels) const{
	for(std::vector<std::string>::const_iterator it = this->labels.begin(); it != this->labels.end(); ++it){
		for(std::vector<std::string>::const_iterator it2 = labels.begin(); it2 != labels.end(); ++it2){
			if (*it == *it2)
				return true;
		}
	}
	return false;
}

bool File::hasPermission(const User& user) const{
	if (this->owner->getUsername() == user.getUsername())
		return true;
	for(std::vector<User*>::const_iterator it = this->users.begin(); it != this->users.end(); ++it)
		if ((*it)->getUsername() == user.getUsername())
			return true;
	return false;
}

void File::setDeleted(const bool& state){
	this->deleted = state;
}

void File::setName(const std::string& name){
	this->name = name;
}

void File::setExtension(const std::string& extension){
	this->extension = extension;
}

void File::setLabels(const std::vector<std::string> &labels){
	this->labels = labels;
}

void File::addUser(User *user){
	this->users.push_back(user);
	LOG(TRACE) << this->id << " se agrego usuario: " << user->getUsername();
}

void File::removeUser(const User& user){
	bool fin = false;
	for(std::vector<User*>::iterator it = this->users.begin(); it != this->users.end() && !fin; ++it){
		if((*it)->getUsername() == user.getUsername()){
			LOG(TRACE) << this->id << " se removio usuario: " << (*it)->getUsername();
			delete *it;
			it = this->users.erase(it);
			fin = true;
		}
	}
}

Json::Value File::getJson() const{

	Json::Value json;
	json["id"] = this->id;
	json["name"] = this->name;
	json["deleted"] = this->deleted;
	json["lastModified"] = this->lastModified;
	json["extension"] = this->extension;
	json["version"] = this->version;
	json["owner"] = this->owner->getUsername();

	if (this->lastUser != NULL)
		json["lastUser"] = this->lastUser->getUsername();
	else
		json["lastUser"] = "";

	if (this->labels.size() > 0){
		Json::Value jsonLabels;
		for(std::vector<std::string>::const_iterator it = this->labels.begin(); it != this->labels.end(); ++it) {
			Json::Value jsonLabel;
			jsonLabel["description"] = *it;
			jsonLabels.append(jsonLabel);
		}
		json["labels"] = jsonLabels;
	}
	else
		json["labels"] = Json::Value(Json::arrayValue);

	if (this->users.size() > 0){
		Json::Value users;
		for(std::vector<User*>::const_iterator it = this->users.begin(); it != this->users.end(); ++it) {
			Json::Value jsonUser;
			jsonUser["username"] = (*it)->getUsername();
			users.append(jsonUser);
		}
		json["users"] = users;
	}
	else
		json["users"] = Json::Value(Json::arrayValue);
	return json;
}

std::string File::getJsonString() const{
	Json::Value json = this->getJson();
	Json::StreamWriterBuilder builder;
	builder.settings_["indentation"] = "\t";
	return Json::writeString(builder,json);
}

void File::setLastUser(User *user){
	this->lastUser = user;
}

void File::setLastModified(const std::string& lastModified){
	this->lastModified = lastModified;
}
