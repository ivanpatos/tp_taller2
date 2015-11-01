REST api
========

A continuación se detalla cada uno de los mensajes http que puede realizar el cliente, con su correspondiente respuesta por parte del servidor.

**Login**::

	- request: 

	url: /login
	method: POST
	query string: -
	header: -
	json: username, password

	- respuesta: 

	si salio ok, json con:
	result : OK
	data: username, name, mail, profilePicture, lastLocation, token

	si salio mal:
	result : ERROR
	errorCode: codigo de error
	2 - ERROR_INVALID_USERNAME
	6 - ERROR_SAVING_DATA
	7 - ERROR_INVALID_PASSWORD

**Logout**::

	- request: 

	url: /logout
	method: POST
	query string: -
	header: username, token
	json: -

	- respuesta: 

	si salio ok, json con:
	result : OK
	data: -

	si salio mal:
	result : ERROR
	errorCode: codigo de error
	1 - ERROR_AUTHENTICATION
	6 - ERROR_SAVING_DATA

**Create user**::

	- request: 

	url: /user
	method: POST
	query string: -
	header: -
	json: username, name, mail, profilePicture, password, token

	- respuesta: 

	si salio ok, json con:
	result : OK
	data: username, name, mail, profilePicture, lastLocation

	si salio mal:
	result : ERROR
	errorCode: codigo de error
	3 - ERROR_USERNAME_EXISTS
	4 - ERROR_USERNAME_MISSING
	5 - ERROR_PASSWORD_MISSING
	6 - ERROR_SAVING_DATA

**Update user**::

	- request: 

	url: /user
	method: PUT
	query string: -
	header: username, token
	json: name, mail, profilePicture, lastLocation, password

	- respuesta: 

	si salio ok, json con:
	result : OK
	data: username, name, mail, profilePicture, lastLocation

	si salio mal:
	result : ERROR
	errorCode: codigo de error
	1 - ERROR_AUTHENTICATION
	6 - ERROR_SAVING_DATA

**Get user**::

	- request: 

	url: /user/username
	method: GET
	query string: -
	header: username, token
	json: -

	- respuesta: 

	si salio ok, json con:
	result : OK
	data: username, name, mail, profilePicture, lastLocation

	si salio mal:
	result : ERROR
	errorCode: codigo de error
	1 - ERROR_AUTHENTICATION
	2 - ERROR_INVALID_USERNAME

**Get all users**::

	- request: 

	url: /user
	method: GET
	query string: -
	header: username, token
	json: -

	- respuesta: 

	si salio ok, json con:
	result : OK
	data: lista con (username, name, mail, profilePicture, lastLocation)

	si salio mal:
	result : ERROR
	errorCode: codigo de error
	1 - ERROR_AUTHENTICATION

**Create Folder**::

	- request: 

	url: /folder
	method: POST
	query string: -
	header: username, token
	json: name, idParent

	- respuesta: 

	si salio ok, json con:
	result : OK
	data: id, name, children (lista con <type, id, name> type puede ser file o folder)

	si salio mal:
	result : ERROR
	errorCode: codigo de error
	1 - ERROR_AUTHENTICATION
	6 - ERROR_SAVING_DATA
	8 - ERROR_INVALID_FOLDER_PARENT
	9 - ERROR_FOLDER_NAME_EXISTS

**Get Folder**::

	- request: 

	url: /folder/idFolder
	method: GET 
	query string: -
	header: username, token
	json: -

	- respuesta: 

	si salio ok, json con:
	result : OK
	data: id, name, children (lista de <type, id, name> para folders con type=folder, en caso de que sea archivo <type, id, name, extension> con type=file)

	si salio mal:
	result : ERROR
	errorCode: codigo de error
	1 - ERROR_AUTHENTICATION
	10 - ERROR_INVALID_FOLDER

**Update Folder**::

	- request: 

	url: /folder/idFolder
	method: PUT
	query string: -
	header: username, token
	json: name, users (lista username)

	- respuesta: 

	si salio ok, json con:
	result : OK
	data: id, name, children (lista con <type, id, name> type puede ser file o folder)

	si salio mal:
	result : ERROR
	errorCode: codigo de error

**Delete Folder**::

	- request: 

	url: /folder/idFolder
	method: DELETE
	query string: -
	header: username, token
	json: -

	- respuesta: 

	si salio ok, json con:
	result : OK
	data: -

	si salio mal:
	result : ERROR
	errorCode: codigo de error
	1 - ERROR_AUTHENTICATION
	10 - ERROR_INVALID_FOLDER

**Create File**::

	- request: 

	url: /file
	method: POST
	query string: -
	header: username, token
	json: name, extension, labels (lista de <description>), data, idFolder

	- respuesta: 

	si salio ok, json con:
	result : OK
	data: id, name, deleted, lastModified, lastUser, labels (lista), owner, users (lista), extension, version (numero de version)

	si salio mal:
	result : ERROR
	errorCode: codigo de error
	1 - ERROR_AUTHENTICATION
	6 - ERROR_SAVING_DATA
	8 - ERROR_INVALID_FOLDER_PARENT
	11 - ERROR_FILE_EXISTS
	18 - ERROR_NOT_ENOUGH_SPACE

**Get File** (logico, obtengo solo los metadatos)::

	- request: 

	url: /file/idFile
	method: GET 
	query string: -
	header: username, token
	json: -

	- respuesta: 

	si salio ok, json con:
	result : OK
	data: id, name, deleted, lastModified, lastUser, labels (lista), owner, users (lista), extension, version (numero de version)

	si salio mal:
	result : ERROR
	errorCode: codigo de error
	1 - ERROR_AUTHENTICATION
	13 - ERROR_INVALID_FILE

**Get Files** (query de varios archivos, solo metadatos)::

	- request: 

	url: /file
	method: GET 
	query string: name, extension, labels (lista), owner
	header: username, token
	json: -

	- respuesta: 

	si salio ok, json con:
	result : OK
	data: lista con (id, name, deleted, lastModified, lastUser, labels (lista), owner, users (lista), extension, version (numero de version))

	si salio mal:
	result : ERROR
	errorCode: codigo de error
	1 - ERROR_AUTHENTICATION
	17 - ERROR_NO_FILES_FOUND

**Get File** (fisico)::

	- request: 

	url: /file/idFile
	method: GET 
	query string: version (por ejemplo: /file/idsarasa?version=2)
	header: username, token
	json: -

	- respuesta: 

	si salio ok, json con:
	result : OK
	data: id (id de la version o sea "idFile_version"), name, extension, data

	si salio mal:
	result : ERROR
	errorCode: codigo de error
	1 - ERROR_AUTHENTICATION
	14 - ERROR_INVALID_FILE_VERSION

**Update File** (logico, modificacion solo los metadatos)::

	- request: 

	url: /file/idFile
	method: PUT
	query string: -
	header: username, token
	json: name, extension, labels (lista), users (lista username), deleted

	- respuesta: 

	si salio ok, json con:
	result : OK
	data: id, name, deleted, lastModified, lastUser, labels (lista), owner, users (lista), extension, version (numero de version)

	si salio mal:
	result : ERROR
	errorCode: codigo de error
	1 - ERROR_AUTHENTICATION
	6 - ERROR_SAVING_DATA
	13 - ERROR_INVALID_FILE
	15 - ERROR_FILE_PERMISSION_DENIED

**Update File** (fisico)::

	- request: 

	url: /file/idFile
	method: PUT
	query string: -
	header: username, token
	json: data

	- respuesta: 

	si salio ok, json con:
	result : OK
	data: id, name, deleted, lastModified, lastUser, labels (lista), owner, users (lista), extension, version (numero de version)

	si salio mal:
	result : ERROR
	errorCode: codigo de error
	1 - ERROR_AUTHENTICATION
	6 - ERROR_SAVING_DATA
	13 - ERROR_INVALID_FILE
	15 - ERROR_FILE_PERMISSION_DENIED
	18 - ERROR_NOT_ENOUGH_SPACE

**Delete File**::

	- request: 

	url: /file/idFile
	method: DELETE
	query string: -
	header: username, token
	json: -

	- respuesta: 

	si salio ok, json con:
	result : OK
	data: -

	si salio mal:
	result : ERROR
	errorCode: codigo de error
	1 - ERROR_AUTHENTICATION
	6 - ERROR_SAVING_DATA
	13 - ERROR_INVALID_FILE
	15 - ERROR_FILE_PERMISSION_DENIED
	16 - ERROR_FILE_ALREADY_DELETED

