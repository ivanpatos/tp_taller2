Instalación
===========

Instalación de dependencias
---------------------------

*ROCKSDB*

Actualizar **gcc** a version por lo menos 4.7, para tener soporte c++11 (fijarse que version se tiene con $ gcc --version)

Instalar dependendencias necesarias para compilar rocksdb haciendo::

	$ sudo apt-get install libgflags-dev libsnappy-dev zlib1g-dev libbz2-dev

Bajar `rocksdb <https://github.com/facebook/rocksdb>`_, luego parado en su carpeta ejecutar::

	$ make static_lib	
	$ make install

*CMAKE*

Para instalar cmake::

	$ sudo apt-get install cmake

*GMOCK + GTEST*

Para instalar gmock junto a gtest hacer los pasos siguientes::

	$ sudo apt-get install google-mock
	$ cd /usr/src/gmock
	$ sudo cmake .
	$ sudo make
	$ sudo cp -a *.a /usr/lib
	$ cd /usr/src/gmock/gtest
	$ sudo cp -a *.a /usr/lib

*PYTHON REQUESTS*

Instalar **pip** si no se lo tiene instalado. Bajar el script `get-pip.py <https://bootstrap.pypa.io/get-pip.py>`_ y correr dicho script:: 

	$ sudo python get-pip.py

Para instalar requests hacer:: 

	$ pip install requests

*LCOV*::

	$ sudo apt-get install lcov 


Instalación del servidor
------------------------

Bajar el servidor del `repositorio <https://github.com/ivanpatos/tp_taller2>`_. Crear una carpeta donde se quiera hacer el build del servidor, luego parado en dicha carpeta ejecutar::

	$ cmake path_a_CMakeLists.txt (se encuentra en src/UdriveServer/main)
	$ make

Si se desea hacer un build del servidor que incluya la ejecución automática de tests unitarios y generación de code coverage ejecutar::

	$ cmake path_a_CMakeLists.txt (se encuentra en src/UdriveServer)
	$ make

