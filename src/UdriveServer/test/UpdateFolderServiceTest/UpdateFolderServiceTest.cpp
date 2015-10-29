#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../main/include/server/Services/UpdateFolderService.h"

#include "UpdateFolderServiceFixture.h"

using ::testing::Return;
using ::testing::_;

TEST_F(UpdateFolderServiceFixture, updateFolderOk) {

	EXPECT_CALL(userDB,getValue( username ) )
		.WillRepeatedly(Return(dataUser));

	Json::Value jsonFolder;
	jsonFolder["id"] = pathNewFolder;
	jsonFolder["name"] = "xxxxxxxxxxxxxxxxxxxxxxxxx";
	Folder folder(jsonFolder);

	EXPECT_CALL(folderDB,getValue( pathNewFolder ) )
		.WillRepeatedly(Return( folder.getJsonString() ));

	Json::Value jsonRoot;
	jsonRoot["id"] = username;
	jsonRoot["name"] = "root";
	Folder rootFolder(jsonRoot);

	//rootFolder.addFolderChildren(&folder);

	EXPECT_CALL(folderDB,getValue( username ) )
		.WillRepeatedly(Return( rootFolder.getJsonString()));

	EXPECT_CALL(folderDB,saveValue( pathNewFolder, _ ) )
		.WillRepeatedly(Return( true ));

	EXPECT_CALL(folderDB,saveValue( username, _ ) )
		.WillRepeatedly(Return( true ));

	Json::Value jsonData;
	jsonData["name"] = "FIUBA_FOLDER";
	Json::StreamWriterBuilder builder;
	builder.settings_["indentation"] = "\t";
	std::string folderChange =  Json::writeString(builder,jsonData);

	std::string responseFromService = updateFolderService->execute( username, token, folderChange , pathNewFolder );

	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	std::string folderName = "FIUBA_FOLDER";
	EXPECT_EQ(	OK 	 , jsonData["result"].asCString() );
	EXPECT_EQ( 	pathNewFolder , jsonData["data"]["id"].asCString()  );
	EXPECT_EQ(	folderName 	 , jsonData["data"]["name"].asCString()  );
}


int main(int argc, char *argv[]){
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
