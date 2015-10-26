#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../main/include/server/Services/CreateUserService.h"
#include "CreateUserServiceFixture.h"

using ::testing::Return;
using ::testing::_;


TEST_F(CreateUserServiceFixture,createUserServiceOK) {

	EXPECT_CALL(userDB,getValue( username ) )
	.WillOnce(Return(""));

	EXPECT_CALL(userDB,saveValue( username , _ ))
	.WillOnce(Return(true));

	EXPECT_CALL(folderDB,saveValue(_,_))
	.WillRepeatedly(Return(true));

	std::string responseFromService = createUserService->execute( username, token, data , query );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ(	OK 	 , jsonData["result"].asCString() );
	EXPECT_EQ( 	username , jsonData["data"]["username"].asCString()  );
	EXPECT_EQ(	mail 	 , jsonData["data"]["mail"].asCString()  );


}

TEST_F(CreateUserServiceFixture,userAlreadyExists) {

	//esto simboliza que el usuario SI estaba en la base de datos
	EXPECT_CALL(userDB,getValue( username ) )
	.WillOnce(Return(data));

	std::string responseFromService = createUserService->execute( username, token, data , query );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ(	ERROR	, jsonData["result"].asCString() );

	EXPECT_EQ(	jsonData["errorCode"], HttpResponse::ERROR_USERNAME_EXISTS );
}

TEST_F(CreateUserServiceFixture,userNameMissing){

	userNotSavedInDb.setUserName("");

	EXPECT_CALL(userDB,getValue( "" ) )
	.WillOnce(Return(""));

	std::string responseFromService = createUserService->execute( "", token, userNotSavedInDb.getJsonString() , query );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ(	ERROR, jsonData["result"].asCString() );
	EXPECT_EQ(	 jsonData["errorCode"] , HttpResponse::ERROR_USERNAME_MISSING );
}

TEST_F(CreateUserServiceFixture,passMissing){

	userNotSavedInDb.setPassword("");

	EXPECT_CALL(userDB,getValue( username ) )
	.WillOnce(Return(""));

	std::string responseFromService = createUserService->execute( username, token, userNotSavedInDb.getJsonString() , query );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ(	ERROR , jsonData["result"].asCString() );
	EXPECT_EQ( 	jsonData["errorCode"] , HttpResponse::ERROR_PASSWORD_MISSING );
}



int main(int argc, char *argv[]){
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
