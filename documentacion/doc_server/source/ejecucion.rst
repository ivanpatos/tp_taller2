Ejecución
=========

Ejecución del servidor
----------------------

Donde se haya realizado el build del servidor simplemente ejecutar::

	$ ./udrive_server

Para frenar el servidor, hacer ctrl+c (provisorio)

Ejecución de tests python requests
----------------------------------

Dirigirse a src/UdriveServer/test y ejecutar::

	$ pyhton request_test.py

.. warning:: Estos tests están pensados para ejecutarse únicamente con la base de datos vacía. Para ello eliminar las carpetas dataDB, fileDB, folderDB y userDB de la carpeta donde se haya hecho el build del server.
