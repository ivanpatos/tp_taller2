#include "../../../include/server/Services/DeleteFolderService.h"
#include "../../../include/server/Services/DeleteFileService.h"
#include "../../../include/server/HttpResponse.h"
#include "../../../include/resources/User.h"
#include "../../../include/resources/File.h"
#include "../../../include/resources/Version.h"
#include "../../../others/json/json.h"


DeleteFolderService::DeleteFolderService(Database &userDB, Database &folderDB, Database &fileDB) : userDB(userDB), folderDB(folderDB), fileDB(fileDB){
}

DeleteFolderService::~DeleteFolderService(){
}

const char* DeleteFolderService::name() const{
	return "DeleteFolderService";
}

void DeleteFolderService::deleteAllTree(Folder *folder, const std::string& username, const std::string& token, const std::string& data, const std::string& query) const{
	std::vector<File*> fileChildren = folder->getFileChildren();
	for(std::vector<File*>::const_iterator it = fileChildren.begin(); it != fileChildren.end(); ++it){
		DeleteFileService deleteFileService(this->userDB, this->folderDB, this->fileDB);
		std::string response = deleteFileService.execute(username, token, data, "idFile="+(*it)->getId());
	}
	std::vector<Folder*> folderChildren = folder->getFolderChildren();
	for(std::vector<Folder*>::const_iterator it = folderChildren.begin(); it != folderChildren.end(); ++it)
		this->deleteAllTree(*it, username, token, data, query);
	this->folderDB.deleteRecord(folder->getId());
}


std::string DeleteFolderService::execute(const std::string& username, const std::string& token, const std::string& data, const std::string& query) const{
	std::string response = "";
	std::string userJsonString = this->userDB.getValue(username);
	if (userJsonString != ""){
		User user(userJsonString);
		if (user.authenticateToken(token)){

			std::string queryKey("idFolder=");
			std::string folderId = query.substr(query.find(queryKey)+queryKey.length());
			std::string folderJsonString = this->folderDB.getValue(folderId);
			if (folderJsonString != ""){
				Folder *folder = new Folder(folderJsonString, this->userDB, this->folderDB, this->fileDB);
				this->deleteAllTree(folder, username, token, data, query);
				delete folder;
				return HttpResponse::GetHttpOkResponse("");
			}
			else
				return HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_INVALID_FOLDER);
		}
		else
			response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_AUTHENTICATION);
	}
	else
		response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_AUTHENTICATION);

	return response;
}
