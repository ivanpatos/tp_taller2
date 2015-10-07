/*
 * WrapperMongoose.cpp
 *
 *  Created on: 23 de set. de 2015
 *      Author: ltessore
 */

#include "../../include/utilities/WrapperMongoose.h"

WrapperMongoose::WrapperMongoose() {
	// TODO Auto-generated constructor stub

}

size_t WrapperMongoose::mgprintfData(struct mg_connection *connection, const char *response){
	return mg_printf_data(connection, response);
}

const char * WrapperMongoose::getHeader(const struct mg_connection *connection, const char *name){
	return mg_get_header(connection, name);
}

size_t WrapperMongoose::contentLen(const struct mg_connection *connection){
	return connection->content_len;
}

const char * WrapperMongoose::queryString(const struct mg_connection *connection){
	return connection->query_string;
}

const char * WrapperMongoose::setOption(struct mg_server *server, const char *name, const char *value){
	return mg_set_option(server,name,value);
}
WrapperMongoose::~WrapperMongoose() {
	// TODO Auto-generated destructor stub
}

