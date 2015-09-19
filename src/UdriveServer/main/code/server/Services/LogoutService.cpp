#include "../../../include/server/Services/LogoutService.h"
#include "../../../include/server/HttpResponse.h"
#include "../../../include/resources/User.h"
#include "../../../others/json/json.h"


LogoutService::LogoutService(Database &userDB) : userDB(userDB){
}

LogoutService::~LogoutService(){
}

std::string LogoutService::execute(const std::string& username, const std::string& token, const std::string& data) const{

	std::string response = "";
	std::string userJsonString = this->userDB.getValue(username);
	if (userJsonString != ""){
		User user(userJsonString);
		if (user.authenticateToken(token)){
			user.generateToken();
			if (this->userDB.saveValue(user.getUsername(), user.getJsonString()))
				response = HttpResponse::GetHttpOkResponse("");
			else
				response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_SAVING_DATA);
		}
		else
			response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_AUTHENTICATION);
	}
	else
		response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_AUTHENTICATION);

	return response;
}
