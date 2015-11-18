#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../../main/include/resources/Version.h"


const char* id = "id";
const char* data = "data";

#include "../../main/include/utilities/easylogging++.h"
INITIALIZE_EASYLOGGINGPP
#define ELPP_DISABLE_LOGS

TEST(VersionTest, getJson) {
	Version version(id,data);

	Json::Value expected;
	expected["id"] = id;
	expected["data"] = data;

	EXPECT_TRUE (expected  == version.getJson());
}

int main(int argc, char *argv[]){
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
