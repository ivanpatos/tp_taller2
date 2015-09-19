#include "../../include/resources/Folder.h"
#include "../../include/database/DataManager.h"


Folder::Folder(const Json::Value& json){
	this->id = json.get("id", "").asCString();
	this->name = json.get("name", "").asCString();
}

Folder::Folder(const std::string& jsonString){
	Json::Value json;
	Json::Reader reader;
	reader.parse(jsonString, json);

	this->id = json.get("id", "").asCString();
	this->name = json.get("name", "").asCString();

	Json::Value jsonChildren = json["children"];
	for(Json::ValueIterator it = jsonChildren.begin() ; it != jsonChildren.end() ; it++) {
		std::string type = (*it).get("type", "").asCString();
		std::string id = (*it).get("id", "").asCString();
		if (type == "folder"){
			Folder *folder = DataManager::Instance().getFolder(id);
			if (folder != NULL)
				this->folderChildren.push_back(folder);
		}
		else{
			File *file = DataManager::Instance().getFile(id);
			if (file != NULL)
				this->fileChildren.push_back(file);
		}
	}
}

Folder::~Folder(){
	for(std::vector<File*>::iterator it = this->fileChildren.begin(); it != this->fileChildren.end(); ++it)
			delete *it;
	for(std::vector<Folder*>::iterator it = this->folderChildren.begin(); it != this->folderChildren.end(); ++it)
			delete *it;
}

std::string Folder::getId() const{
	return this->id;
}

std::string Folder::getName() const{
	return this->name;
}

Json::Value Folder::getJson() const{
	Json::Value json;
	json["id"] = this->id;
	json["name"] = this->name;

	if (this->fileChildren.size() < 1 && this->folderChildren.size() < 1)
		json["children"] = "";
	else{
		Json::Value jsonChildren;
		if (this->fileChildren.size() > 0){
			for(std::vector<File*>::const_iterator it = this->fileChildren.begin(); it != this->fileChildren.end(); ++it) {
				Json::Value jsonFile;
				jsonFile["type"] = "file";
				jsonFile["id"] = (*it)->getId();
				jsonFile["name"] = (*it)->getName();
				jsonFile["extension"] = (*it)->getExtension();
				jsonChildren.append(jsonFile);
			}
		}
		if (this->folderChildren.size() > 0){
			for(std::vector<Folder*>::const_iterator it = this->folderChildren.begin(); it != this->folderChildren.end(); ++it) {
				Json::Value jsonFolder;
				jsonFolder["type"] = "folder";
				jsonFolder["id"] = (*it)->getId();
				jsonFolder["name"] = (*it)->getName();
				jsonChildren.append(jsonFolder);
			}
		}
		json["children"] = jsonChildren;
	}
	return json;
}

std::string Folder::getJsonString() const{
	Json::Value json = this->getJson();
	Json::StreamWriterBuilder builder;
	builder.settings_["indentation"] = "\t";
	return Json::writeString(builder,json);
}

void Folder::addFolderChildren(Folder *folder){
	this->folderChildren.push_back(folder);
}

void Folder::addFileChildren(File *file){
	this->fileChildren.push_back(file);
}

bool Folder::hasFolder(const std::string& folderName) const{
	for(std::vector<Folder*>::const_iterator it = this->folderChildren.begin(); it != this->folderChildren.end(); ++it){
		if((*it)->getName() == folderName)
			return true;
	}
	return false;
}

bool Folder::hasFile(const std::string& fileName, const std::string& fileExtension) const{
	for(std::vector<File*>::const_iterator it = this->fileChildren.begin(); it != this->fileChildren.end(); ++it){
		if((*it)->getName() == fileName && (*it)->getExtension() == fileExtension)
			return true;
	}
	return false;
}

