#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../main/include/server/ServiceFactory.h"
#include "../../main/include/database/MockDatabase.h"

using ::testing::Return;
using ::testing::_;

#include "../../main/include/utilities/easylogging++.h"
INITIALIZE_EASYLOGGINGPP
#define ELPP_DISABLE_LOGS

TEST(ServiceFactoryTest,loginService){
	MockDatabase userDB, folderDB, fileDB, dataDB;
	ServiceFactory serverFactory(userDB,folderDB,fileDB,dataDB);
	const std::string login = "login";
	const std::string post = "POST";

	std::string name = (serverFactory.createService(login, post))->name();
	EXPECT_TRUE(name == "LoginService");
}

TEST(ServiceFactoryTest,logoutService){
	MockDatabase userDB,folderDB,fileDB,dataDB;
	ServiceFactory serverFactory(userDB,folderDB,fileDB,dataDB);
	const std::string logout = "logout";
	const std::string post = "POST";

	std::string name = (serverFactory.createService(logout, post))->name();
	EXPECT_TRUE(name == "LogoutService");
}

TEST(ServiceFactoryTest,createFileService){
	MockDatabase userDB, folderDB, fileDB, dataDB;
	ServiceFactory serverFactory(userDB,folderDB,fileDB,dataDB);
	const std::string resource = "file";
	const std::string method = "POST";

	std::string name = (serverFactory.createService(resource, method))->name();
	EXPECT_TRUE(name == "CreateFileService");
}
TEST(ServiceFactoryTest,createFolderService){
	MockDatabase userDB, folderDB, fileDB, dataDB;
	ServiceFactory serverFactory(userDB,folderDB,fileDB,dataDB);
	const std::string resource = "folder";
	const std::string method = "POST";

	std::string name = (serverFactory.createService(resource, method))->name();
	EXPECT_TRUE(name == "CreateFolderService");
}

TEST(ServiceFactoryTest,createUserService){
	MockDatabase userDB, folderDB, fileDB, dataDB;
	ServiceFactory serverFactory(userDB,folderDB,fileDB,dataDB);
	const std::string resource = "user";
	const std::string method = "POST";

	std::string name = (serverFactory.createService(resource, method))->name();
	EXPECT_TRUE(name == "CreateUserService");
}

TEST(ServiceFactoryTest,getFileService){
	MockDatabase userDB, folderDB, fileDB, dataDB;
	ServiceFactory serverFactory(userDB,folderDB,fileDB,dataDB);
	const std::string resource = "file";
	const std::string method = "GET";

	std::string name = (serverFactory.createService(resource, method))->name();
	EXPECT_TRUE(name == "GetFileService");
}
TEST(ServiceFactoryTest,getFolderService){
	MockDatabase userDB, folderDB, fileDB, dataDB;
	ServiceFactory serverFactory(userDB,folderDB,fileDB,dataDB);
	const std::string resource = "folder";
	const std::string method = "GET";

	std::string name = (serverFactory.createService(resource, method))->name();
	EXPECT_TRUE(name == "GetFolderService");
}
TEST(ServiceFactoryTest,getUserService){
	MockDatabase userDB, folderDB, fileDB, dataDB;
	ServiceFactory serverFactory(userDB,folderDB,fileDB,dataDB);
	const std::string resource = "user";
	const std::string method = "GET";

	std::string name = (serverFactory.createService(resource, method))->name();
	EXPECT_TRUE(name == "GetUserService");
}
TEST(ServiceFactoryTest,nonExistentService){
	MockDatabase userDB, folderDB, fileDB, dataDB;
	ServiceFactory serverFactory(userDB,folderDB,fileDB,dataDB);
	const std::string resource = "other";
	const std::string method = "other";

	std::string name = (serverFactory.createService(resource, method))->name();
	EXPECT_TRUE(name == "NonExistentService");
}
TEST(ServiceFactoryTest,UpdateFileService){
	MockDatabase userDB, folderDB, fileDB, dataDB;
	ServiceFactory serverFactory(userDB,folderDB,fileDB,dataDB);
	const std::string resource = "file";
	const std::string method = "PUT";

	std::string name = (serverFactory.createService(resource, method))->name();
	EXPECT_TRUE(name == "UpdateFileService");
}
TEST(ServiceFactoryTest,updateUserService){
	MockDatabase userDB, folderDB, fileDB, dataDB;
	ServiceFactory serverFactory(userDB,folderDB,fileDB,dataDB);
	const std::string resource = "user";
	const std::string method = "PUT";

	std::string name = (serverFactory.createService(resource, method))->name();
	EXPECT_TRUE(name == "UpdateUserService");
}

TEST(ServiceFactoryTest,deleteFolderService){
	MockDatabase userDB, folderDB, fileDB, dataDB;
	ServiceFactory serverFactory(userDB,folderDB,fileDB,dataDB);
	const std::string resource = "folder";
	const std::string method = "DELETE";

	std::string name = (serverFactory.createService(resource, method))->name();
	EXPECT_TRUE(name == "DeleteFolderService");
}

TEST(ServiceFactoryTest,deleteFileService){
	MockDatabase userDB, folderDB, fileDB, dataDB;
	ServiceFactory serverFactory(userDB,folderDB,fileDB,dataDB);
	const std::string resource = "file";
	const std::string method = "DELETE";

	std::string name = (serverFactory.createService(resource, method))->name();
	EXPECT_TRUE(name == "DeleteFileService");
}

TEST(ServiceFactoryTest,UpdateFolderService){
	MockDatabase userDB, folderDB, fileDB, dataDB;
	ServiceFactory serverFactory(userDB,folderDB,fileDB,dataDB);
	const std::string resource = "folder";
	const std::string method = "PUT";

	std::string name = (serverFactory.createService(resource, method))->name();
	EXPECT_TRUE(name == "UpdateFolderService");
}

int main(int argc, char *argv[]){
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
