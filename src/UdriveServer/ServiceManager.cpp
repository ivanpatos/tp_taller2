#include "ServiceManager.h"

ServiceManager::ServiceManager(){
}

ServiceManager::~ServiceManager(){
}

bool ServiceManager::authenticateRequest(const User& user, const string& token){
	if (user.getToken().compare(token) == 0)
		return true;
	else
		return false;
}

string ServiceManager::createUser(const string& data){

	string response = "";
	Json::Value jsonData(Json::objectValue);
	Json::Reader reader;
	reader.parse(data, jsonData);

	User user(jsonData);
	string username = user.getUsername();
	User *userQuery = DataManager::Instance().getUser(username);
	if (userQuery != NULL){
		delete userQuery;
		response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_USERNAME_EXISTS);
	}
	else{
		string password = user.getPassword();
		if (username == "")
			response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_USERNAME_MISSING);
		else if (password == "")
			response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_PASSWORD_MISSING);
		else if (DataManager::Instance().saveUser(user))
			response = HttpResponse::GetHttpOkResponse(user.getJsonProfile());
		else
			response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_SAVING_DB);
	}
	return response;
}

string ServiceManager::getUser(const string& username, const string& token, const string& queryUsername){

	string response = "";
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
		response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_INVALID_USERNAME);

	return response;
}
