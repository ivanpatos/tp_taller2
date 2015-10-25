#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../main/include/server/Services/CreateUserService.h"
#include "../../main/include/database/MockDatabase.h"
#include "../../main/include/server/HttpResponse.h"
#include "../Utils/Utils.h"
#include "../../main/include/resources/User.h"

using ::testing::Return;
using ::testing::_;

//TODO: REFACTORIZAR ESTO usando un FIXTURE, como hice con GetUserService !!!!!
TEST(CreateUserServiceTest,createUserServiceOK) {

	User userNotSavedInDb = User(getJsonUser("tomRea","123456","tomRea@gmail.com"));

	std::string data = userNotSavedInDb.getJsonString(), username = userNotSavedInDb.getUsername(), token = "", query = "" ;

	MockDatabase userDB, folderDB;

	EXPECT_CALL(userDB,getValue( username ) )
	.WillOnce(Return(""));

	EXPECT_CALL(userDB,saveValue( username , _ ))
	.WillOnce(Return(true));

	EXPECT_CALL(folderDB,saveValue(_,_))
	.WillRepeatedly(Return(true));

	Service* createUserService = new CreateUserService( userDB, folderDB);

	std::string responseFromService = createUserService->execute( username, token, data , query );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ( jsonData["result"] , "OK" );
	EXPECT_EQ( jsonData["data"]["username"] , username );
	EXPECT_EQ( jsonData["data"]["mail"] , "tomRea@gmail.com"  );

	delete createUserService;
}

TEST(CreateUserServiceTest,userAlreadyExists) {

	User userNotSavedInDb = User(getJsonUser("tomRea","123456","tomRea@gmail.com"));

	std::string data = userNotSavedInDb.getJsonString(), username = userNotSavedInDb.getUsername(), token = "", query = "" ;

	MockDatabase userDB, folderDB;

	//esto simboliza que el usuario SI estaba en la base de datos
	EXPECT_CALL(userDB,getValue( username ) )
	.WillOnce(Return(data));

	Service* createUserService = new CreateUserService( userDB, folderDB );

	std::string responseFromService = createUserService->execute( username, token, data , query );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ( jsonData["result"] , "ERROR" );
	EXPECT_EQ( jsonData["errorCode"] , HttpResponse::ERROR_USERNAME_EXISTS );

	delete createUserService;
}

TEST(CreateUserServiceTest,userNameMissing){

	User userNotSavedInDb = User(getJsonUser("","123456","tomRea@gmail.com"));

	std::string data = userNotSavedInDb.getJsonString(), username = userNotSavedInDb.getUsername(), token = "", query = "" ;

	MockDatabase userDB, folderDB;

	EXPECT_CALL(userDB,getValue( username ) )
	.WillOnce(Return(""));

	Service* createUserService = new CreateUserService( userDB, folderDB );

	std::string responseFromService = createUserService->execute( username, token, data , query );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ( jsonData["result"] , "ERROR" );
	EXPECT_EQ( jsonData["errorCode"] , HttpResponse::ERROR_USERNAME_MISSING );

	delete createUserService;
}

TEST(CreateUserServiceTest,passMissing){

	User userNotSavedInDb = User(getJsonUser("tomRea","","tomRea@gmail.com"));

	std::string data = userNotSavedInDb.getJsonString(), username = userNotSavedInDb.getUsername(), token = "", query = "" ;

	MockDatabase userDB, folderDB;

	EXPECT_CALL(userDB,getValue( username ) )
	.WillOnce(Return(""));

	Service* createUserService = new CreateUserService( userDB, folderDB );

	std::string responseFromService = createUserService->execute( username, token, data , query );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ( jsonData["result"] , "ERROR" );
	EXPECT_EQ( jsonData["errorCode"] , HttpResponse::ERROR_PASSWORD_MISSING );

	delete createUserService;
}



int main(int argc, char *argv[]){
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
