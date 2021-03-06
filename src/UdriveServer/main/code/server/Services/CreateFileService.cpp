#include "../../../include/server/Services/CreateFileService.h"
#include "../../../include/server/HttpResponse.h"
#include "../../../include/resources/Folder.h"
#include "../../../include/resources/User.h"
#include "../../../include/resources/Version.h"
#include "../../../include/utilities/Time.h"
#include "../../../others/json/json.h"


CreateFileService::CreateFileService(Database &userDB, Database &folderDB, Database &fileDB, Database &dataDB) : userDB(userDB), folderDB(folderDB), fileDB(fileDB), dataDB(dataDB){
}

CreateFileService::~CreateFileService(){
}

const char* CreateFileService::name() const{
	return "CreateFileService";
}

std::string CreateFileService::execute(const std::string& username, const std::string& token, const std::string& data, const std::string& query) const{
	std::string response = "";
	std::string userJsonString = this->userDB.getValue(username);
	if (userJsonString != ""){
		User user(userJsonString);
		if (user.authenticateToken(token)){
			Json::Value jsonData;
			Json::Reader reader;
			reader.parse(data, jsonData);

			std::string folderJsonString = this->folderDB.getValue(jsonData.get("idFolder", "").asCString());
			if (folderJsonString == "")
				response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_INVALID_FOLDER_PARENT);
			else{
				Folder folder(folderJsonString, this->userDB, this->folderDB, this->fileDB);
				if (folder.hasFile(jsonData.get("name", "").asCString(),jsonData.get("extension", "").asCString()))
					response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_FILE_EXISTS);
				else{
					std::string dataString = jsonData.get("data", "").asCString();
					if (user.getSpace() < dataString.length())
						response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_NOT_ENOUGH_SPACE);
					else{
						user.setSpace(user.getSpace()-dataString.length());
						jsonData["username"] = user.getUsername();
						jsonData["id"] = folder.getId()+"/"+jsonData.get("name", "").asCString()+"."+jsonData.get("extension", "").asCString()+","+Time::getCurrentTime();
						File *file = new File(jsonData, this->userDB);
						folder.addFileChildren(file);
						std::string idVersion = file->getId() + "_1";
						Version version(idVersion, dataString);
						if (this->userDB.saveValue(user.getUsername(), user.getJsonString()) && this->fileDB.saveValue(file->getId(), file->getJsonString()) &&	this->dataDB.saveValue(version.getId(), version.getData()) && this->folderDB.saveValue(folder.getId(), folder.getJsonString()))
							response = HttpResponse::GetHttpOkResponse(file->getJson());
						else
							response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_SAVING_DATA);
					}
				}
			}
		}
		else
			response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_AUTHENTICATION);
	}
	else
		response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_AUTHENTICATION);

	return response;
}
