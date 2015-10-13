#include "../../include/server/ServiceFactory.h"
#include "../../include/server/Services/LoginService.h"
#include "../../include/server/Services/LogoutService.h"
#include "../../include/server/Services/CreateUserService.h"
#include "../../include/server/Services/GetUserService.h"
#include "../../include/server/Services/UpdateUserService.h"
#include "../../include/server/Services/CreateFolderService.h"
#include "../../include/server/Services/GetFolderService.h"
#include "../../include/server/Services/CreateFileService.h"
#include "../../include/server/Services/GetFileService.h"
#include "../../include/server/Services/UpdateFileService.h"
#include "../../include/server/Services/DeleteFileService.h"
#include "../../include/server/Services/DeleteFolderService.h"
#include "../../include/server/Services/UpdateFolderService.h"
#include "../../include/server/Services/NonExistentService.h"


ServiceFactory::ServiceFactory(Database &userDB, Database &folderDB, Database &fileDB, Database &dataDB) :
	userDB(userDB), folderDB(folderDB), fileDB(fileDB), dataDB(dataDB){
}

ServiceFactory::~ServiceFactory(){
}

Service* ServiceFactory::createService(const std::string& resource, const std::string& method) const{
	if (resource == "login" && method == "POST")
		return new LoginService(this->userDB);
	if (resource == "logout" && method == "POST")
		return new LogoutService(this->userDB);
	if (resource == "user" && method == "POST")
		return new CreateUserService(this->userDB, this->folderDB);
	if (resource == "user" && method == "GET")
		return new GetUserService(this->userDB);
	if (resource == "user" && method == "PUT")
		return new UpdateUserService(this->userDB);
	if (resource == "folder" && method == "POST")
		return new CreateFolderService(this->userDB, this->folderDB, this->fileDB);
	if (resource == "folder" && method == "GET")
		return new GetFolderService(this->userDB, this->folderDB, this->fileDB);
	if (resource == "folder" && method == "PUT")
			return new UpdateFolderService(this->userDB, this->folderDB, this->fileDB, this->dataDB);
	if (resource == "folder" && method == "DELETE")
		return new DeleteFolderService(this->userDB, this->folderDB, this->fileDB);
	if (resource == "file" && method == "POST")
		return new CreateFileService(this->userDB, this->folderDB, this->fileDB, this->dataDB);
	if (resource == "file" && method == "GET")
			return new GetFileService(this->userDB, this->fileDB, this->dataDB);
	if (resource == "file" && method == "PUT")
			return new UpdateFileService(this->userDB, this->folderDB, this->fileDB, this->dataDB);
	if (resource == "file" && method == "DELETE")
			return new DeleteFileService(this->userDB, this->folderDB, this->fileDB);
	return new NonExistentService();
}
