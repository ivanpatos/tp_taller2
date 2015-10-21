/*
 * MockDatabase.h
 *
 *  Created on: Oct 21, 2015
 *      Author: tomrea
 */

#ifndef INCLUDE_DATABASE_MOCKDATABASE_H_
#define INCLUDE_DATABASE_MOCKDATABASE_H_

#include <gmock/gmock.h>
#include "Database.h"

class MockDatabase: public Database {

	public:

	MOCK_CONST_METHOD1(getValue, std::string(const std::string& key));
	MOCK_METHOD0(init, void());
    MOCK_METHOD2(saveValue,bool(const std::string& key, const std::string& value));
	MOCK_METHOD1(deleteRecord,void(const std::string& key));
	MOCK_CONST_METHOD0(getAllValues,std::vector<std::string>() );
};


#endif /* INCLUDE_DATABASE_MOCKDATABASE_H_ */
