#include "../../../include/server/Services/LoginService.h"
#include "../../../include/server/HttpResponse.h"
#include "../../../include/resources/User.h"
#include "../../../others/json/json.h"


LoginService::LoginService(Database &userDB) : userDB(userDB){
}

LoginService::~LoginService(){
}

const char* LoginService::name() const{
	return "LoginService";
}
std::string LoginService::execute(const std::string& username, const std::string& token, const std::string& data, const std::string& query) const{

	std::string response = "";
	Json::Value jsonData;
	Json::Reader reader;
	reader.parse(data, jsonData);

	std::string userJsonString = this->userDB.getValue(jsonData.get("username", "").asCString());
	if (userJsonString != ""){
		User user(userJsonString);
		if (user.getPassword() == jsonData.get("password", "").asCString()){
			user.generateToken();
			if (this->userDB.saveValue(user.getUsername(), user.getJsonString())) {
				response = HttpResponse::GetHttpOkResponse(user.getJsonProfileWithToken());
				LOG(INFO) << "Usuario se loggeo en la app: " + user.getUsername() + " token:" + user.getToken() ;
			}
			else
				response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_SAVING_DATA);
		}
		else
			response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_INVALID_PASSWORD);
	}
	else
		response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_INVALID_USERNAME);

	return response;
}
