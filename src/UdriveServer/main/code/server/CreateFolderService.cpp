#include "../../include/server/CreateFolderService.h"
#include "../../include/server/HttpResponse.h"
#include "../../include/database/DataManager.h"
#include "../../include/resources/Folder.h"
#include "../../include/resources/User.h"
#include "../../include/utilities/Time.h"
#include "../../others/json/json.h"


CreateFolderService::CreateFolderService(){
}

CreateFolderService::~CreateFolderService(){
}

std::string CreateFolderService::execute(const std::string& username, const std::string& token, const std::string& data) const{
	std::string response = "";
	User *user = DataManager::Instance().getUser(username);
	if (user){
		if (user->authenticateToken(token)){
			Json::Value jsonData;
			Json::Reader reader;
			reader.parse(data, jsonData);
			Folder *folderParent = DataManager::Instance().getFolder(jsonData.get("idParent", "").asCString());
			if (folderParent == NULL)
				response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_INVALID_FOLDER_PARENT);
			else{
				if (folderParent->hasFolder(jsonData.get("name", "").asCString()))
					response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_FOLDER_NAME_EXISTS);
				else{
					jsonData["id"] = user->getUsername() + Time::getCurrentTime();
					Folder *folder = new Folder(jsonData);
					folderParent->addFolderChildren(folder);
					if (DataManager::Instance().saveFolder(*folder) && DataManager::Instance().saveFolder(*folderParent))
						response = HttpResponse::GetHttpOkResponse(folder->getJson());
					else
						response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_SAVING_DATA);
					delete folderParent;
				}
			}
		}
		else
			response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_AUTHENTICATION);
		delete user;
	}
	else
		response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_AUTHENTICATION);

	return response;
}


const std::string CreateFolderServiceCreator::resource = "folder";
const std::string CreateFolderServiceCreator::method = "POST";


Service* CreateFolderServiceCreator::create() const{
	return new CreateFolderService();
}

std::string CreateFolderServiceCreator::getResource() const{
	return this->resource;
}

std::string CreateFolderServiceCreator::getMethod() const{
	return this->method;
}
