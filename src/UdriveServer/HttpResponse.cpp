#include "HttpResponse.h"

const string HttpResponse::ERROR_INVALID_USERNAME = "Invalid username";
const string HttpResponse::ERROR_AUTHENTICATION = "Authentification failed";
const string HttpResponse::ERROR_USERNAME_EXISTS = "Username already exists";
const string HttpResponse::ERROR_USERNAME_MISSING = "Username is missing";
const string HttpResponse::ERROR_PASSWORD_MISSING = "Password is missing";
const string HttpResponse::ERROR_SAVING_DB = "Failed to save data";

string HttpResponse::GetHttpOkResponse(const Json::Value& data){
	Json::Value jsonResponse;
	jsonResponse["result"] = "OK";
	jsonResponse["data"] = data;
	Json::StreamWriterBuilder builder;
	return Json::writeString(builder, jsonResponse);
}

string HttpResponse::GetHttpErrorResponse(const string& errorMessage){
	Json::Value jsonResponse;
	jsonResponse["result"] = "ERROR";
	jsonResponse["message"] = errorMessage;
	Json::StreamWriterBuilder builder;
	return Json::writeString(builder, jsonResponse);
}
