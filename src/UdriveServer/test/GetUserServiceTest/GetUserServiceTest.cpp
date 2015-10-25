#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../main/include/server/Services/GetUserService.h"
#include "GetUserServiceFixture.h"

using ::testing::Return;
using ::testing::_;

TEST_F(GetUserServiceFixture,getUserQueryServiceOK) {

	query = username;

	EXPECT_CALL(userDB,getValue( username ) )
	.WillOnce(Return(data))
	.WillOnce(Return(data));

	std::string responseFromService = getUserService->execute( username, token, data , query );

	std::cout <<"response from service: " << responseFromService << std::endl;

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	std::cout << "response json data" << jsonData << std::endl;

	std::cout << "result" << jsonData["result"] << std::endl;

	std::string ok = "OK";
	EXPECT_EQ( ok , jsonData["result"].asCString() );
	EXPECT_EQ( username , jsonData["data"]["username"].asCString()  );
	EXPECT_EQ( mail , jsonData["data"]["mail"].asCString()  );

}

TEST_F(GetUserServiceFixture,getAllUsersServiceOK) {

	query = "";

	EXPECT_CALL(userDB,getValue( username ) )
	.WillOnce(Return(data));

	EXPECT_CALL(userDB,getAllValues() )
	.WillOnce(Return(allUsers));

	std::string responseFromService = getUserService->execute( username, token, data , query );

	std::cout <<"response from service: " << responseFromService << std::endl;

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	std::cout << "response json data" << jsonData << std::endl;

	std::cout << "result" << jsonData["result"] << std::endl;

	std::string ok = "OK";
	EXPECT_EQ( ok , jsonData["result"].asCString() );
	EXPECT_EQ( userNotSavedInDb2.getUsername() , jsonData["data"][1]["username"].asCString()  );
	EXPECT_EQ( userNotSavedInDb2.getEmail() , jsonData["data"][1]["mail"].asCString()  );

}

int main(int argc, char *argv[]){
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
