#ifndef _HTTP_RESPONSE_H_
#define _HTTP_RESPONSE_H_

#include <string>
#include "json/json.h"


class HttpResponse{

public:

	enum errorCode{
		ERROR_AUTHENTICATION = 1,
		ERROR_INVALID_USERNAME,
		ERROR_USERNAME_EXISTS,
		ERROR_USERNAME_MISSING,
		ERROR_PASSWORD_MISSING,
		ERROR_SAVING_DATA,
		ERROR_INVALID_PASSWORD
	};

	static std::string GetHttpOkResponse(const Json::Value& data);
	static std::string GetHttpErrorResponse(const errorCode& errorCode);
};



#endif
