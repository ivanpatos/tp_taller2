#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../main/include/server/Services/UpdateUserService.h"
#include "UpdateUserServiceFixture.h"

using ::testing::Return;
using ::testing::_;

#include "../../main/include/utilities/easylogging++.h"
INITIALIZE_EASYLOGGINGPP
#define ELPP_DISABLE_LOGS

TEST_F(UpdateUserServiceFixture,updateUserServiceOK) {

	User originalUser( getJsonUser( username, "123456", "xxx@xxxx.com"));
	originalUser.setToken(token);

	EXPECT_CALL(userDB,getValue( username ) )
	.WillOnce(Return( originalUser.getJsonString() ));

	EXPECT_CALL(userDB,saveValue( username , data ))
	.WillOnce(Return(true));

	std::string responseFromService = updateUserService->execute( username, token, data , query );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ(	OK 	 , jsonData["result"].asCString() );
	EXPECT_EQ( 	username , jsonData["data"]["username"].asCString()  );
	EXPECT_EQ(	mail 	 , jsonData["data"]["mail"].asCString()  );
}

TEST_F(UpdateUserServiceFixture,updateUserServiceUserNonExisting) {

	User originalUser( getJsonUser( username, "999", "xxx@xxxx.com"));
	originalUser.setToken(token);

	//esto representa que el objeto no es encontrado en la database
	EXPECT_CALL(userDB,getValue( username ) )
	.WillOnce(Return( "" ));

	std::string responseFromService = updateUserService->execute( username, token, data , query );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ(	ERROR 	 , jsonData["result"].asCString() );
	EXPECT_EQ(	jsonData["errorCode"], HttpResponse::ERROR_AUTHENTICATION );
}

TEST_F(UpdateUserServiceFixture,updateUserServiceUserWrongToken) {

	User originalUser( getJsonUser( username, "999", "xxx@xxxx.com"));
	originalUser.setToken("1111111111111");

	EXPECT_CALL(userDB,getValue( username ) )
	.WillOnce(Return( originalUser.getJsonString() ));

	std::string responseFromService = updateUserService->execute( username, token, data , query );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ(	ERROR 	 , jsonData["result"].asCString() );
	EXPECT_EQ(	jsonData["errorCode"], HttpResponse::ERROR_AUTHENTICATION );
}

TEST_F(UpdateUserServiceFixture,updateUserServiceUserFailureAtSaving) {

	User originalUser( getJsonUser( username, "123456", "xxx@xxxx.com"));
	originalUser.setToken(token);

	EXPECT_CALL(userDB,getValue( username ) )
	.WillOnce(Return( originalUser.getJsonString() ));

	//esto representa un error al salvar
	EXPECT_CALL(userDB,saveValue( username , data ))
	.WillOnce(Return(false));

	std::string responseFromService = updateUserService->execute( username, token, data , query );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ(	ERROR 	 , jsonData["result"].asCString() );
	EXPECT_EQ(	jsonData["errorCode"], HttpResponse::ERROR_SAVING_DATA );
}

int main(int argc, char *argv[]){
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
