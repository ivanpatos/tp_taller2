/*
 * CreateFileServiceFixture.h
 *
 *  Created on: Oct 26, 2015
 *      Author: tomrea
 */

#ifndef TEST_CREATEFILESERVICEFIXTURETEST_H_
#define TEST_CREATEFILESERVICEFIXTURETEST_H_

#include "../../main/include/database/MockDatabase.h"
#include "../../main/include/server/HttpResponse.h"
#include "../Utils/Utils.h"
#include "../../main/include/resources/User.h"
#include "../../main/include/resources/Folder.h"

using ::testing::Test;

class CreateFileServiceFixture: public Test {
public:

	CreateFileServiceFixture( ) : userNotSavedInDb(getJsonUser("tomRea", "123456", "tomRea@gmail.com")){
		createFileService = new CreateFileService(userDB,folderDB,fileDB,dataDB);
	}

	void SetUp( ) {
		userNotSavedInDb.setToken(token);
		dataUser = userNotSavedInDb.getJsonString();
		username = userNotSavedInDb.getUsername();
		mail = userNotSavedInDb.getEmail();
		query = "";
		pathNewFolder = username + "/" + folderName;
	}

   void TearDown( ) {
   }

   ~CreateFileServiceFixture( ) {
	   delete createFileService;
   }

   User userNotSavedInDb;

   CreateFileService* createFileService;

   MockDatabase userDB, folderDB, fileDB,dataDB;

   std::string dataUser, username , token = "666", query, mail;

   std::string OK = "OK", ERROR = "ERROR";

   std::string fileName="archivoCopado";
   std::string extension="txt";
   std::string dataTxtFile="esto es un archivo de texto";
   int version = 1;

   std::string folderName = "folder1";
   std::string pathNewFolder;
};




#endif /* TEST_CREATEFILESERVICEFIXTURETEST_H_ */
