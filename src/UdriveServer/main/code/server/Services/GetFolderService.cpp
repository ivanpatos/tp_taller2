#include "../../../include/server/Services/GetFolderService.h"
#include "../../../include/server/HttpResponse.h"
#include "../../../include/resources/User.h"
#include "../../../include/resources/Folder.h"
#include "../../../others/json/json.h"


GetFolderService::GetFolderService(Database &userDB, Database &folderDB, Database &fileDB) : userDB(userDB), folderDB(folderDB), fileDB(fileDB){
}

GetFolderService::~GetFolderService(){
}

std::string GetFolderService::execute(const std::string& username, const std::string& token, const std::string& data, const std::string& query) const{
	std::string response = "";
	std::string userJsonString = this->userDB.getValue(username);
	if (userJsonString != ""){
		User user(userJsonString);
		if (user.authenticateToken(token)){
			std::string queryKey("idFolder=");
			std::string queryIdFolder = query.substr(query.find(queryKey)+queryKey.length());
			std::string folderQueryJsonString = this->folderDB.getValue(queryIdFolder);
			if (folderQueryJsonString != ""){
				Folder queryFolder(folderQueryJsonString, this->userDB, this->folderDB, this->fileDB);
				response = HttpResponse::GetHttpOkResponse(queryFolder.getJson());
			}
			else
				response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_INVALID_FOLDER);
		}
		else
			response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_AUTHENTICATION);
	}
	else
		response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_AUTHENTICATION);

	return response;
}
