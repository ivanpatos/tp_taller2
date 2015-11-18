#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include "../../main/include/resources/File.h"
#include "../../main/include/resources/Folder.h"
#include "../../main/include/database/MockDatabase.h"
#include "../Utils/Utils.h"

const unsigned int VERSION = 1;

#include "../../main/include/utilities/easylogging++.h"
INITIALIZE_EASYLOGGINGPP
#define ELPP_DISABLE_LOGS

using ::testing::_;
TEST(FolderTest, addFolderChildren){

	Folder folder(getJsonFolder("1","folder"));
	Folder *children1 = new Folder(getJsonFolder("9","children1"));
	Folder *children2 = new Folder(getJsonFolder("9","children2"));
	folder.addFolderChildren(children1);
	folder.addFolderChildren(children2);

	//Add folder to expected vector
	std::vector<Folder*> expected;
	expected.push_back(children2);
	expected.push_back(children1);

	//Expected
	EXPECT_TRUE(compareVectors<Folder*>(folder.getFolderChildren(), expected));

}

TEST(FolderTest, addFileChildren){
	Folder folder(getJsonFolder("1","folder"));
	MockDatabase userDB;
	//Expect call getValue in File constructor
	EXPECT_CALL(userDB,getValue(_)).Times(2);
	File *children1 = new File(getJsonFile("id1","children1","txt", VERSION), userDB);
	File *children2 = new File(getJsonFile("id2","children1","pdf", VERSION), userDB);
	folder.addFileChildren(children1);
	folder.addFileChildren(children2);

	//Add folder to expected vector
	std::vector<File*> expected;
	expected.push_back(children2);
	expected.push_back(children1);

	//Expected
	EXPECT_TRUE(compareVectors<File*>(folder.getFileChildren(), expected));
}

TEST(FolderTest, removeFileChildren){
	Folder folder(getJsonFolder("1","folder"));
	MockDatabase userDB;
	//Expect call getValue in File constructor
	EXPECT_CALL(userDB,getValue(_)).Times(2);
	File *children1 = new File(getJsonFile("id1","children1","txt", VERSION), userDB);
	File *children2 = new File(getJsonFile("id2","children1","pdf", VERSION), userDB);
	folder.addFileChildren(children1);
	folder.addFileChildren(children2);

	//Add folder to expected vector
	std::vector<File*> expected;
	expected.push_back(children2);

	folder.removeFileChildren(children1);

	//Expected
	EXPECT_TRUE(compareVectors<File*>(folder.getFileChildren(), expected));
}

TEST(FolderTest, hasFolder){
	Folder folder(getJsonFolder("1","folder"));
	Folder *children1 = new Folder(getJsonFolder("9","children1"));
	Folder *children2 = new Folder(getJsonFolder("9","children2"));
	folder.addFolderChildren(children1);

	EXPECT_TRUE(folder.hasFolder("children1"));
	EXPECT_FALSE(folder.hasFolder("children2"));
}

TEST(FolderTest, hasFile){
	Folder folder(getJsonFolder("1","folder"));
	MockDatabase userDB;
	//Expect call getValue in File constructor
	EXPECT_CALL(userDB,getValue(_)).Times(2);
	File *children1 = new File(getJsonFile("id1","children1","txt", VERSION), userDB);
	File *children2 = new File(getJsonFile("id2","children2","pdf", VERSION), userDB);

	//add files and check
	folder.addFileChildren(children1);
	folder.addFileChildren(children2);
	EXPECT_TRUE(folder.hasFile("children1","txt"));
	EXPECT_TRUE(folder.hasFile("children2","pdf"));

	//remove file and check
	folder.removeFileChildren(children2);
	EXPECT_FALSE(folder.hasFile("children2","pdf"));

}

TEST(FolderTest, setName){
	Folder folder(getJsonFolder("1","folder"));
	std::string newName = "newNameFolder";
	folder.setName(newName);
	EXPECT_EQ(folder.getName(), newName);
}

int main(int argc, char *argv[]){
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
