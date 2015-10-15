
#ifndef TEST_MOCK_MOCKDATABASE_CPP_
#define TEST_MOCK_MOCKDATABASE_CPP_
#include <gmock/gmock.h>
#include "../../main/include/database/Database.h"

class MockDatabase: public Database{
public:
	MockDatabase(): Database(){}
	MOCK_CONST_METHOD1(getValue, std::string(const std::string& key));
	MOCK_METHOD0(init, void());
    MOCK_METHOD2(saveValue,bool(const std::string& key, const std::string& value));
	MOCK_METHOD1(deleteRecord,void(const std::string& key));
	MOCK_CONST_METHOD0(getAllValues,std::vector<std::string>() );

	//virtual ~MockDatabase(){}
};



#endif /* TEST_MOCK_MOCKDATABASE_CPP_ */
