#include "../../include/server/LoginService.h"
#include "../../include/server/HttpResponse.h"
#include "../../include/database/DataManager.h"
#include "../../include/resources/User.h"
#include "../../others/json/json.h"


LoginService::LoginService(){
}

LoginService::~LoginService(){
}

std::string LoginService::execute(const std::string& username, const std::string& token, const std::string& data) const{
	std::string response = "";
	Json::Value jsonData;
	Json::Reader reader;
	reader.parse(data, jsonData);

	User* user = DataManager::Instance().getUser(jsonData.get("username", "").asCString());
	if (user){
		if (user->getPassword() == jsonData.get("password", "").asCString()){
			user->generateToken();
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


const std::string LoginServiceCreator::resource = "login";
const std::string LoginServiceCreator::method = "POST";


Service* LoginServiceCreator::create() const{
	return new LoginService();
}

std::string LoginServiceCreator::getResource() const{
	return this->resource;
}

std::string LoginServiceCreator::getMethod() const{
	return this->method;
}
