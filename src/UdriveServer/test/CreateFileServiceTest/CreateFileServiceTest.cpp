#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../main/include/server/Services/CreateFileService.h"
#include "CreateFileServiceFixture.h"

using ::testing::Return;
using ::testing::_;


TEST_F(CreateFileServiceFixture,invalidUsername) {

	query = username;

	EXPECT_CALL(userDB,getValue( username ) )
		.WillOnce(Return(""));

	std::string responseFromService = createFileService->execute( username, token, data , query );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ(	ERROR, jsonData["result"].asCString() );
	EXPECT_EQ(	 jsonData["errorCode"] , HttpResponse::ERROR_AUTHENTICATION );
}

TEST_F(CreateFileServiceFixture,invalidToken) {

	query = username;
	userNotSavedInDb.setToken("555");
	std::string data2 = userNotSavedInDb.getJsonString();
	EXPECT_CALL(userDB,getValue( username ) )
			.WillOnce(Return(data2));

	std::string responseFromService = createFileService->execute( username, token, data , query );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ(	ERROR, jsonData["result"].asCString() );
	EXPECT_EQ(	 jsonData["errorCode"] , HttpResponse::ERROR_AUTHENTICATION );
}

TEST_F(CreateFileServiceFixture,invalidFolderParent) {

	query = username;

	std::string data2 = userNotSavedInDb.getJsonString();
	EXPECT_CALL(userDB,getValue( username ) )
			.WillOnce(Return(data2));

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse(data, jsonData);

	EXPECT_CALL(folderDB,getValue(jsonData.get("idFolder", "").asCString()) )
				.WillOnce(Return(""));

	std::string responseFromService = createFileService->execute( username, token, data , query );

	reader.parse( responseFromService, jsonData);

	EXPECT_EQ(	ERROR, jsonData["result"].asCString() );
	EXPECT_EQ(	 jsonData["errorCode"] , HttpResponse::ERROR_INVALID_FOLDER_PARENT );

}

TEST_F(CreateFileServiceFixture, errorSavingData) {
	query = username;

	std::string data2 = userNotSavedInDb.getJsonString();
	EXPECT_CALL(userDB,getValue( username ) )
			.WillRepeatedly(Return(data2));

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse(data, jsonData);

	EXPECT_CALL(folderDB,getValue(jsonData.get("idFolder", "").asCString()) )
					.WillOnce(Return("folder"));

	EXPECT_CALL(fileDB,saveValue( _ , _ ))
		.WillOnce(Return(true));

	EXPECT_CALL(dataDB,saveValue( _ , _ ))
		.WillOnce(Return(true));

	EXPECT_CALL(folderDB,saveValue( _ , _ ))
			.WillOnce(Return(false));

	std::string responseFromService = createFileService->execute( username, token, data , query );

	reader.parse( responseFromService, jsonData);
	EXPECT_EQ(	ERROR, jsonData["result"].asCString() );
	EXPECT_EQ(	 jsonData["errorCode"] , HttpResponse::ERROR_SAVING_DATA );

}

TEST_F(CreateFileServiceFixture, errorFileExists) {
//TODO
}

TEST_F(CreateFileServiceFixture, createFileOk) {
	query = username;

	std::string data2 = userNotSavedInDb.getJsonString();
	EXPECT_CALL(userDB,getValue( username ) )
			.WillRepeatedly(Return(data2));

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse(data, jsonData);

	EXPECT_CALL(folderDB,getValue(jsonData.get("idFolder", "").asCString()) )
					.WillOnce(Return("folder"));

	EXPECT_CALL(fileDB,saveValue( _ , _ ))
		.WillOnce(Return(true));

	EXPECT_CALL(dataDB,saveValue( _ , _ ))
		.WillOnce(Return(true));

	EXPECT_CALL(folderDB,saveValue( _ , _ ))
			.WillOnce(Return(true));

	std::string responseFromService = createFileService->execute( username, token, data , query );

	reader.parse( responseFromService, jsonData);
	EXPECT_EQ(	OK, jsonData["result"].asCString() );
}



int main(int argc, char *argv[]){
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
