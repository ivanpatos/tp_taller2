#include "../../include/server/CreateUserService.h"
#include "../../include/server/HttpResponse.h"
#include "../../include/database/DataManager.h"
#include "../../include/resources/User.h"
#include "../../others/json/json.h"


CreateUserService::CreateUserService(){
}

CreateUserService::~CreateUserService(){
}

bool CreateUserService::initUserFolders(const User& user) const{
	std::string username = user.getUsername();
	Json::Value json;

	json["id"] = username;
	json["name"] = "root";
	Folder *rootFolder = new Folder(json);
	if (!DataManager::Instance().saveFolder(*rootFolder))
		return false;

	json["id"] = "sharedwith_" + username;
	json["name"] = "sharedwith";
	Folder *sharedWithFolder = new Folder(json);
	if (!DataManager::Instance().saveFolder(*sharedWithFolder))
		return false;

	json["id"] = "trash_" + username;
	json["name"] = "trash";
	Folder *trashFolder = new Folder(json);
	if (!DataManager::Instance().saveFolder(*trashFolder))
		return false;


	json["id"] = "recovered_" + username;
	json["name"] = "recovered";
	Folder *recoveredFolder = new Folder(json);
	if (!DataManager::Instance().saveFolder(*recoveredFolder))
		return false;

	return true;
}

std::string CreateUserService::execute(const std::string& username, const std::string& token, const std::string& data) const{
	std::string response = "";
	Json::Value jsonData;
	Json::Reader reader;
	reader.parse(data, jsonData);

	User user(jsonData);
	User *userQuery = DataManager::Instance().getUser(user.getUsername());
	if (userQuery != NULL){
		delete userQuery;
		response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_USERNAME_EXISTS);
	}
	else{
		if (user.getUsername() == "")
			response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_USERNAME_MISSING);
		else if (user.getPassword() == "")
			response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_PASSWORD_MISSING);
		else{
			user.generateToken();
			if (DataManager::Instance().saveUser(user) && this->initUserFolders(user))
				response = HttpResponse::GetHttpOkResponse(user.getJsonProfile());
			else
				response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_SAVING_DATA);
		}
	}
	return response;
}


const std::string CreateUserServiceCreator::resource = "user";
const std::string CreateUserServiceCreator::method = "POST";


Service* CreateUserServiceCreator::create() const{
	return new CreateUserService();
}

std::string CreateUserServiceCreator::getResource() const{
	return this->resource;
}

std::string CreateUserServiceCreator::getMethod() const{
	return this->method;
}
