/*
 * CreateUserServiceFixture.h
 *
 *  Created on: Oct 25, 2015
 *      Author: tomrea
 */

#ifndef TEST_CREATEUSERSERVICETEST_CREATEUSERSERVICEFIXTURE_H_
#define TEST_CREATEUSERSERVICETEST_CREATEUSERSERVICEFIXTURE_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../main/include/database/MockDatabase.h"
#include "../../main/include/server/HttpResponse.h"
#include "../Utils/Utils.h"
#include "../../main/include/resources/User.h"

using ::testing::Test;

class CreateUserServiceFixture: public Test {
public:

	CreateUserServiceFixture( ) : userNotSavedInDb(getJsonUser("tomRea", "123456", "tomRea@gmail.com")){

		createUserService = new CreateUserService(userDB,folderDB);
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

   ~CreateUserServiceFixture( ) {
	   delete createUserService;
   }

   User userNotSavedInDb;

   CreateUserService* createUserService;

   MockDatabase userDB, folderDB;

   std::string data, username , token = "666", query, mail;

   std::string OK = "OK", ERROR = "ERROR";
};



#endif /* TEST_CREATEUSERSERVICETEST_CREATEUSERSERVICEFIXTURE_H_ */
