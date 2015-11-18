#include "../../include/resources/Folder.h"


Folder::Folder(const Json::Value& json){
	this->id = json.get("id", "").asCString();
	this->name = json.get("name", "").asCString();
}

Folder::Folder(const std::string& jsonString, Database &userDB, Database &folderDB, Database &fileDB){
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
			std::string folderChildJsonString = folderDB.getValue(id);
			if (folderChildJsonString != "")
				this->folderChildren.push_back(new Folder(folderChildJsonString, userDB, folderDB, fileDB));
		}
		else{
			std::string fileChildJsonString = fileDB.getValue(id);
			if (fileChildJsonString != "")
				this->fileChildren.push_back(new File(fileChildJsonString, userDB));
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

std::vector<Folder*> Folder::getFolderChildren() const{
	return this->folderChildren;
}

std::vector<File*> Folder::getFileChildren() const{
	return this->fileChildren;
}

Json::Value Folder::getJson() const{
	Json::Value json;
	json["id"] = this->id;
	json["name"] = this->name;

	if (this->fileChildren.size() < 1 && this->folderChildren.size() < 1)
		json["children"] = Json::Value(Json::arrayValue);
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

void Folder::setName(const std::string& name){
	this->name = name;
}

void Folder::addFolderChildren(Folder *folder){
	this->folderChildren.push_back(folder);
	LOG(TRACE) << this->id << " se agrego carpeta hija: " << folder->getName();
}

void Folder::addFileChildren(File *file){
	this->fileChildren.push_back(file);
	LOG(TRACE) << this->id + " se agrego archivo hijo: " + file->getName();
}

void Folder::removeFileChildren(File *file){
	bool fin = false;
	for(std::vector<File*>::iterator it = this->fileChildren.begin(); it != this->fileChildren.end() && !fin; ++it){
		if((*it)->getId() == file->getId()){
			LOG(TRACE) << this->id << " se removio archivo hijo: " << (*it)->getName();
			delete *it;
			it = this->fileChildren.erase(it);
			fin = true;
		}
	}
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

