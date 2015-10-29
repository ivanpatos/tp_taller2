#include "../../../include/server/Services/GetFileService.h"
#include "../../../include/server/HttpResponse.h"
#include "../../../include/resources/User.h"
#include "../../../include/resources/File.h"
#include "../../../include/resources/Folder.h"
#include "../../../include/resources/Version.h"
#include "../../../others/json/json.h"


GetFileService::GetFileService(Database &userDB,  Database &folderDB, Database &fileDB, Database &dataDB) : userDB(userDB), folderDB(folderDB), fileDB(fileDB), dataDB(dataDB){
}

GetFileService::~GetFileService(){
}

const char* GetFileService::name() const{
	return "GetFileService";
}

std::vector<std::string> getValueFromQuery(const std::string& queryString, const std::string& queryKey){
	std::string query = queryString;
	std::vector<std::string> output;
	while (query.find(queryKey) != std::string::npos){
		query = query.substr(query.find(queryKey)+queryKey.length());
		std::string value;
		if (query.find("&") != std::string::npos)
			value = query.substr(0, query.find("&"));
		else
			value = query;
		output.push_back(value);
	}
	if (output.empty())
		output.push_back("");
	return output;
}

void searchFiles(Folder *folder, const std::string& name, const std::string& extension, const std::vector<std::string>& labels, const std::string& owner, Json::Value& jsonFileList){
	std::vector<File*> fileChildren = folder->getFileChildren();
	for(std::vector<File*>::const_iterator it = fileChildren.begin(); it != fileChildren.end(); ++it){
		File* file = *it;
		if (file->getName()==name || file->getExtension()==extension || file->hasAnyLabel(labels) || file->getOwner()->getUsername()==owner)
			jsonFileList.append(file->getJson());
	}
	std::vector<Folder*> folderChildren = folder->getFolderChildren();
	for(std::vector<Folder*>::const_iterator it = folderChildren.begin(); it != folderChildren.end(); ++it)
		searchFiles(*it, name, extension, labels, owner, jsonFileList);
}

std::string GetFileService::execute(const std::string& username, const std::string& token, const std::string& data, const std::string& query) const{
	std::string response = "";
	std::string userJsonString = this->userDB.getValue(username);
	if (userJsonString != ""){
		User user(userJsonString);
		if (user.authenticateToken(token)){

			//get fisico
			if (query.find("version=") != std::string::npos){

				std::string queryKey("version=");
				std::string queryVersion = query.substr(query.find(queryKey)+queryKey.length());
				std::string queryIdFile = query.substr(0, query.find("?"));
				std::string queryIdVersion = queryIdFile + "_" + queryVersion;
				std::string versionData = this->dataDB.getValue(queryIdVersion);

				if (versionData != ""){
					Version version(queryIdVersion, versionData);
					Json::Value versionJson = version.getJson();
					File queryFile(this->fileDB.getValue(queryIdFile), this->userDB);
					versionJson["name"] = queryFile.getName();
					versionJson["extension"] = queryFile.getExtension();
					response = HttpResponse::GetHttpOkResponse(versionJson);
				}
				else
					response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_INVALID_FILE_VERSION);
			}

			//get logico, busqueda de varios archivos
			else if (query.find("?") != std::string::npos){

					std::string name = getValueFromQuery(query, "name=")[0];
					std::string extension = getValueFromQuery(query, "extension=")[0];
					std::vector<std::string> labels = getValueFromQuery(query, "label=");
					std::string owner = getValueFromQuery(query, "owner=")[0];

					Json::Value jsonFileList;

					std::string folderJsonString = this->folderDB.getValue(username);
					Folder *rootFolder = new Folder(folderJsonString, this->userDB, this->folderDB, this->fileDB);
					searchFiles(rootFolder, name, extension, labels, owner, jsonFileList);
					delete rootFolder;

					folderJsonString = this->folderDB.getValue("sharedwith_"+username);
					Folder *sharedwithFolder = new Folder(folderJsonString, this->userDB, this->folderDB, this->fileDB);
					searchFiles(sharedwithFolder, name, extension, labels, owner, jsonFileList);
					delete sharedwithFolder;

					folderJsonString = this->folderDB.getValue("recovered_"+username);
					Folder *recoveredFolder = new Folder(folderJsonString, this->userDB, this->folderDB, this->fileDB);
					searchFiles(recoveredFolder, name, extension, labels, owner, jsonFileList);
					delete recoveredFolder;

					if (!jsonFileList.empty())
						response = HttpResponse::GetHttpOkResponse(jsonFileList);
					else
						response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_NO_FILES_FOUND);
			}

			//get logico de un archivo
			else{
				std::string queryIdFile = query;
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
