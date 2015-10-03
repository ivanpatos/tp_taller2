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


*PYTHON REQUESTS*

Primero instalar pip si no se lo tiene instalado: bajar el script get-pip.py (https://bootstrap.pypa.io/get-pip.py) y correr el script haciendo: $ sudo python get-pip.py

Finalmente instalar requests: $ pip install requests


#Compilacion y ejecucion de servidor#

Crear una carpeta donde se quiera hacer el build del proyecto, luego parado en dicha carpeta ejecutar:

$ cmake path_a_CMakeLists.txt (se encuentra en src/UdriveServer/main)

$ make

$ ./udrive_server

Para frenar el servidor, hacer ctrl+c (provisorio)


#Ejecucion de tests python requests#

Dirigirse a src/UdriveServer/test y ejecutar: $ pyhton request_test.py

