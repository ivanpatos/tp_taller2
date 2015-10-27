#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../main/include/server/Services/LogoutService.h"
#include "LogoutServiceFixture.h"

using ::testing::Return;
using ::testing::_;



TEST_F(LogoutServiceFixture,invalidUsername) {

	query = username;

	EXPECT_CALL(userDB,getValue( username ) )
	.WillOnce(Return(""));

	std::string responseFromService = logoutService->execute( username, token, data , query );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ(	ERROR, jsonData["result"].asCString() );
	EXPECT_EQ(	 jsonData["errorCode"] , HttpResponse::ERROR_AUTHENTICATION );
}



TEST_F(LogoutServiceFixture,validUsernameInvalidToken) {

	query = username;
	userNotSavedInDb.setToken("555");

	std::string data2 = userNotSavedInDb.getJsonString();
	EXPECT_CALL(userDB,getValue( username ) )
		.WillOnce(Return(data2));

	std::string responseFromService = logoutService->execute( username, token, data , query );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ(	ERROR, jsonData["result"].asCString() );
	EXPECT_EQ(	 jsonData["errorCode"] , HttpResponse::ERROR_AUTHENTICATION );
}

TEST_F(LogoutServiceFixture,validUsernameAndPasswordNotSavedValue) {
	query = username;

	EXPECT_CALL(userDB,getValue( username ) )
			.WillOnce(Return(data));

	EXPECT_CALL(userDB,saveValue( username , _ ))
	.WillOnce(Return(false));

	std::string responseFromService = logoutService->execute( username, token, data , query );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ(	ERROR, jsonData["result"].asCString() );
	EXPECT_EQ(	 jsonData["errorCode"] , HttpResponse::ERROR_SAVING_DATA );

}


TEST_F(LogoutServiceFixture,validUsernameAndPasswordSavedValue) {
	query = username;

	EXPECT_CALL(userDB,getValue( username ) )
			.WillOnce(Return(data));

	EXPECT_CALL(userDB,saveValue( username , _ ))
	        .WillOnce(Return(true));

	std::string responseFromService = logoutService->execute( username, token, data , query );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ(	OK 	 , jsonData["result"].asCString() );

}


int main(int argc, char *argv[]){
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
