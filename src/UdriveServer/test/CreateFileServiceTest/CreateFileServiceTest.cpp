#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../main/include/server/Services/CreateFileService.h"
#include "CreateFileServiceFixture.h"

using ::testing::Return;
using ::testing::_;

#include "../../main/include/utilities/easylogging++.h"
INITIALIZE_EASYLOGGINGPP
#define ELPP_DISABLE_LOGS

TEST_F(CreateFileServiceFixture,invalidUsername) {

	EXPECT_CALL(userDB,getValue( username ) )
		.WillOnce(Return(""));

	std::string responseFromService = createFileService->execute( username, token, "" , "" );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ(	ERROR, jsonData["result"].asCString() );
	EXPECT_EQ(	 jsonData["errorCode"] , HttpResponse::ERROR_AUTHENTICATION );
}

TEST_F(CreateFileServiceFixture,invalidToken) {

	userNotSavedInDb.setToken("555");
	std::string data2 = userNotSavedInDb.getJsonString();
	EXPECT_CALL(userDB,getValue( username ) )
			.WillOnce(Return(data2));

	std::string responseFromService = createFileService->execute( username, token, "" , "" );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ(	ERROR, jsonData["result"].asCString() );
	EXPECT_EQ(	 jsonData["errorCode"] , HttpResponse::ERROR_AUTHENTICATION );
}

TEST_F(CreateFileServiceFixture,invalidFolderParent) {

	EXPECT_CALL(userDB,getValue( username ) )
			.WillOnce(Return(dataUser));

	Json::Value jsonFolderData;
	jsonFolderData["name"] 	 	= folderName;
	jsonFolderData["id"] 	= pathNewFolder;
	Folder folderBuscada(jsonFolderData);

	Json::StreamWriterBuilder builder;
	Json::Value jsonFileHeader;
	jsonFileHeader["name"] 	 	= fileName;
	jsonFileHeader["idFolder"] 	= pathNewFolder;
	jsonFileHeader["extension"] = extension;
	jsonFileHeader["data"]		= dataTxtFile;
	builder.settings_["indentation"] = "\t";
	std::string fileHeader =  Json::writeString(builder,jsonFileHeader);

	EXPECT_CALL(folderDB,getValue( pathNewFolder ) )
					.WillOnce(Return( "" ));

	std::string responseFromService = createFileService->execute( username, token, fileHeader , "" );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ(	ERROR, jsonData["result"].asCString() );
	EXPECT_EQ(	 jsonData["errorCode"] , HttpResponse::ERROR_INVALID_FOLDER_PARENT );

}

TEST_F(CreateFileServiceFixture, errorSavingData) {

	EXPECT_CALL(userDB,getValue( username ) )
			.WillRepeatedly(Return(dataUser));

	Json::Value jsonFolderData;
	jsonFolderData["name"] 	 	= folderName;
	jsonFolderData["id"] 	= pathNewFolder;
	Folder folderBuscada(jsonFolderData);

	Json::StreamWriterBuilder builder;
	Json::Value jsonFileHeader;
	jsonFileHeader["name"] 	 	= fileName;
	jsonFileHeader["idFolder"] 	= pathNewFolder;
	jsonFileHeader["extension"] = extension;
	jsonFileHeader["data"]		= dataTxtFile;
	builder.settings_["indentation"] = "\t";
	std::string fileHeader =  Json::writeString(builder,jsonFileHeader);

	EXPECT_CALL(folderDB,getValue(jsonFileHeader.get("idFolder", "").asCString()) )
					.WillOnce(Return( folderBuscada.getJsonString() ));

	EXPECT_CALL(userDB,saveValue( _ , _ ))
		.WillOnce(Return(true));

	EXPECT_CALL(fileDB,saveValue( _ , _ ))
		.WillOnce(Return(true));

	EXPECT_CALL(dataDB,saveValue( _ , _ ))
		.WillOnce(Return(true));

	EXPECT_CALL(folderDB,saveValue( _ , _ ))
			.WillOnce(Return(false));

	std::string responseFromService = createFileService->execute( username, token, fileHeader , "" );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ(	ERROR, jsonData["result"].asCString() );
	EXPECT_EQ(	 jsonData["errorCode"] , HttpResponse::ERROR_SAVING_DATA );

}

TEST_F(CreateFileServiceFixture, errorFileExists) {
//TODO
}

TEST_F(CreateFileServiceFixture,createFileServiceOK) {

	EXPECT_CALL(userDB,getValue( username ) )
	.WillOnce(Return(dataUser))
	.WillOnce(Return(dataUser));

	Json::Value jsonFolderData;
	jsonFolderData["name"] 	 	= folderName;
	jsonFolderData["id"] 	= pathNewFolder;
	Folder folderBuscada(jsonFolderData);

	Json::StreamWriterBuilder builder;
	Json::Value jsonFileHeader;
	jsonFileHeader["name"] 	 	= fileName;
	jsonFileHeader["idFolder"] 	= pathNewFolder;
	jsonFileHeader["extension"] = extension;
	jsonFileHeader["data"]		= dataTxtFile;
	builder.settings_["indentation"] = "\t";
	std::string fileHeader =  Json::writeString(builder,jsonFileHeader);

	EXPECT_CALL(folderDB,getValue(jsonFileHeader.get("idFolder", "").asCString()) )
					.WillOnce(Return( folderBuscada.getJsonString() ));


	EXPECT_CALL( userDB, saveValue( username , _ ) )
	.WillOnce(Return( true ));

	EXPECT_CALL( folderDB, saveValue( _ , _ ) )
	.WillOnce(Return( true ));

	EXPECT_CALL( fileDB, saveValue( _ , _ ) )
	.WillOnce(Return( true ));

	EXPECT_CALL( dataDB, saveValue( _ , dataTxtFile ) )
	.WillOnce(Return( true ));

	std::string responseFromService = createFileService->execute( username, token, fileHeader , "" );

	Json::Value jsonData;
	Json::Reader reader;
	reader.parse( responseFromService, jsonData);

	EXPECT_EQ(	OK 	 , jsonData["result"].asCString() );
	//std::string idFile = folderName + "/" + fileName + "." + extension;
	EXPECT_EQ(	fileName 	 , jsonData["data"]["name"].asCString()  );
	EXPECT_EQ(	extension 	 , jsonData["data"]["extension"].asCString()  );
	int versionResponse = jsonData["data"]["version"].asInt();
	EXPECT_EQ(	version 	 , versionResponse  );
	EXPECT_EQ( username ,jsonData["data"]["owner"].asCString() );
}



int main(int argc, char *argv[]){
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
