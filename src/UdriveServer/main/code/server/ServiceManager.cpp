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
	std::hash<std::string> hasher;
	std::stringstream stringStream;
	stringStream << hasher(tokenSource);
	std::string token = stringStream.str();
	user->setToken(token);
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

std::string ServiceManager::createUser(const std::string& data){

	std::string response = "";
	Json::Value jsonData(Json::objectValue);
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
		else if (DataManager::Instance().saveUser(user))
			response = HttpResponse::GetHttpOkResponse(user.getJsonProfile());
		else
			response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_SAVING_DATA);
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
