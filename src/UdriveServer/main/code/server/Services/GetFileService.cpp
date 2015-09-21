#include "../../../include/server/Services/GetFileService.h"
#include "../../../include/server/HttpResponse.h"
#include "../../../include/resources/User.h"
#include "../../../include/resources/File.h"
#include "../../../include/resources/Version.h"
#include "../../../others/json/json.h"


GetFileService::GetFileService(Database &userDB, Database &fileDB, Database &dataDB) : userDB(userDB), fileDB(fileDB), dataDB(dataDB){
}

GetFileService::~GetFileService(){
}

std::string GetFileService::execute(const std::string& username, const std::string& token, const std::string& data) const{
	std::string response = "";
	std::string userJsonString = this->userDB.getValue(username);
	if (userJsonString != ""){
		User user(userJsonString);
		if (user.authenticateToken(token)){

			//get fisico
			if (data.find("version=") != std::string::npos){
				std::string query("version=");
				std::string queryVersion = data.substr(data.find(query)+query.length());
				query = "idFile=";
				std::string queryIdFile = data.substr(data.find(query)+query.length(), data.find("&version=")-data.find(query)-query.length());
				std::string queryIdVersion = queryIdFile + "_" + queryVersion;
				std::string versionData = this->dataDB.getValue(queryIdVersion);

				if (versionData != ""){
					Version version(queryIdVersion, versionData);
					response = HttpResponse::GetHttpOkResponse(version.getJson());
				}
				else
					response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_INVALID_FILE_VERSION);
			}

			//get logico
			else{
				std::string query("idFile=");
				std::string queryIdFile = data.substr(data.find(query)+query.length());
				std::string fileQueryJsonString = this->fileDB.getValue(queryIdFile);
				if (fileQueryJsonString != ""){
					File queryFile(fileQueryJsonString, this->userDB);
					response = HttpResponse::GetHttpOkResponse(queryFile.getJson());
				}
				else
					response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_INVALID_FILE);
			}
		}
		else
			response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_AUTHENTICATION);
	}
	else
		response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_AUTHENTICATION);

	return response;
}
