/*
 * UpdateFileServiceFixture.h
 *
 *  Created on: Oct 26, 2015
 *      Author: tomrea
 */

#ifndef TEST_UPDATEFILESERVICEFIXTURETEST_H_
#define TEST_UPDATEFILESERVICEFIXTURETEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../main/include/database/MockDatabase.h"
#include "../../main/include/server/HttpResponse.h"
#include "../Utils/Utils.h"
#include "../../main/include/resources/User.h"
#include "../../main/include/resources/File.h"
#include "../../main/include/resources/Folder.h"

using ::testing::Test;

class UpdateFileServiceFixture: public Test {
public:

	UpdateFileServiceFixture( ) : userNotSavedInDb(getJsonUser("tomRea", "123456", "tomRea@gmail.com")){
		updateFileService = new UpdateFileService(userDB,folderDB,fileDB,dataDB);
		fileBuscado = NULL;
		std::cout << "UpdateFileServiceFixture" << std::endl;
	}

	void SetUp( ) {
		userNotSavedInDb.setToken(token);
		dataUser = userNotSavedInDb.getJsonString();
		username = userNotSavedInDb.getUsername();
		mail = userNotSavedInDb.getEmail();
		query = "";
		pathNewFolder = username + "/" + folderName;
		fileId = folderName + "/" + fileName + "." + extension + "," + "12345";
		jsonFileData["name"] 	 	= fileName;
		jsonFileData["id"]			= fileId;
		jsonFileData["extension"] 	= extension;
		jsonFileData["data"]		= dataTxtFile;
		jsonFileData["version"]		= 1;
		jsonFileData["owner"]		= username;
		jsonFileData["lastUser"]	= username;
		jsonFileData["deleted"]		= 0;

		Json::StreamWriterBuilder builder;
		builder.settings_["indentation"] = "\t";
		stringJsonFileChange =  Json::writeString(builder,jsonFileData);

	}

   void TearDown( ) {
   }

   ~UpdateFileServiceFixture( ) {
	   delete updateFileService;
		std::cout << "delete" << std::endl;
   }

   User userNotSavedInDb;

   UpdateFileService* updateFileService;

   MockDatabase userDB, folderDB, fileDB,dataDB;

   std::string dataUser, username , token = "666", query, mail;

   std::string OK = "OK", ERROR = "ERROR";

   std::string fileName="archivoCopado";
   std::string extension="txt";
   std::string dataTxtFile="esto es un archivo de texto";
   int version = 1;

   std::string folderName = "folder1";
   std::string pathNewFolder;
   std::string fileId;

   File* fileBuscado;
   Json::Value jsonFileData;
   std::string stringJsonFileChange;

   std::string nuevoNombre = "NUEVO_NOMBRE";
   std::string nuevaLabel = "taggeado";

};



#endif /* TEST_UPDATEFILESERVICEFIXTURETEST_H_ */
