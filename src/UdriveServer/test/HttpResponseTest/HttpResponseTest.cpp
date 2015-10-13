#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../main/include/server/HttpResponse.h"

using ::testing::Return;
using ::testing::_;

const char* data = "data";

std::string getResponse(std::string result){
	Json::Value jsonResponse;
	jsonResponse["result"] = result;
	if (result == "ERROR"){
		jsonResponse["errorCode"] = HttpResponse::ERROR_AUTHENTICATION;
	}
	else if (result == "OK"){
    	jsonResponse["data"] = data;
	}
    Json::StreamWriterBuilder builder;
	return Json::writeString(builder, jsonResponse);
}
TEST(HttpResponseTest, getHttpErrorResponse) {
	HttpResponse httpResponse;
	std::string response = httpResponse.GetHttpErrorResponse(HttpResponse::ERROR_AUTHENTICATION);
    EXPECT_EQ(response, getResponse("ERROR"));
}

TEST(HttpResponseTest, getHttpErrorResponseInvalid) {
	HttpResponse httpResponse;
	std::string response = httpResponse.GetHttpErrorResponse(HttpResponse::ERROR_AUTHENTICATION);
    EXPECT_TRUE(response != getResponse("OTHER"));
}


TEST(HttpResponseTest, getHttpOkResponse) {
	HttpResponse httpResponse;
	std::string response = httpResponse.GetHttpOkResponse(data);
    EXPECT_EQ(response, getResponse("OK"));
}

TEST(HttpResponseTest, getHttpOkResponseInvalid) {
	HttpResponse httpResponse;
	std::string response = httpResponse.GetHttpOkResponse(data);
    EXPECT_TRUE(response != getResponse("OTHER"));
}


int main(int argc, char *argv[]){
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
