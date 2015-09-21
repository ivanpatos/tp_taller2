#include "../../../include/server/Services/CreateFolderService.h"
#include "../../../include/server/HttpResponse.h"
#include "../../../include/resources/Folder.h"
#include "../../../include/resources/User.h"
#include "../../../others/json/json.h"


CreateFolderService::CreateFolderService(Database &userDB, Database &folderDB, Database &fileDB) : userDB(userDB), folderDB(folderDB), fileDB(fileDB){
}

CreateFolderService::~CreateFolderService(){
}

std::string CreateFolderService::execute(const std::string& username, const std::string& token, const std::string& data, const std::string& query) const{
	std::string response = "";
	std::string userJsonString = this->userDB.getValue(username);
	if (userJsonString != ""){
		User user(userJsonString);
		if (user.authenticateToken(token)){
			Json::Value jsonData;
			Json::Reader reader;
			reader.parse(data, jsonData);

			std::string folderParentJsonString = this->folderDB.getValue(jsonData.get("idParent", "").asCString());
			if (folderParentJsonString == "")
				response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_INVALID_FOLDER_PARENT);
			else{
				Folder folderParent(folderParentJsonString, this->userDB, this->folderDB, this->fileDB);
				if (folderParent.hasFolder(jsonData.get("name", "").asCString()))
					response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_FOLDER_NAME_EXISTS);
				else{
					jsonData["id"] = folderParent.getId()+"/"+jsonData.get("name", "").asCString();
					Folder *folder = new Folder(jsonData);
					folderParent.addFolderChildren(folder);
					if (this->folderDB.saveValue(folder->getId(), folder->getJsonString()) && this->folderDB.saveValue(folderParent.getId(), folderParent.getJsonString()))
						response = HttpResponse::GetHttpOkResponse(folder->getJson());
					else
						response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_SAVING_DATA);
				}
			}
		}
		else
			response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_AUTHENTICATION);
	}
	else
		response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_AUTHENTICATION);

	return response;
}
