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
SET(SRC_FILES ../../main/code/database/Database.cpp ../../main/code/server/HttpResponse.cpp ../../main/others/jsoncpp.cpp HttpResponseTest.cpp ../Mock/MockWrapperMongoose.h ../../main/others/mongoose.c ../../main/code/utilities/Time.cpp ../../main/code/utilities/WrapperMongoose.cpp)

# Variable con las librerías
SET(LINK_LIBRARIES rocksdb pthread z bz2 snappy gtest gmock)

# Genera el ejecutable
ADD_EXECUTABLE(HttpResponseTestRun ${SRC_FILES})

# Linkea las librerías
TARGET_LINK_LIBRARIES(HttpResponseTestRun ${LINK_LIBRARIES})
