-------------------------------------------------------------------------------------------------------------------------------
CMAKE

Instalar cmake con: sudo apt-get install cmake
Crear el CMakeLists.txt en la carpeta src del proyecto donde estan todos los fuentes
Para generar el make ejecutar: cmake CMakeLists.txt  
Luego ejecutar: make
Finalmente correr con ./nombre_ejecutable
-------------------------------------------------------------------------------------------------------------------------------
PYTHON REQUESTS

Instalar pip:
Bajar get-pip.py de aca https://pip.pypa.io/en/latest/installing.html, luego ejecutar: sudo python get-pip.py

Ejecutar: pip install requests
-------------------------------------------------------------------------------------------------------------------------------
ROCKSDB
(https://github.com/facebook/rocksdb)

Actualizar gcc a version por lo menos 4.7, para tener soporte c++11 (fijarse q version se tiene con gcc --version)

Instalar gflags:  sudo apt-get install libgflags-dev  
Instalar snappy:  sudo apt-get install libsnappy-dev
Instalar zlib:  sudo apt-get install zlib1g-dev
Instalar bzip2:  sudo apt-get install libbz2-dev

Bajar rocksdb, ejecutar "make static_lib", luego "make install"

Para compilar un proyecto que usa las libs de rocksdb:
g++ proyecto.cpp -o proyecto -std=c++11 -lrocksdb -lpthread -lz -lbz2 -lsnappy
-------------------------------------------------------------------------------------------------------------------------------
MONGOOSE
(https://github.com/cesanta/mongoose)

Simplemente consta de dos archivos (mongoose.c y mongoose.h). Bajar de ahi y listo

Se los usa como con cualquier otra cosa: #include "mongoose.h" y listo
-------------------------------------------------------------------------------------------------------------------------------
JSONCPP 
(https://github.com/open-source-parsers/jsoncpp)

Idem MONGOOSE, son un par de archivos (json.h, json-forwards.h, y json.cpp) pero para generarlos hay que hacer lo siguiente:

Bajar el paquete de ahi y ejecutar "python amalgamate.py", los archivos generados estan en /../dist
-------------------------------------------------------------------------------------------------------------------------------
GIT 

Para instalar: sudo apt-get install git
(Tutorial --> https://www.atlassian.com/git/tutorials/)

Comandos utiles:

git init
git add .
git commit
git commit -a -m "mensaje"	(agrega cambios de archivos que alguna vez fueron agregados con add)

git status 			(lista que archivos estan stage, unstaged, untracked)
git log 			(lista commits, con -p mas detallado, --oneline una linea)

git checkout <commit> 		(veo commit respectivo sin afectar el master)
git checkout <commit> <file>
git checkout HEAD <file>
git revert <commit> 		(cargo el commit viejo y lo commitea)

git branch 			(lista los branches y en cual estoy)
git branch <new-branch> 	(crea branch nueva)
git checkout <new-branch> 	(cambio al branch nuevo
git checkout -b <new-branch> 	(crea branch nueva y cambia a esa branch)

git merge experimental 		(mergea la branch actual con la branch experimental)
git branch -d experimental 	(se asegura que los cambios esten en la branch actual)
git branch -D crazy-idea 	(borra a la mierda la branch)

git diff 			(entre working directory e index)
git diff –cached 		(entre index y commit)
git diff HEAD 			(entre working directory y commit)
git diff <branch1>..<branch2>	(entre 2 branches, ult commits)

git remote add name url
git remote -v			(lista conexiones)
git remote rm name		(borra conexion)
git branch -r			(lista branches remotos)
git push origin --delete branch	(borra branch remota)
git push origin master		(manda master local a repo)
git pull origin			(baja lo que hay en el repo, fetch + merge)
git fetch origin		(baja pero no mergea, sirve para ver que hay en el repo)
-------------------------------------------------------------------------------------------------------------------------------
