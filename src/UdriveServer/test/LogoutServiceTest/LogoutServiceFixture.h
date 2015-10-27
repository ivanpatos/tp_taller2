/*
 * LogoutServiceFixture.h
 */
#ifndef TEST_LOGOUTSERVICETEST_H_
#define TEST_LOGOUTSERVICETEST_H_
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../main/include/server/Services/LogoutService.h"
#include "../../main/include/database/MockDatabase.h"
#include "../../main/include/server/HttpResponse.h"
#include "../Utils/Utils.h"
#include "../../main/include/resources/User.h"

using ::testing::Test;

class LogoutServiceFixture: public Test {
public:

	LogoutServiceFixture( ) : userNotSavedInDb(getJsonUser("tomRea", "123456", "tomRea@gmail.com")){

		logoutService = new LogoutService(userDB);
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

   ~LogoutServiceFixture( ) {
	   delete logoutService;
   }

   User userNotSavedInDb;

   LogoutService* logoutService;

   MockDatabase userDB;

   std::string data, username , token = "666", query, mail;

   std::string OK = "OK", ERROR = "ERROR";
};

#endif /* TEST_LOGOUTSERVICETEST_H_ */
