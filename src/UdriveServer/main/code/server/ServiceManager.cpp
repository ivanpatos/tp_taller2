#include <tr1/functional>
#include "../../include/server/ServiceManager.h"
#include "../../include/server/HttpResponse.h"
#include "../../include/utilities/Time.h"
#include "../../include/database/DataManager.h"
#include "../../others/json/json.h"


ServiceManager::ServiceManager(){
}

ServiceManager::~ServiceManager(){
}

bool ServiceManager::authenticateRequest(const User& user, const std::string& token){
	if (user.getToken().compare(token) == 0)
		return true;
	else
		return false;
}

void ServiceManager::generateToken(User *user){
	std::string tokenSource = user->getUsername() + user->getPassword() + Time::getCurrentTime();
	std::tr1::hash<std::string> hasher;
	std::stringstream stringStream;
	stringStream << hasher(tokenSource);
	std::string token = stringStream.str();
	user->setToken(token);
}

bool ServiceManager::initUserFolders(const User& user){

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

std::string ServiceManager::login(const std::string& username, const std::string& password){
	std::string response = "";
	User *user = DataManager::Instance().getUser(username);
	if (user){
		if (user->getPassword() == password){
			this->generateToken(user);
			if (DataManager::Instance().saveUser(*user))
				response = HttpResponse::GetHttpOkResponse(user->getJsonProfileWithToken());
			else
				response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_SAVING_DATA);
		}
		else
			response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_INVALID_PASSWORD);
		delete user;
	}
	else
		response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_INVALID_USERNAME);

	return response;
}

std::string ServiceManager::logout(const std::string& username, const std::string& token){
	std::string response = "";
		User *user = DataManager::Instance().getUser(username);
		if (user){
			if (this->authenticateRequest(*user, token)){
				this->generateToken(user);
				if (DataManager::Instance().saveUser(*user))
					response = HttpResponse::GetHttpOkResponse("");
				else
					response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_SAVING_DATA);
			}
			else
				response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_AUTHENTICATION);
			delete user;
		}
		else
			response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_AUTHENTICATION);

		return response;
}

std::string ServiceManager::createUser(const std::string& data){

	std::string response = "";
	Json::Value jsonData;
	Json::Reader reader;
	reader.parse(data, jsonData);

	User user(jsonData);
	std::string username = user.getUsername();
	User *userQuery = DataManager::Instance().getUser(username);
	if (userQuery != NULL){
		delete userQuery;
		response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_USERNAME_EXISTS);
	}
	else{
		std::string password = user.getPassword();
		if (username == "")
			response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_USERNAME_MISSING);
		else if (password == "")
			response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_PASSWORD_MISSING);
		else{
			this->generateToken(&user);
			if (DataManager::Instance().saveUser(user) && this->initUserFolders(user))
				response = HttpResponse::GetHttpOkResponse(user.getJsonProfile());
			else
				response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_SAVING_DATA);
		}
	}
	return response;
}

std::string ServiceManager::getUser(const std::string& username, const std::string& token, const std::string& queryUsername){

	std::string response = "";
	User *user = DataManager::Instance().getUser(username);
	if (user){
		if (this->authenticateRequest(*user, token)){
			User *queryUser = DataManager::Instance().getUser(queryUsername);
			if (queryUser){
				Json::Value userProfileJson = queryUser->getJsonProfile();
				delete queryUser;
				response = HttpResponse::GetHttpOkResponse(userProfileJson);
			}
			else
				response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_INVALID_USERNAME);
		}
		else
			response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_AUTHENTICATION);
		delete user;
	}
	else
		response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_AUTHENTICATION);

	return response;
}

std::string ServiceManager::getAllUsers(const std::string& username, const std::string& token){

	std::string response = "";
	User *user = DataManager::Instance().getUser(username);
	if (user){
		if (this->authenticateRequest(*user, token)){

			Json::Value jsonUserList;
			std::vector<User*> userList = DataManager::Instance().getAllUsers();
			for(std::vector<User*>::iterator it = userList.begin(); it != userList.end(); ++it) {
				Json::Value userProfileJson = (*it)->getJsonProfile();
				jsonUserList.append(userProfileJson);
				delete *it;
			}

			response = HttpResponse::GetHttpOkResponse(jsonUserList);
		}
		else
			response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_AUTHENTICATION);
		delete user;
	}
	else
		response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_AUTHENTICATION);

	return response;
}

std::string ServiceManager::updateUser(const std::string& username, const std::string& token, const std::string& data){

	std::string response = "";
	User *user = DataManager::Instance().getUser(username);
	if (user){
		if (this->authenticateRequest(*user, token)){
			user->updateProfile(data);
			if (DataManager::Instance().saveUser(*user))
				response = HttpResponse::GetHttpOkResponse(user->getJsonProfile());
			else
				response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_SAVING_DATA);

		}
		else
			response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_AUTHENTICATION);
		delete user;
	}
	else
		response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_AUTHENTICATION);

	return response;
}

std::string ServiceManager::createFolder(const std::string& username, const std::string& token, const std::string& data){

	std::string response = "";
		User *user = DataManager::Instance().getUser(username);
		if (user){
			if (this->authenticateRequest(*user, token)){
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

std::string ServiceManager::getFolder(const std::string& username, const std::string& token, const std::string& queryIdFolder){
	std::string response = "";
	User *user = DataManager::Instance().getUser(username);
	if (user){
		if (this->authenticateRequest(*user, token)){
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
