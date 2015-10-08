75.52 - Taller de Programacion II - 2do Cuat. 2015 - TP "Udrive"


#Documentacion#

Ademas de este readme se cuenta con documentacion generada con sphinx, ubicada en el directorio documentacion.

Para visualizar dicha documentacion, dirigirese a la carpeta del documento que se desee y ejecutar: $ make html

Luego abrir el informe yendo a dir_del_informe/_build/html/index.html


#Instalacion de dependencias#

*ROCKSDB*

Actualizar gcc a version por lo menos 4.7, para tener soporte c++11 (fijarse que version se tiene con $ gcc --version)

Instalar dependendencias necesarias para compilar rocksdb: $ sudo apt-get install libgflags-dev libsnappy-dev zlib1g-dev libbz2-dev

Bajar rocksdb de su repositorio (https://github.com/facebook/rocksdb), luego ejecutar $ make static_lib

Finalmente hacer $ make install


*CMAKE*

Para instalar cmake hacer: $ sudo apt-get install cmake


*GMOCK + GTEST*

Para instalar gmock junto a gtest hacer los pasos siguientes: 

$ sudo apt-get install google-mock

$ cd /usr/src/gmock

$ sudo cmake .

$ sudo make

$ sudo cp -a *.a /usr/lib

$ cd /usr/src/gmock/gtest

$ sudo cp -a *.a /usr/lib


*PYTHON REQUESTS*

Primero instalar pip si no se lo tiene instalado: bajar el script get-pip.py (https://bootstrap.pypa.io/get-pip.py) y correr el script haciendo: $ sudo python get-pip.py

Finalmente instalar requests: $ pip install requests


*LCOV*

$ sudo apt-get install lcov 


*SPHINX*

$ sudo pip install Sphinx


#Compilacion y ejecucion de servidor#

Crear una carpeta donde se quiera hacer el build del proyecto, luego parado en dicha carpeta ejecutar:

$ cmake path_a_CMakeLists.txt (se encuentra en src/UdriveServer/main)

$ make

$ ./udrive_server

Para frenar el servidor, hacer ctrl+c (provisorio)


#Compilacion y ejecución de servidor junto a tests#

Para compilar el servidor junto a los tests (incluye ejecución automática de los test con respectivo informe de code coverage)

Crear una carpeta donde se quiera hacer el build del proyecto, luego parado en dicha carpeta ejecutar:

$ cmake path_a_CMakeLists.txt (se encuentra en src/UdriveServer)

$ make

En la carpeta donde se realizó el build, la carpeta main contiene el ejecutable del server. Si se desea ejecutarlo:

$ ./udrive-server

En la carpeta test se encuentra el reporte generado de code coverage. Para verlo abrir index.html

Si se desea ejecutar los tests individualmente ir a la correspondiente carpeta del test ubicada en la carpeta test y correr el ejecutable respectivo (también se puede ejecutar con el comando ctest)



#Ejecucion de tests python requests#

Dirigirse a src/UdriveServer/test y ejecutar: $ pyhton request_test.py

