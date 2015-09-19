#include "../../include/resources/File.h"
#include "../../include/utilities/Time.h"


File::File(const Json::Value& json, Database &userDB){

	std::string username = json.get("username", "").asCString();
	this->id = username + Time::getCurrentTime();
	this->owner = new User(userDB.getValue(username));
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
		json["labels"] = "";

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
		json["users"] = "";
	return json;
}

std::string File::getJsonString() const{
	Json::Value json = this->getJson();
	Json::StreamWriterBuilder builder;
	builder.settings_["indentation"] = "\t";
	return Json::writeString(builder,json);
}
