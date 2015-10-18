CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

option(ONLYTEST "ONLYTEST" OFF)

# Nombre del proyecto
PROJECT(TP_TALLER2)

include(CTest) #!!! DESCOMENTAR ESTA LINEA SI SE QUIERE BUILDEAR CON TESTS - CORRER TESTS Y VER COVERAGE !!!
#Al comentarla, se buildea el server normalmente

if(NOT ONLYTEST)
	add_subdirectory (main)
        unset(ONLYTEST)
endif(NOT ONLYTEST)

if(BUILD_TESTING)
	add_subdirectory (test)
endif()
