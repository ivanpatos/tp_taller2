/*
 * CreateFolderService.cpp
 *
 *  Created on: Oct 26, 2015
 *      Author: tomrea
 */


#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../main/include/server/Services/CreateFolderService.h"
#include "CreateFolderServiceFixture.h"

using ::testing::Return;
using ::testing::_;


TEST_F(CreateFolderServiceFixture,createFolderServiceOK) {

	EXPECT_CALL(userDB,getValue( username ) )
	.WillOnce(Return(data));

	Json::Value jsonHeader;
	jsonHeader["name"] 	 	= "folder1";
	jsonHeader["idParent"] 	= username;
	Json::StreamWriterBuilder builder;
	std::string stringHeader = Json::writeString(builder,jsonHeader);

	Json::Value json;
	json["id"] = username;
	json["name"] = "root";
	Folder rootFolder(json);

	std::cout << stringHeader << std::endl;
	EXPECT_CALL( folderDB,getValue( jsonHeader.get("idParent", "").asCString() ) )
	.WillRepeatedly(Return( rootFolder.getJsonString() ));

	EXPECT_CALL( folderDB, saveValue( _ , _ ) )
	.WillOnce(Return( true ))
	.WillOnce(Return( true ));

	std::string responseFromService = createFolderService->execute( username, token, stringHeader , query );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	std::string folderName = "folder1";
	std::string pathNewFolder = username + "/" + folderName;
	EXPECT_EQ(	OK 	 , jsonData["result"].asCString() );
	EXPECT_EQ( 	pathNewFolder , jsonData["data"]["id"].asCString()  );
	EXPECT_EQ(	folderName 	 , jsonData["data"]["name"].asCString()  );
}

TEST_F(CreateFolderServiceFixture,createFolderServiceUserMissing) {

	EXPECT_CALL(userDB,getValue( username ) )
	.WillOnce(Return(""));

	Json::Value jsonHeader;
	jsonHeader["name"] 	 	= "folder1";
	jsonHeader["idParent"] 	= username;
	Json::StreamWriterBuilder builder;
	std::string stringHeader = Json::writeString(builder,jsonHeader);

	Json::Value json;
	json["id"] = username;
	json["name"] = "root";
	Folder rootFolder(json);

	std::string responseFromService = createFolderService->execute( username, token, stringHeader , query );
	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	std::string folderName = "folder1";
	std::string pathNewFolder = username + "/" + folderName;
	EXPECT_EQ(	ERROR 	 , jsonData["result"].asCString() );
	EXPECT_EQ( 	jsonData["errorCode"], HttpResponse::ERROR_AUTHENTICATION  );
}

int main(int argc, char *argv[]){
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}


