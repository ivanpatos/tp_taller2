#include "../../../include/server/Services/UpdateFolderService.h"
#include "../../../include/server/Services/UpdateFileService.h"
#include "../../../include/server/HttpResponse.h"
#include "../../../include/resources/User.h"
#include "../../../include/resources/File.h"
#include "../../../others/json/json.h"


UpdateFolderService::UpdateFolderService(Database &userDB, Database &folderDB, Database &fileDB, Database &dataDB) : userDB(userDB), folderDB(folderDB), fileDB(fileDB), dataDB(dataDB){
}

UpdateFolderService::~UpdateFolderService(){
}

const char* UpdateFolderService::name() const{
	return "UpdateFolderService";
}

void UpdateFolderService::updateAllTree(Folder *folder, const std::string& username, const std::string& token, const std::string& data, const std::string& query) const{

	std::vector<File*> fileChildren = folder->getFileChildren();
	for(std::vector<File*>::const_iterator it = fileChildren.begin(); it != fileChildren.end(); ++it){

		Json::Value jsonFile = (*it)->getJson();
		Json::Value jsonData;
		Json::Reader reader;
		reader.parse(data, jsonData);
		jsonFile["users"] = jsonData["users"];

		Json::StreamWriterBuilder builder;
		builder.settings_["indentation"] = "\t";
		std::string jsonStringFile = Json::writeString(builder,jsonFile);

		UpdateFileService updateFileService(this->userDB, this->folderDB, this->fileDB, this->dataDB);
		std::string response = updateFileService.execute(username, token, jsonStringFile, (*it)->getId());
	}
	std::vector<Folder*> folderChildren = folder->getFolderChildren();
	for(std::vector<Folder*>::const_iterator it = folderChildren.begin(); it != folderChildren.end(); ++it)
		this->updateAllTree(*it, username, token, data, query);
}


std::string UpdateFolderService::execute(const std::string& username, const std::string& token, const std::string& data, const std::string& query) const{
	std::string response = "";
	std::string userJsonString = this->userDB.getValue(username);
	if (userJsonString != ""){
		User user(userJsonString);
		if (user.authenticateToken(token)){

			std::string folderId = query;
			std::string folderJsonString = this->folderDB.getValue(folderId);
			if (folderJsonString != ""){

				Json::Value jsonData;
				Json::Reader reader;
				reader.parse(data, jsonData);

				std::string folderParentId = query.substr(0, query.find_last_of("/"));
				std::string folderParentJsonString = this->folderDB.getValue(folderParentId);
				Folder folderParent(folderParentJsonString, this->userDB, this->folderDB, this->fileDB);
				Folder *folder = new Folder(folderJsonString, this->userDB, this->folderDB, this->fileDB);

				if (!folderParent.hasFolder(jsonData.get("name", "").asCString()))
					folder->setName(jsonData.get("name", "").asCString());
				this->updateAllTree(folder, username, token, data, query);
				if (this->folderDB.saveValue(folder->getId(), folder->getJsonString()))
					response = HttpResponse::GetHttpOkResponse(folder->getJson());
				else
					response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_SAVING_DATA);

				delete folder;
			}
			else
				response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_INVALID_FOLDER);
		}
		else
			response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_AUTHENTICATION);
	}
	else
		response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_AUTHENTICATION);

	return response;
}
