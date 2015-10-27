/*
 * CreateFolderService.cpp
 *
 *  Created on: Oct 26, 2015
 *      Author: tomrea
 */


#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../main/include/server/Services/GetFolderService.h"
#include "GetFolderServiceFixture.h"

using ::testing::Return;
using ::testing::_;


TEST_F(GetFolderServiceFixture,getFolderServiceOK) {

	EXPECT_CALL(userDB,getValue( username ) )
	.WillOnce(Return(data));

	std::string folderName = "folder1";
	std::string pathNewFolder = username + "/" + folderName;

	Json::Value jsonFolderData;
	jsonFolderData["name"] 	 	= folderName;
	jsonFolderData["id"] 	= pathNewFolder;
	Folder folderBuscada(jsonFolderData);

	Json::Value json;
	json["id"] = username;
	json["name"] = "root";
	Folder rootFolder(json);

	EXPECT_CALL( folderDB,getValue( pathNewFolder ) )
	.WillOnce(Return( folderBuscada.getJsonString() ));

	std::string responseFromService = getFolderService->execute( username, token, "" , pathNewFolder );

	std::cout << responseFromService << std::endl;
	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ(	OK 	 , jsonData["result"].asCString() );
	EXPECT_EQ( 	pathNewFolder , jsonData["data"]["id"].asCString()  );
	EXPECT_EQ(	folderName 	 , jsonData["data"]["name"].asCString()  );
}

TEST_F(GetFolderServiceFixture,getFolderServiceInvalidFolder) {

	EXPECT_CALL(userDB,getValue( username ) )
	.WillOnce(Return(data));

	std::string folderName = "folder1";
	std::string pathNewFolder = username + "/" + folderName;

	Json::Value jsonFolderData;
	jsonFolderData["name"] 	 	= folderName;
	jsonFolderData["id"] 	= pathNewFolder;
	Folder folderBuscada(jsonFolderData);

	Json::Value json;
	json["id"] = username;
	json["name"] = "root";
	Folder rootFolder(json);

	EXPECT_CALL( folderDB,getValue( pathNewFolder ) )
	.WillOnce(Return( "" ));

	std::string responseFromService = getFolderService->execute( username, token, "" , pathNewFolder );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ(	ERROR 	 , jsonData["result"].asCString() );
	EXPECT_EQ( 	jsonData["errorCode"] , HttpResponse::ERROR_INVALID_FOLDER );
}

int main(int argc, char *argv[]){
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}


