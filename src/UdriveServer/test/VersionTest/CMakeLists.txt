# Para generar el make ejecutar en la carpeta donde se quiere buildear: cmake path_dir_con_fuentes  (recomendacion no hacerlo en la misma carpeta donde estan los fuentes)
# Luego ejecutar: make
# Finalmente correr con ./HttpResponseTest


CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Nombre del proyecto
PROJECT(TP_TALLER2)

#SET(GCC_COVERAGE_LINK_FLAGS, "-lpthread -lrt")
#add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
# Setea flags del compilador
SET(CMAKE_CXX_FLAGS "-std=c++11 -lgmock")

# Variable con los fuentes
SET(SRC_FILES  ../../main/code/database/Database.cpp 
../../main/code/resources/File.cpp ../../main/code/resources/Folder.cpp ../../main/code/resources/User.cpp ../../main/code/resources/Version.cpp
../../main/code/server/HttpResponse.cpp ../../main/code/server/Server.cpp ../../main/code/server/ServiceFactory.cpp 
../../main/code/server/Services/CreateFileService.cpp ../../main/code/server/Services/CreateFolderService.cpp ../../main/code/server/Services/CreateUserService.cpp ../../main/code/server/Services/GetFileService.cpp ../../main/code/server/Services/GetFolderService.cpp ../../main/code/server/Services/GetUserService.cpp ../../main/code/server/Services/LoginService.cpp ../../main/code/server/Services/LogoutService.cpp ../../main/code/server/Services/NonExistentService.cpp ../../main/code/server/Services/UpdateUserService.cpp ../../main/code/server/Services/DeleteFolderService.cpp ../../main/code/server/Services/DeleteFileService.cpp ../../main/code/server/Services/UpdateFileService.cpp
../../main/others/jsoncpp.cpp  ../../main/others/mongoose.c ../../main/code/utilities/Time.cpp ../../main/code/utilities/WrapperMongoose.cpp ../Mock/MockWrapperMongoose.h  VersionTest.cpp)

# Variable con las librerías
SET(LINK_LIBRARIES rocksdb pthread z bz2 snappy gtest gmock)

# Genera el ejecutable
ADD_EXECUTABLE(VersionTestRun ${SRC_FILES})

# Linkea las librerías
TARGET_LINK_LIBRARIES(VersionTestRun ${LINK_LIBRARIES})
