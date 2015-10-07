/*
 * WrapperMongoose.h
 *
 *  Created on: 23 de set. de 2015
 *      Author: ltessore
 */

#ifndef WRAPPERMONGOOSE_H_
#include "../../others/mongoose.h"

class WrapperMongoose {
public:
	WrapperMongoose();
	virtual size_t mgprintfData(struct mg_connection *connection, const char *response);
	virtual const char *getHeader(const struct mg_connection *connection, const char *name);
	virtual size_t contentLen(const struct mg_connection *connection);
	virtual const char *queryString(const struct mg_connection *connection);
	virtual const char *setOption(struct mg_server *server, const char *name, const char *value);
	virtual ~WrapperMongoose();
};

#endif /* WRAPPERMONGOOSE_H_ */
