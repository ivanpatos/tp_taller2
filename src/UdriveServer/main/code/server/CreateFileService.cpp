#include "../../include/server/CreateFileService.h"
#include "../../include/server/HttpResponse.h"
#include "../../include/database/DataManager.h"
#include "../../include/resources/Folder.h"
#include "../../include/resources/User.h"
#include "../../include/utilities/Time.h"
#include "../../others/json/json.h"


CreateFileService::CreateFileService(){
}

CreateFileService::~CreateFileService(){
}

std::string CreateFileService::execute(const std::string& username, const std::string& token, const std::string& data) const{
	std::string response = "";
	User *user = DataManager::Instance().getUser(username);
	if (user){
		if (user->authenticateToken(token)){
			Json::Value jsonData;
			Json::Reader reader;
			reader.parse(data, jsonData);
			Folder *folder = DataManager::Instance().getFolder(jsonData.get("idFolder", "").asCString());
			if (folder == NULL)
				response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_INVALID_FOLDER_PARENT);
			else{
				if (folder->hasFile(jsonData.get("name", "").asCString(),jsonData.get("extension", "").asCString()))
					response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_FILE_EXISTS);
				else{
					jsonData["username"] = user->getUsername();
					File *file = new File(jsonData);
					folder->addFileChildren(file);
					std::string idVersion = file->getId() + "_1";
					Version *version = new Version(idVersion,jsonData.get("data", "").asCString());

					if (DataManager::Instance().saveFile(*file) && DataManager::Instance().saveVersion(*version) && DataManager::Instance().saveFolder(*folder))
						response = HttpResponse::GetHttpOkResponse(file->getJson());
					else
						response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_SAVING_DATA);
					delete folder;
					delete version;
				}
			}
		}
		else
			response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_AUTHENTICATION);
		delete user;
	}
	else
		response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_AUTHENTICATION);

	return response;
}


const std::string CreateFileServiceCreator::resource = "file";
const std::string CreateFileServiceCreator::method = "POST";


Service* CreateFileServiceCreator::create() const{
	return new CreateFileService();
}

std::string CreateFileServiceCreator::getResource() const{
	return this->resource;
}

std::string CreateFileServiceCreator::getMethod() const{
	return this->method;
}
