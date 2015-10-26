/*
 * UpdateUserServiceFixture.h
 *
 *  Created on: Oct 25, 2015
 *      Author: tomrea
 */

#ifndef TEST_UPDATEUSERSERVICETEST_UPDATEUSERSERVICEFIXTURE_H_
#define TEST_UPDATEUSERSERVICETEST_UPDATEUSERSERVICEFIXTURE_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../main/include/database/MockDatabase.h"
#include "../../main/include/server/HttpResponse.h"
#include "../Utils/Utils.h"
#include "../../main/include/resources/User.h"

using ::testing::Test;

class UpdateUserServiceFixture: public Test {
public:

	UpdateUserServiceFixture() : userNotSavedInDb(getJsonUser("tomRea", "123456", "tomRea@gmail.com")) {

		updateUserService = new UpdateUserService(userDB);
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

   ~UpdateUserServiceFixture( ) {
	   delete updateUserService;
   }

   User userNotSavedInDb;

   UpdateUserService* updateUserService;

   MockDatabase userDB;

   std::string data, username , token = "666", query, mail;

   std::string OK = "OK", ERROR = "ERROR";
};



#endif /* TEST_UPDATEUSERSERVICETEST_UPDATEUSERSERVICEFIXTURE_H_ */
