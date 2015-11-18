#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include "../../main/include/resources/File.h"
#include "../../main/include/database/MockDatabase.h"
#include "../Utils/Utils.h"


const unsigned int VERSION = 1;

#include "../../main/include/utilities/easylogging++.h"
INITIALIZE_EASYLOGGINGPP
#define ELPP_DISABLE_LOGS

using ::testing::_;

TEST(FileTest, addUsers) {
	//MockDB
	MockDatabase userDB;
	//Expect call getValue in File constructor
	EXPECT_CALL(userDB,getValue(_)).Times(1);

	File file(getJsonFile("id","file","pdf",VERSION), userDB);
	std::vector<User*> expected;

	//Create users
	Json::Value juan = getJsonUser("juan","xyz","juan@bla.com");
	Json::Value tito = getJsonUser("tito","xyz","tito@bla.com");
	User *user1 = new User(juan);
	User *user2 = new User(tito);

	//Add users to expected vector
	expected.push_back(user2);
	expected.push_back(user1);
	//Add user to file
	file.addUser(user1);
	file.addUser(user2);


	//Expected
	EXPECT_TRUE(compareVectors<User*>(file.getUsers(), expected));

}

TEST(FileTest, removeUsers){
	MockDatabase userDB;
	//Expect call getValue in File constructor
	EXPECT_CALL(userDB,getValue(_)).Times(1);

	File file(getJsonFile("id","file","pdf", VERSION), userDB);
	std::vector<User*> expected;

	//Create users
	User *user1 = new User(getJsonUser("juan","xyz","juan@bla.com"));
	User *user2 = new User(getJsonUser("tito","xyz","tito@bla.com"));

	//Add user to file
	file.addUser(user1);
	file.addUser(user2);

	//remove user
	file.removeUser(*user1);

	//expected user
	expected.push_back(user2);

	//Expected
	EXPECT_TRUE(compareVectors<User*>(file.getUsers(), expected));

}

TEST(FileTest, hasPermission){
	MockDatabase userDB;

	//Expect call getValue in File constructor
	EXPECT_CALL(userDB,getValue(_)).Times(1);
	File file(getJsonFile("id","algo.txt","", VERSION), userDB);

	//Create users
	User *user1 = new User(getJsonUser("juan","xyz","juan@bla.com"));
	User *user2 = new User(getJsonUser("tito","xyz","tito@bla.com"));

	//Add user to file
	file.addUser(user1);

	EXPECT_TRUE(file.hasPermission(*user1));
	EXPECT_FALSE(file.hasPermission(*user2));

	delete user2;
}

TEST(FileTest, increaseVersion){
	MockDatabase userDB;

	//Expect call getValue in File constructor
	EXPECT_CALL(userDB,getValue(_)).Times(1);
	File file(getJsonFile("id","file","txt", VERSION), userDB);

	//increase version
	file.increaseVersion();
	EXPECT_EQ(file.getVersion(), VERSION +1);
}



int main(int argc, char *argv[]){
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
