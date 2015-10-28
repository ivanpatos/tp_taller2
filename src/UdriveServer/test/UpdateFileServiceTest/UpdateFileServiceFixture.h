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

using ::testing::Test;

class UpdateFileServiceFixture: public Test {
public:

	UpdateFileServiceFixture( ) : userNotSavedInDb(getJsonUser("tomRea", "123456", "tomRea@gmail.com")){

		updateFileService = new UpdateFileService(userDB,folderDB,fileDB,dataDB);
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

   ~UpdateFileServiceFixture( ) {
	   delete updateFileService;
   }

   User userNotSavedInDb;

   UpdateFileService* updateFileService;

   MockDatabase userDB, folderDB, fileDB, dataDB;

   std::string data, username , token = "666", query, mail;

   std::string OK = "OK", ERROR = "ERROR";
};



#endif /* TEST_UPDATEFILESERVICEFIXTURETEST_H_ */
