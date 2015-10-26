/*
 * GetUserServiceFixture.h
 *
 *  Created on: Oct 25, 2015
 *      Author: tomrea
 */
#ifndef TEST_GETUSERSERVICETEST_GETUSERSERVICEFIXTURE_H_
#define TEST_GETUSERSERVICETEST_GETUSERSERVICEFIXTURE_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../main/include/database/MockDatabase.h"
#include "../../main/include/server/HttpResponse.h"
#include "../Utils/Utils.h"
#include "../../main/include/resources/User.h"

using ::testing::Test;

class GetUserServiceFixture: public Test {
public:

	GetUserServiceFixture( ) : userNotSavedInDb(getJsonUser("tomRea", "123456", "tomRea@gmail.com")),
							   userNotSavedInDb2(getJsonUser("julian","1678902","julian@fiuba.com")) {

		getUserService = new GetUserService(userDB);

	}

	void SetUp( ) {
		userNotSavedInDb.setToken(token);
		data = userNotSavedInDb.getJsonString();
		username = userNotSavedInDb.getUsername();
		mail = userNotSavedInDb.getEmail();
		query = "";

		allUsers.push_back(data);
		allUsers.push_back(userNotSavedInDb2.getJsonString());
	}

   void TearDown( ) {
   }

   ~GetUserServiceFixture( ) {
	   delete getUserService;
   }

   User userNotSavedInDb;

   GetUserService* getUserService;

   MockDatabase userDB;

   std::string data, username , token = "666", query, mail;

   User userNotSavedInDb2;

   std::vector<std::string> allUsers;
};



#endif /* TEST_GETUSERSERVICETEST_GETUSERSERVICEFIXTURE_H_ */
