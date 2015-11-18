#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../../main/include/resources/User.h"

#include "../../main/include/utilities/easylogging++.h"
INITIALIZE_EASYLOGGINGPP
#define ELPP_DISABLE_LOGS

TEST(UserTest, fromJsonParameter){
	Json::Value valueInput(Json::objectValue);
	valueInput["username"] = "JuanPerez";
	valueInput["password"] = "holamundo";
	valueInput["mail"] = "juanperez@gmail.com";
	valueInput["profilePicture"] = "";
	valueInput["location"] = "";
	valueInput["token"] = "";
	User user(valueInput);

	EXPECT_EQ(user.getUsername(), "JuanPerez");
	EXPECT_EQ(user.getPassword(), "holamundo");
	EXPECT_EQ(user.getToken(), "");
}

TEST(UserTest, fromStringParameter){
	std::string input = "{\n\t\"lastLocation\" : \"\",\n\t\"mail\" : \"juanperez@gmail.com\",\n\t\"name\" : \"\",\n\t\"password\" : \"holamundo\",\n\t\"profilePicture\" : \"\",\n\t\"token\" : \"\",\n\t\"username\" : \"JuanPerez\"\n}";
	User user(input);

	EXPECT_EQ(user.getUsername(), "JuanPerez");
	EXPECT_EQ(user.getPassword(), "holamundo");
	EXPECT_EQ(user.getToken(), "");
}

TEST(UserTest, updateProfile ) {
	std::string input = "{\n\t\"lastLocation\" : \"\",\n\t\"mail\" : \"juanperez@gmail.com\",\n\t\"name\" : \"\",\n\t\"password\" : \"holamundo\",\n\t\"profilePicture\" : \"\",\n\t\"token\" : \"\",\n\t\"username\" : \"JuanPerez\"\n}";
	User user(input);
	EXPECT_EQ(user.getUsername(), "JuanPerez");
	EXPECT_EQ(user.getPassword(), "holamundo");
	EXPECT_EQ(user.getToken(), "");

	std::string inputUpdate = "{\n\t\"lastLocation\" : \"\",\n\t\"mail\" : \"nestorcarlos@gmail.com\",\n\t\"name\" : \"\",\n\t\"password\" : \"newpassword\",\n\t\"profilePicture\" : \"\",\n\t\"token\" : \"othertoken\",\n\t\"username\" : \"NestorCarlos\"\n}";
	user.updateProfile(inputUpdate);
	EXPECT_EQ(user.getEmail(), "nestorcarlos@gmail.com");
}


int main(int argc, char *argv[]){
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
