# Para generar el make ejecutar: cmake CMakeLists.txt  
# Luego ejecutar: make
# Finalmente correr con ./server_udropbox


CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

# Nombre del proyecto
PROJECT(server_udropbox)

# Setea flags del compilador
SET(CMAKE_CXX_FLAGS "-std=c++11")

# Variable con los fuentes
SET(SRC_FILES serverUDropbox.cpp jsoncpp.cpp mongoose.c)

# Variable con las librerías
SET(LINK_LIBRARIES rocksdb pthread z bz2 snappy)

# Genera el ejecutable
ADD_EXECUTABLE(server_udropbox ${SRC_FILES})

# Linkea las librerías
TARGET_LINK_LIBRARIES(server_udropbox ${LINK_LIBRARIES})
