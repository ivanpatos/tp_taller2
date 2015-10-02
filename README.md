75.52 - Taller de Programacion II - 2do Cuat. 2015 - TP "Udrive"


#Instalacion de dependencias#

*ROCKSDB*

Actualizar gcc a version por lo menos 4.7, para tener soporte c++11 (fijarse q version se tiene con gcc --version)
Instalar dependendencias necesarias para compilar rocksdb: $ sudo apt-get install libgflags-dev libsnappy-dev zlib1g-dev libbz2-dev
Bajar rocksdb de su repositorio (https://github.com/facebook/rocksdb), luego ejecutar $ make static_lib
Finalmente hacer $ make install


*CMAKE*

Para instalar cmake: $ sudo apt-get install cmake


*PYTHON REQUESTS*

Primero instalar pip: bajar el script get-pip.py (https://bootstrap.pypa.io/get-pip.py)
Luego correr el script: $ sudo python get-pip.py
Finalmente instalar requests: $ pip install requests


#Compilacion y ejecucion de servidor#

Crear una carpeta donde se quiera hacer el build del proyecto, luego parado en dicha carpeta ejecutar:

$ cmake path_a_CMakeLists.txt (se encuentra en src/UdriveServer/main)
$ make
$ ./udrive_server

Para frenar el servidor, hacer ctrl+c (provisorio)


#Ejecucion de tests python requests#

Dirigirse a src/UdriveServer/test y ejecutar: $ pyhton request_test.py

