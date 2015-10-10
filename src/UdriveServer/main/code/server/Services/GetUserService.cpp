#include "../../../include/server/Services/GetUserService.h"
#include "../../../include/server/HttpResponse.h"
#include "../../../include/resources/User.h"
#include "../../../others/json/json.h"


GetUserService::GetUserService(Database &userDB) : userDB(userDB){
}

GetUserService::~GetUserService(){
}

const char* GetUserService::name() const{
	return "GetUserService";
}

std::string GetUserService::execute(const std::string& username, const std::string& token, const std::string& data, const std::string& query) const{
	std::string response = "";
	std::string userJsonString = this->userDB.getValue(username);
	if (userJsonString != ""){
		User user(userJsonString);
		if (user.authenticateToken(token)){
			if (query != ""){
				std::string queryUsername = query;
				std::string userQueryJsonString = this->userDB.getValue(queryUsername);
				if (userQueryJsonString != ""){
					User userQuery(userQueryJsonString);
					Json::Value userProfileJson = userQuery.getJsonProfile();
					response = HttpResponse::GetHttpOkResponse(userProfileJson);
				}
				else
					response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_INVALID_USERNAME);
			}
			else{
				Json::Value jsonUserList;
				std::vector<std::string> userJsonStringList = this->userDB.getAllValues();
				for(std::vector<std::string>::iterator it = userJsonStringList.begin(); it != userJsonStringList.end(); ++it) {
					User userVector(*it);
					Json::Value userProfileJson = userVector.getJsonProfile();
					jsonUserList.append(userProfileJson);
				}
				response = HttpResponse::GetHttpOkResponse(jsonUserList);
			}
		}
		else
			response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_AUTHENTICATION);
	}
	else
		response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_AUTHENTICATION);

	return response;
}
