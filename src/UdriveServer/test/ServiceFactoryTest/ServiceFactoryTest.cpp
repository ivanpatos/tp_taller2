#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../main/include/server/ServiceFactory.h"

using ::testing::Return;
using ::testing::_;


TEST(ServiceFactoryTest,loginService){
	Database userDB("./userDB"), folderDB("./folderDB"), fileDB("./fileDB"), dataDB("./dataDB");
	ServiceFactory serverFactory(userDB,folderDB,fileDB,dataDB);
	const std::string login = "login";
	const std::string post = "POST";

	std::string name = (serverFactory.createService(login, post))->name();
	EXPECT_TRUE(name == "LoginService");
}

TEST(ServiceFactoryTest,logoutService){
	Database userDB("./userDB"), folderDB("./folderDB"), fileDB("./fileDB"), dataDB("./dataDB");
	ServiceFactory serverFactory(userDB,folderDB,fileDB,dataDB);
	const std::string logout = "logout";
	const std::string post = "POST";

	std::string name = (serverFactory.createService(logout, post))->name();
	EXPECT_TRUE(name == "LogoutService");
}

TEST(ServiceFactoryTest,createFileService){
	Database userDB("./userDB"), folderDB("./folderDB"), fileDB("./fileDB"), dataDB("./dataDB");
	ServiceFactory serverFactory(userDB,folderDB,fileDB,dataDB);
	const std::string resource = "file";
	const std::string method = "POST";

	std::string name = (serverFactory.createService(resource, method))->name();
	EXPECT_TRUE(name == "CreateFileService");
}
TEST(ServiceFactoryTest,createFolderService){
	Database userDB("./userDB"), folderDB("./folderDB"), fileDB("./fileDB"), dataDB("./dataDB");
	ServiceFactory serverFactory(userDB,folderDB,fileDB,dataDB);
	const std::string resource = "folder";
	const std::string method = "POST";

	std::string name = (serverFactory.createService(resource, method))->name();
	EXPECT_TRUE(name == "CreateFolderService");
}

TEST(ServiceFactoryTest,createUserService){
	Database userDB("./userDB"), folderDB("./folderDB"), fileDB("./fileDB"), dataDB("./dataDB");
	ServiceFactory serverFactory(userDB,folderDB,fileDB,dataDB);
	const std::string resource = "user";
	const std::string method = "POST";

	std::string name = (serverFactory.createService(resource, method))->name();
	EXPECT_TRUE(name == "CreateUserService");
}

TEST(ServiceFactoryTest,getFileService){
	Database userDB("./userDB"), folderDB("./folderDB"), fileDB("./fileDB"), dataDB("./dataDB");
	ServiceFactory serverFactory(userDB,folderDB,fileDB,dataDB);
	const std::string resource = "file";
	const std::string method = "GET";

	std::string name = (serverFactory.createService(resource, method))->name();
	EXPECT_TRUE(name == "GetFileService");
}
TEST(ServiceFactoryTest,getFolderService){
	Database userDB("./userDB"), folderDB("./folderDB"), fileDB("./fileDB"), dataDB("./dataDB");
	ServiceFactory serverFactory(userDB,folderDB,fileDB,dataDB);
	const std::string resource = "folder";
	const std::string method = "GET";

	std::string name = (serverFactory.createService(resource, method))->name();
	EXPECT_TRUE(name == "GetFolderService");
}
TEST(ServiceFactoryTest,getUserService){
	Database userDB("./userDB"), folderDB("./folderDB"), fileDB("./fileDB"), dataDB("./dataDB");
	ServiceFactory serverFactory(userDB,folderDB,fileDB,dataDB);
	const std::string resource = "user";
	const std::string method = "GET";

	std::string name = (serverFactory.createService(resource, method))->name();
	EXPECT_TRUE(name == "GetUserService");
}
TEST(ServiceFactoryTest,nonExistentService){
	Database userDB("./userDB"), folderDB("./folderDB"), fileDB("./fileDB"), dataDB("./dataDB");
	ServiceFactory serverFactory(userDB,folderDB,fileDB,dataDB);
	const std::string resource = "other";
	const std::string method = "other";

	std::string name = (serverFactory.createService(resource, method))->name();
	EXPECT_TRUE(name == "NonExistentService");
}
TEST(ServiceFactoryTest,UpdateFileService){
	Database userDB("./userDB"), folderDB("./folderDB"), fileDB("./fileDB"), dataDB("./dataDB");
	ServiceFactory serverFactory(userDB,folderDB,fileDB,dataDB);
	const std::string resource = "file";
	const std::string method = "PUT";

	std::string name = (serverFactory.createService(resource, method))->name();
	EXPECT_TRUE(name == "UpdateFileService");
}
TEST(ServiceFactoryTest,updateUserService){
	Database userDB("./userDB"), folderDB("./folderDB"), fileDB("./fileDB"), dataDB("./dataDB");
	ServiceFactory serverFactory(userDB,folderDB,fileDB,dataDB);
	const std::string resource = "user";
	const std::string method = "PUT";

	std::string name = (serverFactory.createService(resource, method))->name();
	EXPECT_TRUE(name == "UpdateUserService");
}

TEST(ServiceFactoryTest,deleteFolderService){
	Database userDB("./userDB"), folderDB("./folderDB"), fileDB("./fileDB"), dataDB("./dataDB");
	ServiceFactory serverFactory(userDB,folderDB,fileDB,dataDB);
	const std::string resource = "folder";
	const std::string method = "DELETE";

	std::string name = (serverFactory.createService(resource, method))->name();
	EXPECT_TRUE(name == "DeleteFolderService");
}

TEST(ServiceFactoryTest,deleteFileService){
	Database userDB("./userDB"), folderDB("./folderDB"), fileDB("./fileDB"), dataDB("./dataDB");
	ServiceFactory serverFactory(userDB,folderDB,fileDB,dataDB);
	const std::string resource = "file";
	const std::string method = "DELETE";

	std::string name = (serverFactory.createService(resource, method))->name();
	EXPECT_TRUE(name == "DeleteFileService");
}
int main(int argc, char *argv[]){
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
