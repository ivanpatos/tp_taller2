# Para generar el make ejecutar en la carpeta donde se quiere buildear: cmake path_dir_con_fuentes  (recomendacion no hacerlo en la misma carpeta donde estan los fuentes)
# Luego ejecutar: make
# Finalmente correr con ./udrive_server


CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Nombre del proyecto
PROJECT(TP_TALLER2)

# Setea flags del compilador
SET(CMAKE_CXX_FLAGS "-std=c++11")

# Variable con los fuentes
SET(SRC_FILES DataManager.cpp HttpResponse.cpp jsoncpp.cpp Main.cpp mongoose.c RestServer.cpp ServiceManager.cpp Time.cpp User.cpp)

# Variable con las librerías
SET(LINK_LIBRARIES rocksdb pthread z bz2 snappy)

# Genera el ejecutable
ADD_EXECUTABLE(udrive_server ${SRC_FILES})

# Linkea las librerías
TARGET_LINK_LIBRARIES(udrive_server ${LINK_LIBRARIES})
