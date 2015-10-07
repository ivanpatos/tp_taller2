#include "../../../include/server/Services/DeleteFileService.h"
#include "../../../include/server/HttpResponse.h"
#include "../../../include/resources/User.h"
#include "../../../include/resources/File.h"
#include "../../../include/resources/Version.h"
#include "../../../others/json/json.h"


DeleteFileService::DeleteFileService(Database &userDB, Database &folderDB, Database &fileDB) : userDB(userDB), folderDB(folderDB), fileDB(fileDB){
}

DeleteFileService::~DeleteFileService(){
}

const char* DeleteFileService::name() const{
	return "DeleteFileService";
}

void DeleteFileService::deleteFileFromOwner(Folder* folder, File *file) const{
	if (folder->hasFile(file->getName(), file->getExtension())){
		folder->removeFileChildren(file);
		this->folderDB.saveValue(folder->getId(), folder->getJsonString());
	}
	else{
		std::vector<Folder*> folderChildren = folder->getFolderChildren();
		for(std::vector<Folder*>::const_iterator it = folderChildren.begin(); it != folderChildren.end(); ++it)
			this->deleteFileFromOwner(*it, file);
	}
}

std::string DeleteFileService::execute(const std::string& username, const std::string& token, const std::string& data, const std::string& query) const{
	std::string response = "";
		std::string userJsonString = this->userDB.getValue(username);
		if (userJsonString != ""){
			User user(userJsonString);
			if (user.authenticateToken(token)){

				std::string queryKey("idFile=");
				std::string fileId = query.substr(query.find(queryKey)+queryKey.length());
				std::string fileJsonString = this->fileDB.getValue(fileId);

				if (fileJsonString != ""){
					File *file = new File(fileJsonString, this->userDB);
					if (!file->hasPermission(user)){
						delete file;
						return response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_FILE_PERMISSION_DENIED);
					}
					else if(file->getDeleted()){
						delete file;
						return response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_FILE_ALREADY_DELETED);
					}
					else{

						//remuevo file de la carpeta padre que lo contiene
						//veo primero si esta en la carpeta recovered, sino recorro el arbol del owner
						User *owner = file->getOwner();
						Folder folderRecoveredOwner(this->folderDB.getValue("recovered_" + owner->getUsername()), this->userDB, this->folderDB, this->fileDB);
						if (folderRecoveredOwner.hasFile(file->getName(), file->getExtension())){
							folderRecoveredOwner.removeFileChildren(file);
							if (!this->folderDB.saveValue(folderRecoveredOwner.getId(), folderRecoveredOwner.getJsonString()))
								return response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_SAVING_DATA);
						}
						else{
							Folder *folderRootOwner = new Folder(this->folderDB.getValue(owner->getUsername()), this->userDB, this->folderDB, this->fileDB);
							deleteFileFromOwner(folderRootOwner, file);
							delete folderRootOwner;
						}

						//agrego file al trash del owner
						Folder folderTrashOwner(this->folderDB.getValue("trash_" + owner->getUsername()), this->userDB, this->folderDB, this->fileDB);
						folderTrashOwner.addFileChildren(file);
						if (!this->folderDB.saveValue(folderTrashOwner.getId(), folderTrashOwner.getJsonString()))
							return response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_SAVING_DATA);

						std::vector<User*> users = file->getUsers();
						for(std::vector<User*>::const_iterator it = users.begin(); it != users.end(); ++it){

							//remuevo file de la carpeta sharedwith del usuario compartido
							Folder folderSharedWith(this->folderDB.getValue("sharedwith_" + (*it)->getUsername()), this->userDB, this->folderDB, this->fileDB);
							if (folderSharedWith.hasFile(file->getName(), file->getExtension())){
								folderSharedWith.removeFileChildren(file);
								if (!this->folderDB.saveValue(folderSharedWith.getId(), folderSharedWith.getJsonString()))
									return response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_SAVING_DATA);
							}
							//si no esta en la carpeta sharedwith entonces el archivo a borrar esta en la carpeta recovered
							else{
								Folder folderRecovered(this->folderDB.getValue("recovered_" + (*it)->getUsername()), this->userDB, this->folderDB, this->fileDB);
								folderRecovered.removeFileChildren(file);
								if (!this->folderDB.saveValue(folderRecovered.getId(), folderRecovered.getJsonString()))
									return response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_SAVING_DATA);
							}

							//agrego file al trash del usuario compartido
							Folder folderTrash(this->folderDB.getValue("trash_" + (*it)->getUsername()), this->userDB, this->folderDB, this->fileDB);
							folderTrash.addFileChildren(new File(fileJsonString, this->userDB));
							if (!this->folderDB.saveValue(folderTrash.getId(), folderTrash.getJsonString()))
								return response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_SAVING_DATA);
						}
						file->setDeleted(true);
						if (!this->fileDB.saveValue(file->getId(), file->getJsonString()))
								return response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_SAVING_DATA);

						response = HttpResponse::GetHttpOkResponse("");
					}
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
