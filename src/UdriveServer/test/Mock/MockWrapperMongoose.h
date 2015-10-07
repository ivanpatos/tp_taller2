/*
 * MockWrapperMongoose.h
 *
 *  Created on: 23 de set. de 2015
 *      Author: ltessore
 */

#ifndef TEST_MOCK_MOCKWRAPPERMONGOOSE_H_
#define TEST_MOCK_MOCKWRAPPERMONGOOSE_H_
#include <gmock/gmock.h>
#include "../../main/include/utilities/WrapperMongoose.h"

class MockWrapperMongoose: public WrapperMongoose{
public:
	MockWrapperMongoose();
	MOCK_METHOD2(mgprintfData, size_t(struct mg_connection *connection, const char *response));
	MOCK_METHOD2(getHeader, const char *(const struct mg_connection *connection, const char *name));
	MOCK_METHOD1(contentLen, size_t (const struct mg_connection *connection));
	MOCK_METHOD1(queryString, const char *(const struct mg_connection *connection));
	MOCK_METHOD3(setOption, const char*(struct mg_server *server, const char *name, const char *value));
	virtual ~MockWrapperMongoose();
};

//virtual size_t mgprintfData(struct mg_connection *connection, const char *response);
//virtual const char *getHeader(const struct mg_connection *connection, const char *name);
//virtual size_t contentLen(const struct mg_connection *connection);
//virtual const char *queryString(const struct mg_connection *connection);
//virtual const char *setOption(struct mg_server *server, const char *name, const char *value);

#endif /* TEST_MOCK_MOCKWRAPPERMONGOOSE_H_ */
