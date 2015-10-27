#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../main/include/server/Services/LoginService.h"
#include "LoginServiceFixture.h"

using ::testing::Return;
using ::testing::_;



TEST_F(LoginServiceFixture,invalidUsername) {

	query = username;

	EXPECT_CALL(userDB,getValue( username ) )
	.WillOnce(Return(""));


	std::string responseFromService = loginService->execute( username, token, data , query );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ(	ERROR, jsonData["result"].asCString() );
	EXPECT_EQ(	 jsonData["errorCode"] , HttpResponse::ERROR_INVALID_USERNAME );
}



TEST_F(LoginServiceFixture,validUsernameInvalidPassword) {

	query = username;
	userNotSavedInDb.setPassword("invalid");

	std::string data2 = userNotSavedInDb.getJsonString();
	EXPECT_CALL(userDB,getValue( username ) )
		.WillOnce(Return(data2));

	std::string responseFromService = loginService->execute( username, token, data , query );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ(	ERROR, jsonData["result"].asCString() );
	EXPECT_EQ(	 jsonData["errorCode"] , HttpResponse::ERROR_INVALID_PASSWORD );
}

TEST_F(LoginServiceFixture,validUsernameAndPasswordNotSavedValue) {
	query = username;
	userNotSavedInDb.setPassword(""); //valid

	EXPECT_CALL(userDB,getValue( username ) )
			.WillOnce(Return(data));

	EXPECT_CALL(userDB,saveValue( username , _ ))
	.WillOnce(Return(false));

	std::string responseFromService = loginService->execute( username, token, data , query );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ(	ERROR, jsonData["result"].asCString() );
	EXPECT_EQ(	 jsonData["errorCode"] , HttpResponse::ERROR_SAVING_DATA );

}


TEST_F(LoginServiceFixture,validUsernameAndPasswordSavedValue) {
	query = username;

	EXPECT_CALL(userDB,getValue( username ) )
			.WillOnce(Return(data));

	EXPECT_CALL(userDB,saveValue( username , _ ))
	        .WillOnce(Return(true));

	std::string responseFromService = loginService->execute( username, token, data , query );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ(	OK 	 , jsonData["result"].asCString() );
	EXPECT_EQ( 	username , jsonData["data"]["username"].asCString()  );
	EXPECT_EQ(	mail 	 , jsonData["data"]["mail"].asCString()  );
}


int main(int argc, char *argv[]){
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
