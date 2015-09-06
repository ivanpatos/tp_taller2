#ifndef _HTTP_RESPONSE_H_
#define _HTTP_RESPONSE_H_

#include "json/json.h"

using namespace std;

class HttpResponse{

public:

	static const string ERROR_INVALID_USERNAME;
	static const string ERROR_AUTHENTICATION;
	static const string ERROR_USERNAME_EXISTS;
	static const string ERROR_USERNAME_MISSING;
	static const string ERROR_PASSWORD_MISSING;
	static const string ERROR_SAVING_DB;

	static string GetHttpOkResponse(const Json::Value& data);
	static string GetHttpErrorResponse(const string& errorMessage);
};



#endif
