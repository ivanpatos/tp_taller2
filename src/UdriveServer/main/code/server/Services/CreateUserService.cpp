#include "../../../include/server/Services/CreateUserService.h"
#include "../../../include/server/HttpResponse.h"
#include "../../../include/resources/User.h"
#include "../../../include/resources/Folder.h"
#include "../../../others/json/json.h"


CreateUserService::CreateUserService(Database &userDB, Database &folderDB) : userDB(userDB), folderDB(folderDB){
}

CreateUserService::~CreateUserService(){
}

const char* CreateUserService::name() const{
	return "CreateUserService";
}
bool CreateUserService::initUserFolders(const User& user) const{
	std::string username = user.getUsername();
	Json::Value json;

	json["id"] = username;
	json["name"] = "root";
	Folder rootFolder(json);
	if (!this->folderDB.saveValue(rootFolder.getId(), rootFolder.getJsonString()))
		return false;

	json["id"] = "sharedwith_" + username;
	json["name"] = "sharedwith";
	Folder sharedWithFolder(json);
	if (!this->folderDB.saveValue(sharedWithFolder.getId(), sharedWithFolder.getJsonString()))
			return false;

	json["id"] = "trash_" + username;
	json["name"] = "trash";
	Folder trashFolder(json);
	if (!this->folderDB.saveValue(trashFolder.getId(), trashFolder.getJsonString()))
			return false;


	json["id"] = "recovered_" + username;
	json["name"] = "recovered";
	Folder recoveredFolder(json);
	if (!this->folderDB.saveValue(recoveredFolder.getId(), recoveredFolder.getJsonString()))
			return false;


	return true;
}

std::string CreateUserService::execute(const std::string& username, const std::string& token, const std::string& data, const std::string& query) const{
	std::string response = "";
	Json::Value jsonData;
	Json::Reader reader;
	reader.parse(data, jsonData);

	User user(jsonData);
	if (this->userDB.getValue(user.getUsername()) != "")
		response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_USERNAME_EXISTS);
	else{
		if (user.getUsername() == "")
			response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_USERNAME_MISSING);
		else if (user.getPassword() == "")
			response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_PASSWORD_MISSING);
		else{
			user.generateToken();
			if (this->userDB.saveValue(user.getUsername(), user.getJsonString()) && this->initUserFolders(user))
				response = HttpResponse::GetHttpOkResponse(user.getJsonProfileWithToken());
			else
				response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_SAVING_DATA);
		}
	}
	return response;
}

