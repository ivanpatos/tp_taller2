#include "../../include/server/GetUserService.h"
#include "../../include/server/HttpResponse.h"
#include "../../include/database/DataManager.h"
#include "../../include/resources/User.h"
#include "../../others/json/json.h"


GetUserService::GetUserService(){
}

GetUserService::~GetUserService(){
}

std::string GetUserService::execute(const std::string& username, const std::string& token, const std::string& data) const{
	std::string response = "";
	User *user = DataManager::Instance().getUser(username);
	if (user){
		if (user->authenticateToken(token)){
			if (data != ""){
				std::string query("username=");
				std::string queryUsername = data.substr(data.find(query)+query.length());
				User *queryUser = DataManager::Instance().getUser(queryUsername);
				if (queryUser){
					Json::Value userProfileJson = queryUser->getJsonProfile();
					delete queryUser;
					response = HttpResponse::GetHttpOkResponse(userProfileJson);
				}
				else
					response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_INVALID_USERNAME);
			}
			else{
				Json::Value jsonUserList;
				std::vector<User*> userList = DataManager::Instance().getAllUsers();
				for(std::vector<User*>::iterator it = userList.begin(); it != userList.end(); ++it) {
					Json::Value userProfileJson = (*it)->getJsonProfile();
					jsonUserList.append(userProfileJson);
					delete *it;
				}
				response = HttpResponse::GetHttpOkResponse(jsonUserList);
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


const std::string GetUserServiceCreator::resource = "user";
const std::string GetUserServiceCreator::method = "GET";


Service* GetUserServiceCreator::create() const{
	return new GetUserService();
}

std::string GetUserServiceCreator::getResource() const{
	return this->resource;
}

std::string GetUserServiceCreator::getMethod() const{
	return this->method;
}
