#include "../../../include/server/Services/UpdateFileService.h"
#include "../../../include/server/HttpResponse.h"
#include "../../../include/resources/User.h"
#include "../../../include/resources/File.h"
#include "../../../include/resources/Version.h"
#include "../../../others/json/json.h"
#include <sstream>


UpdateFileService::UpdateFileService(Database &userDB, Database &fileDB, Database &dataDB) : userDB(userDB), fileDB(fileDB), dataDB(dataDB){
}

UpdateFileService::~UpdateFileService(){
}

std::string UpdateFileService::execute(const std::string& username, const std::string& token, const std::string& data, const std::string& query) const{
	std::string response = "";
	std::string userJsonString = this->userDB.getValue(username);
	if (userJsonString != ""){
		User user(userJsonString);
		if (user.authenticateToken(token)){

			//solo update fisico por ahora

			Json::Value jsonData;
			Json::Reader reader;
			reader.parse(data, jsonData);

			std::string queryKey("idFile=");
			std::string fileId = query.substr(query.find(queryKey)+queryKey.length());
			std::string fileJsonString = this->fileDB.getValue(fileId);

			if (fileJsonString != ""){
				File file(fileJsonString, this->userDB);
				if (file.isSharedWith(user)){
					file.increaseVersion();

					std::ostringstream ss;
					ss << file.getVersion();

					std::string idVersion = file.getId() + "_" + ss.str();
					Version version(idVersion, jsonData.get("data", "").asCString());

					if (this->fileDB.saveValue(file.getId(), file.getJsonString()) && this->dataDB.saveValue(version.getId(), version.getData()))
						response = HttpResponse::GetHttpOkResponse(file.getJson());
					else
						response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_SAVING_DATA);
				}
				else
					response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_FILE_NOT_SHARED_WITH);
			}
			else
				response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_INVALID_FILE);
		}
		else
			response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_AUTHENTICATION);
	}
	else
		response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_AUTHENTICATION);

	return response;
}
