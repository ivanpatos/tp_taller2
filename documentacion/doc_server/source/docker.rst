Docker
======

Instalación de docker y creación de imagen
------------------------------------------

En caso de que se quiera correr el servidor a través de un contenedor de docker, realizar los siguientes pasos.

Para instalar Docker::

	$ sudo apt-get update
	$ sudo apt-get install wget
	$ wget -qO- https://get.docker.com/ | sh

Una vez instalado Docker, procedemos a crear la imagen::

	$ cd src/UdriveServer/mydockerbuild
	$ sudo docker build .

Para ver la nueva imagen creada, con su respectivo <IMAGE ID>::

	$ sudo docker images

Luego le asignamos un tag a la imagen::

	$ sudo docker tag <IMAGE ID> server


Ejecución del servidor
----------------------

Para ejecutar el servidor::

	$ sudo docker run -p 8080:8080 server
