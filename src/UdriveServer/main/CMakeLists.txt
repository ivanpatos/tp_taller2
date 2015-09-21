# Para generar el make ejecutar en la carpeta donde se quiere buildear: cmake path_dir_con_fuentes  (recomendacion no hacerlo en la misma carpeta donde estan los fuentes)
# Luego ejecutar: make
# Finalmente correr con ./udrive_server


CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Nombre del proyecto
PROJECT(TP_TALLER2)

# Setea flags del compilador
SET(CMAKE_CXX_FLAGS "-std=c++11")

# Variable con los fuentes
SET(SRC_FILES code/database/Database.cpp 
code/resources/File.cpp code/resources/Folder.cpp code/resources/User.cpp code/resources/Version.cpp
code/server/HttpResponse.cpp code/server/Server.cpp code/server/ServiceFactory.cpp 
code/server/Services/CreateFileService.cpp code/server/Services/CreateFolderService.cpp code/server/Services/CreateUserService.cpp code/server/Services/GetFileService.cpp code/server/Services/GetFolderService.cpp code/server/Services/GetUserService.cpp code/server/Services/LoginService.cpp code/server/Services/LogoutService.cpp code/server/Services/NonExistentService.cpp code/server/Services/UpdateUserService.cpp 
others/jsoncpp.cpp code/Main.cpp others/mongoose.c code/utilities/Time.cpp)

# Variable con las librerías
SET(LINK_LIBRARIES rocksdb pthread z bz2 snappy)

# Genera el ejecutable
ADD_EXECUTABLE(udrive_server ${SRC_FILES})

# Linkea las librerías
TARGET_LINK_LIBRARIES(udrive_server ${LINK_LIBRARIES})
