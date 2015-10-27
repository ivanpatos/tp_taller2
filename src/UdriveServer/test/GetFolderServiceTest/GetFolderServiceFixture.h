/*
 * CreateFolderServiceFixture.h
 *
 *  Created on: Oct 26, 2015
 *      Author: tomrea
 */

#ifndef TEST_GETFOLDERSERVICETEST_GETFOLDERSERVICEFIXTURE_H_
#define TEST_GETFOLDERSERVICETEST_GETFOLDERSERVICEFIXTURE_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../main/include/database/MockDatabase.h"
#include "../../main/include/server/HttpResponse.h"
#include "../Utils/Utils.h"
#include "../../main/include/resources/User.h"
#include "../../main/include/resources/Folder.h"

using ::testing::Test;

class GetFolderServiceFixture: public Test {
public:

	GetFolderServiceFixture( ) : userNotSavedInDb(getJsonUser("tomRea", "123456", "tomRea@gmail.com")){

		getFolderService = new GetFolderService(userDB,folderDB,fileDB);
	}

	void SetUp( ) {
		userNotSavedInDb.setToken(token);
		data = userNotSavedInDb.getJsonString();
		username = userNotSavedInDb.getUsername();
		mail = userNotSavedInDb.getEmail();
		query = "";
	}

   void TearDown( ) {
   }

   ~GetFolderServiceFixture( ) {
	   delete getFolderService;
   }

   User userNotSavedInDb;

   GetFolderService* getFolderService;

   MockDatabase userDB, folderDB, fileDB;

   std::string data, username , token = "666", query, mail;

   std::string OK = "OK", ERROR = "ERROR";
};



#endif /* TEST_GETFOLDERSERVICETEST_GETFOLDERSERVICEFIXTURE_H_ */
