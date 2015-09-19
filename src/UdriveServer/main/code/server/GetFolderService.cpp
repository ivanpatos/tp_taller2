#include "../../include/server/GetFolderService.h"
#include "../../include/server/HttpResponse.h"
#include "../../include/database/DataManager.h"
#include "../../include/resources/User.h"
#include "../../others/json/json.h"


GetFolderService::GetFolderService(){
}

GetFolderService::~GetFolderService(){
}

std::string GetFolderService::execute(const std::string& username, const std::string& token, const std::string& data) const{
	std::string response = "";
	User *user = DataManager::Instance().getUser(username);
	if (user){
		if (user->authenticateToken(token)){
			std::string query("idFolder=");
			std::string queryIdFolder = data.substr(data.find(query)+query.length());
			Folder *queryFolder = DataManager::Instance().getFolder(queryIdFolder);
			if (queryFolder){
				Json::Value folderJson = queryFolder->getJson();
				delete queryFolder;
				response = HttpResponse::GetHttpOkResponse(folderJson);
			}
			else
				response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_INVALID_FOLDER);
		}
		else
			response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_AUTHENTICATION);
		delete user;
	}
	else
		response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_AUTHENTICATION);

	return response;
}


const std::string GetFolderServiceCreator::resource = "folder";
const std::string GetFolderServiceCreator::method = "GET";


Service* GetFolderServiceCreator::create() const{
	return new GetFolderService();
}

std::string GetFolderServiceCreator::getResource() const{
	return this->resource;
}

std::string GetFolderServiceCreator::getMethod() const{
	return this->method;
}
