Librerías
=========

Para facilitar el desarrollo del proyecto, se utilizaron diferentes librerías externas open source.

Servidor http
-------------

Para levantar un servidor http se utilizó `mongoose <https://github.com/cesanta/mongoose>`_, el cual facilitó en gran medida el manejo de http requests.

Datos json
----------

Para la manipulación de datos json se hizo uso de la librerías `jsoncpp <https://github.com/open-source-parsers/jsoncpp>`_. Los json se usaron tanto para el envío de datos a través de los mensajes http como en la persistencia de datos del lado del servidor.

Persistencia de datos
---------------------

Para la persistencia de datos por parte del servidor, se utilizó una base de datos no relacional del tipo *clave/valor* llamada `rocksdb <https://github.com/facebook/rocksdb>`_.
