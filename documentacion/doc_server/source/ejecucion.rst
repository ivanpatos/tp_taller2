Ejecución
=========

Ejecución del servidor
----------------------

Donde se haya realizado el build del servidor simplemente ejecutar (en caso de haber compilado totalmente el proyecto junto a los tests y code coverage, entrar primero a la carpeta main)::

	$ ./udrive_server

Para frenar el servidor, introducir "stop" (sin comillas) en la consola.

.. warning:: Una vez frenado el servidor, el servidor queda totalmente apagado, sin poder atender nuevas peticiones de los clientes.

Ejecución de tests unitarios
----------------------------

Como se mencionó anteriormente (ver instalación del servidor), la ejecución de tests unitarios pueden ser ejecutados en forma automática al realizarse la compilación del servidor.

Si se desea ejecutar los tests individualmente ir a la correspondiente carpeta del test ubicada en la carpeta test y correr el ejecutable respectivo (también se puede ejecutar con el comando ctest).

Para ver el informe de code coverage, abrir index.html ubicado en la carpeta donde se realizó el build del servidor.

Ejecución de tests python requests
----------------------------------

Con el servidor corriendo, dirigirse a src/UdriveServer/test y ejecutar::

	$ pyhton request_test.py

.. warning:: Estos tests están pensados para ejecutarse únicamente con la base de datos vacía. Para ello eliminar las carpetas dataDB, fileDB, folderDB y userDB de la carpeta donde se haya hecho el build del server.

Ejecución de test de stress
---------------------------

Con el servidor corriendo, dirigirse a src/UdriveServer/test y ejecutar::

	$ pyhton stress_test.py
