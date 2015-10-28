#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../main/include/server/Services/UpdateFileService.h"
#include "UpdateFileServiceFixture.h"

using ::testing::Return;
using ::testing::_;


TEST_F(UpdateFileServiceFixture,invalidUsername) {
	query = username;

	EXPECT_CALL(userDB,getValue( username ) )
		.WillOnce(Return(""));

	std::string responseFromService = updateFileService->execute( username, token, data , query );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ(	ERROR, jsonData["result"].asCString() );
	EXPECT_EQ(	 jsonData["errorCode"] , HttpResponse::ERROR_AUTHENTICATION );
}

TEST_F(UpdateFileServiceFixture,invalidToken) {
	query = username;
	userNotSavedInDb.setToken("555");
	std::string data2 = userNotSavedInDb.getJsonString();
	EXPECT_CALL(userDB,getValue( username ) )
			.WillOnce(Return(data2));

	std::string responseFromService = updateFileService->execute( username, token, data , query );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ(	ERROR, jsonData["result"].asCString() );
	EXPECT_EQ(	 jsonData["errorCode"] , HttpResponse::ERROR_AUTHENTICATION );
}

TEST_F(UpdateFileServiceFixture,invalidFile) {
	query = username;
	std::string data2 = userNotSavedInDb.getJsonString();
	EXPECT_CALL(userDB,getValue( username ) )
			.WillOnce(Return(data2));

	EXPECT_CALL(fileDB,getValue( _ ) )
				.WillOnce(Return(""));
	std::string responseFromService = updateFileService->execute( username, token, data , query );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ(	ERROR, jsonData["result"].asCString() );
	EXPECT_EQ(	 jsonData["errorCode"] , HttpResponse::ERROR_INVALID_FILE );

}

TEST_F(UpdateFileServiceFixture, permisonDenied) {
//TODO
}

TEST_F(UpdateFileServiceFixture, errorSavingData) {
//TODO
}

TEST_F(UpdateFileServiceFixture, updateFisicoOk) {
//TODO
}


TEST_F(UpdateFileServiceFixture, updateFisicoErrorSavingData) {
//TODO
}


TEST_F(UpdateFileServiceFixture, updateMetadatosOk) {
//TODO
}


TEST_F(UpdateFileServiceFixture, updateMetadatosErrorSavingData) {
//TODO
}


int main(int argc, char *argv[]){
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
