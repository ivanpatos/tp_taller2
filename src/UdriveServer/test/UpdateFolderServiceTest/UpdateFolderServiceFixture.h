/*
 * UpdateFolderServiceFixture.h
 *
 *  Created on: Oct 26, 2015
 *      Author: tomrea
 */

#ifndef TEST_UPDATEFOLDERERVICEFIXTURETEST_H_
#define TEST_UPDATEFOLDERERVICEFIXTURETEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../main/include/database/MockDatabase.h"
#include "../../main/include/server/HttpResponse.h"
#include "../Utils/Utils.h"
#include "../../main/include/resources/User.h"
#include "../../main/include/resources/File.h"
#include "../../main/include/resources/Folder.h"

using ::testing::Test;

class UpdateFolderServiceFixture: public Test {
public:

	UpdateFolderServiceFixture( ) : userNotSavedInDb(getJsonUser("tomRea", "123456", "tomRea@gmail.com")){
		updateFolderService = new UpdateFolderService(userDB,folderDB,fileDB,dataDB);
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

   ~UpdateFolderServiceFixture( ) {
	   delete updateFolderService;
   }

   User userNotSavedInDb;

   UpdateFolderService* updateFolderService;

   MockDatabase userDB, folderDB, fileDB,dataDB;

   std::string dataUser, username , token = "666", query, mail;

   std::string OK = "OK", ERROR = "ERROR";

   std::string folderName = "folder1";
   std::string pathNewFolder;

   std::string nuevoNombre = "NUEVO_NOMBRE";
   std::string nuevaLabel = "taggeado";

};



#endif /* TEST_UPDATEFOLDERERVICEFIXTURETEST_H_ */
