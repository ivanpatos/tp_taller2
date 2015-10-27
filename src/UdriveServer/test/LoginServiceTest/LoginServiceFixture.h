/*
 * LoginServiceFixture.h
 */
#ifndef TEST_LOGINSERVICETEST_H_
#define TEST_LOGINSERVICETEST_H_
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../main/include/server/Services/LoginService.h"
#include "../../main/include/database/MockDatabase.h"
#include "../../main/include/server/HttpResponse.h"
#include "../Utils/Utils.h"
#include "../../main/include/resources/User.h"

using ::testing::Test;

class LoginServiceFixture: public Test {
public:

	LoginServiceFixture( ) : userNotSavedInDb(getJsonUser("tomRea", "123456", "tomRea@gmail.com")){

		loginService = new LoginService(userDB);
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

   ~LoginServiceFixture( ) {
	   delete loginService;
   }

   User userNotSavedInDb;

   LoginService* loginService;

   MockDatabase userDB;

   std::string data, username , token = "666", query, mail;

   std::string OK = "OK", ERROR = "ERROR";
};

#endif /* TEST_LOGINSERVICETEST_H_ */
