/*
 * CreateFileServiceFixture.h
 *
 *  Created on: Oct 26, 2015
 *      Author: tomrea
 */

#ifndef TEST_CREATEFILESERVICEFIXTURETEST_H_
#define TEST_CREATEFILESERVICEFIXTURETEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../main/include/database/MockDatabase.h"
#include "../../main/include/server/HttpResponse.h"
#include "../Utils/Utils.h"
#include "../../main/include/resources/User.h"
#include "../../main/include/resources/File.h"

using ::testing::Test;

class CreateFileServiceFixture: public Test {
public:

	CreateFileServiceFixture( ) : userNotSavedInDb(getJsonUser("tomRea", "123456", "tomRea@gmail.com")){

		createFileService = new CreateFileService(userDB,folderDB,fileDB,dataDB);
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

   ~CreateFileServiceFixture( ) {
	   delete createFileService;
   }

   User userNotSavedInDb;

   CreateFileService* createFileService;

   MockDatabase userDB, folderDB, fileDB, dataDB;

   std::string data, username , token = "666", query, mail;

   std::string OK = "OK", ERROR = "ERROR";
};



#endif /* TEST_CREATEFILESERVICEFIXTURETEST_H_ */
