#include "../../../include/server/Services/UpdateFileService.h"
#include "../../../include/server/HttpResponse.h"
#include "../../../include/resources/User.h"
#include "../../../include/resources/File.h"
#include "../../../include/resources/Folder.h"
#include "../../../include/resources/Version.h"
#include "../../../include/utilities/Time.h"
#include "../../../others/json/json.h"
#include <sstream>

#include <iostream>
UpdateFileService::UpdateFileService(Database &userDB, Database &folderDB, Database &fileDB, Database &dataDB) : userDB(userDB), folderDB(folderDB), fileDB(fileDB), dataDB(dataDB){
}

UpdateFileService::~UpdateFileService(){
}

const char* UpdateFileService::name() const{
	return "UpdateFileService";
}
std::string UpdateFileService::execute(const std::string& username, const std::string& token, const std::string& data, const std::string& query) const{
	std::string response = "";
	std::string userJsonString = this->userDB.getValue(username);
	if (userJsonString != ""){
		User user(userJsonString);
		if (user.authenticateToken(token)){

			std::string fileId = query;
			std::string fileJsonString = this->fileDB.getValue(fileId);

			if (fileJsonString != ""){
				File file(fileJsonString, this->userDB);
				if (file.hasPermission(user)){

					Json::Value jsonData;
					Json::Reader reader;
					reader.parse(data, jsonData);

					//update fisico
					if (jsonData.isMember("data")){
						std::string dataString = jsonData.get("data", "").asCString();
						if (user.getSpace() < dataString.length())
							response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_NOT_ENOUGH_SPACE);
						else{
							user.setSpace(user.getSpace()-dataString.length());
							file.increaseVersion();
							file.setLastUser(new User(userJsonString));
							file.setLastModified(Time::getCurrentTime());
							std::ostringstream ss;
							ss << file.getVersion();
							Version version(file.getId() + "_" + ss.str(), dataString);
							if (this->userDB.saveValue(user.getUsername(), user.getJsonString()) && this->fileDB.saveValue(file.getId(), file.getJsonString()) && this->dataDB.saveValue(version.getId(), version.getData()))
								response = HttpResponse::GetHttpOkResponse(file.getJson());
							else
								response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_SAVING_DATA);
						}
					}
					//update metadatos
					else{
						//actualizo nombre y extension
						file.setName(jsonData.get("name", "").asCString());
						file.setExtension(jsonData.get("extension", "").asCString());

						//actualizo labels
						Json::Value jsonLabels = jsonData["labels"];
						std::vector<std::string> labels;
						for(Json::ValueIterator it = jsonLabels.begin() ; it != jsonLabels.end() ; it++)
							labels.push_back((*it).get("description", "").asCString());
						file.setLabels(labels);

						//agrego usuarios compartidos
						Json::Value jsonUsers = jsonData["users"];
						for(Json::ValueIterator it = jsonUsers.begin() ; it != jsonUsers.end() ; it++) {
							User* userSharedWith = new User(userDB.getValue((*it).get("username", "").asCString()));
							if (!file.hasPermission(*userSharedWith)){
								file.addUser(userSharedWith);
								Folder folderSharedWith(this->folderDB.getValue("sharedwith_" + userSharedWith->getUsername()), this->userDB, this->folderDB, this->fileDB);
								folderSharedWith.addFileChildren(new File(fileJsonString, this->userDB));
								if (!this->folderDB.saveValue(folderSharedWith.getId(), folderSharedWith.getJsonString()))
									return response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_SAVING_DATA);
							}
						}
						//saco usuarios con los que no se quiere compartir mas
						if (file.isOwner(user)){
							std::vector<User*> users = file.getUsers();
							for(std::vector<User*>::const_iterator it = users.begin(); it != users.end(); ++it){
								bool found = false;
								Json::Value jsonUsers = jsonData["users"];
								for(Json::ValueIterator itJson = jsonUsers.begin() ; itJson != jsonUsers.end() && !found; itJson++){
									if ((*itJson).get("username", "").asCString() == (*it)->getUsername())
										found = true;
								}
								if (!found){
									Folder folderSharedWith(this->folderDB.getValue("sharedwith_" + (*it)->getUsername()), this->userDB, this->folderDB, this->fileDB);
									folderSharedWith.removeFileChildren(&file);
									if (!this->folderDB.saveValue(folderSharedWith.getId(), folderSharedWith.getJsonString()))
										return response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_SAVING_DATA);
									Folder folderRecovered(this->folderDB.getValue("recovered_" + (*it)->getUsername()), this->userDB, this->folderDB, this->fileDB);
									folderRecovered.removeFileChildren(&file);
									if (!this->folderDB.saveValue(folderRecovered.getId(), folderRecovered.getJsonString()))
										return response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_SAVING_DATA);
									file.removeUser(**it);
								}
							}
						}
						//recupero archivo borrado
						if (!jsonData.get("deleted", "").asBool() && file.getDeleted()){

							file.setDeleted(false);

							//remuevo file de la carpeta trash del owner
							User *owner = file.getOwner();
							Folder folderTrashOwner(this->folderDB.getValue("trash_" + owner->getUsername()), this->userDB, this->folderDB, this->fileDB);
							folderTrashOwner.removeFileChildren(&file);
							if (!this->folderDB.saveValue(folderTrashOwner.getId(), folderTrashOwner.getJsonString()))
								return response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_SAVING_DATA);

							//agrego file a la carpeta recovered del owner
							Folder folderRecoveredOwner(this->folderDB.getValue("recovered_" + owner->getUsername()), this->userDB, this->folderDB, this->fileDB);
							folderRecoveredOwner.addFileChildren(new File(file.getJsonString(), this->userDB));
							if (!this->folderDB.saveValue(folderRecoveredOwner.getId(), folderRecoveredOwner.getJsonString()))
								return response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_SAVING_DATA);

							std::vector<User*> users = file.getUsers();
							for(std::vector<User*>::const_iterator it = users.begin(); it != users.end(); ++it){

								//remuevo file de la carpeta trash del usuario compartido
								Folder folderTrashUser(this->folderDB.getValue("trash_" + (*it)->getUsername()), this->userDB, this->folderDB, this->fileDB);
								folderTrashUser.removeFileChildren(&file);
								if (!this->folderDB.saveValue(folderTrashUser.getId(), folderTrashUser.getJsonString()))
									return response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_SAVING_DATA);

								//agrego file a la carpeta recovered del usuario compartido
								Folder folderRecoveredUser(this->folderDB.getValue("recovered_" + (*it)->getUsername()), this->userDB, this->folderDB, this->fileDB);
								folderRecoveredUser.addFileChildren(new File(file.getJsonString(), this->userDB));
								if (!this->folderDB.saveValue(folderRecoveredUser.getId(), folderRecoveredUser.getJsonString()))
									return response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_SAVING_DATA);
							}
						}
						if (!this->fileDB.saveValue(file.getId(), file.getJsonString()))
							response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_SAVING_DATA);
						else
							response = HttpResponse::GetHttpOkResponse(file.getJson());
					}
				}
				else
					response = HttpResponse::GetHttpErrorResponse(HttpResponse::ERROR_FILE_PERMISSION_DENIED);
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
