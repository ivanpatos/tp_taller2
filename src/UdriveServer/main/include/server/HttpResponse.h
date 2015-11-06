#ifndef _HTTP_RESPONSE_H_
#define _HTTP_RESPONSE_H_

#include <string>
#include "../../others/json/json.h"

/**
 * Clase que define la respuesta generada por el servidor.
 */
class HttpResponse{

public:

	enum errorCode{
		ERROR_AUTHENTICATION = 1,
		ERROR_INVALID_USERNAME,
		ERROR_USERNAME_EXISTS,
		ERROR_USERNAME_MISSING,
		ERROR_PASSWORD_MISSING,
		ERROR_SAVING_DATA,
		ERROR_INVALID_PASSWORD,
		ERROR_INVALID_FOLDER_PARENT,
		ERROR_FOLDER_NAME_EXISTS,
		ERROR_INVALID_FOLDER,
		ERROR_FILE_EXISTS,
		ERROR_INVALID_REQUEST,
		ERROR_INVALID_FILE,
		ERROR_INVALID_FILE_VERSION,
		ERROR_FILE_PERMISSION_DENIED,
		ERROR_FILE_ALREADY_DELETED,
		ERROR_NO_FILES_FOUND,
		ERROR_NOT_ENOUGH_SPACE
	};

	/**
	 * Respuesta OK
	 * @param data Json del mensaje a enviar.
	 * @return Mensaje en formato string a ser enviado por el servidor con los datos correspondientes.
	 */
	static std::string GetHttpOkResponse(const Json::Value& data);

	/**
	 * Respuesta Error
	 * @param errorCode Código de error.
	 * @return Mensaje en formato string a ser enviado por el servidor indicando el error que se generó.
	 */
	static std::string GetHttpErrorResponse(const errorCode& errorCode);
};



#endif
