#include "../../include/server/LogoutService.h"
#include "../../include/server/HttpResponse.h"
#include "../../include/database/DataManager.h"
#include "../../include/resources/User.h"
#include "../../others/json/json.h"


LogoutService::LogoutService(){
}

LogoutService::~LogoutService(){
}

std::string LogoutService::execute(const std::string& username, const std::string& token, const std::string& data) const{
	std::string response = "";
			User *user = DataManager::Instance().getUser(username);
			if (user){
				if (user->authenticateToken(token)){
					user->generateToken();
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


const std::string LogoutServiceCreator::resource = "logout";
const std::string LogoutServiceCreator::method = "POST";


Service* LogoutServiceCreator::create() const{
	return new LogoutService();
}

std::string LogoutServiceCreator::getResource() const{
	return this->resource;
}

std::string LogoutServiceCreator::getMethod() const{
	return this->method;
}
