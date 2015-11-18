Configuración de log
====================

El servidor cuenta con un sistema de log en donde se registran los eventos que se generan durante la ejecución del mismo. Dicho sistema permite configurar el nivel de los eventos que se desean registrar.

Para configurar el sistema de log, se debe crear un archivo "conf.conf" (sin comillas) en el directorio donde se encuentre el ejecutable del servidor. El formato del archivo es el siguiente::

	* GLOBAL:
	   ENABLED              =  true
	* DEBUG:
	   ENABLED              =  true
	* TRACE:
	   ENABLED              =  true
	* ERROR:
	   ENABLED              =  true
	* WARNING:
	   ENABLED              =  true
	* INFO:
	   ENABLED              =  true

Poniendo false o true en cada tipo de log, se activa o desactiva el respectivo log. Si no hay archivo de configuración, se toma por default todos los tipos de log activados.

.. warning:: Si se quiere cambiar la configuración, es necesario editar el archivo, parar el server, y volverlo a levantar.

