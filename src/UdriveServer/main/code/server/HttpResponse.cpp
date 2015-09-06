#include "../../include/server/HttpResponse.h"

std::string HttpResponse::GetHttpOkResponse(const Json::Value& data){
	Json::Value jsonResponse;
	jsonResponse["result"] = "OK";
	jsonResponse["data"] = data;
	Json::StreamWriterBuilder builder;
	return Json::writeString(builder, jsonResponse);
}

std::string HttpResponse::GetHttpErrorResponse(const errorCode& errorCode){
	Json::Value jsonResponse;
	jsonResponse["result"] = "ERROR";
	jsonResponse["errorCode"] = errorCode;
	Json::StreamWriterBuilder builder;
	return Json::writeString(builder, jsonResponse);
}
