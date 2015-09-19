#include "../../include/server/UpdateUserService.h"
#include "../../include/server/HttpResponse.h"
#include "../../include/database/DataManager.h"
#include "../../include/resources/User.h"
#include "../../others/json/json.h"


UpdateUserService::UpdateUserService(){
}

UpdateUserService::~UpdateUserService(){
}

std::string UpdateUserService::execute(const std::string& username, const std::string& token, const std::string& data) const{
	std::string response = "";
	User *user = DataManager::Instance().getUser(username);
	if (user){
		if (user->authenticateToken(token)){
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


const std::string UpdateUserServiceCreator::resource = "user";
const std::string UpdateUserServiceCreator::method = "PUT";


Service* UpdateUserServiceCreator::create() const{
	return new UpdateUserService();
}

std::string UpdateUserServiceCreator::getResource() const{
	return this->resource;
}

std::string UpdateUserServiceCreator::getMethod() const{
	return this->method;
}
