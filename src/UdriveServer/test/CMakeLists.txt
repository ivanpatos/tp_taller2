cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/test/cmake/Modules/")

FIND_PROGRAM( GCOV_PATH gcov )
FIND_PROGRAM( LCOV_PATH lcov )
FIND_PROGRAM( GENHTML_PATH genhtml )
FIND_PROGRAM( GCOVR_PATH gcovr PATHS ${CMAKE_SOURCE_DIR}/test)

enable_testing()

# Locate GMock
find_package(GMock REQUIRED)
include_directories(${GMock_INCLUDE_DIRS})

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Setea flags del compilador
SET(CMAKE_CXX_FLAGS "-std=c++11 -g -O0 -Wall -fprofile-arcs -ftest-coverage")
SET(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")
SET(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

# Variable con las librerías
SET(LINK_LIBRARIES pthread z bz2 snappy gtest gmock gcov)

if(BUILD_TESTING)
	add_subdirectory (UserTest)
	add_subdirectory (HttpResponseTest)
	add_subdirectory (VersionTest)
	add_subdirectory (ServiceFactoryTest)
        add_subdirectory (FolderTest)
        add_subdirectory (FileTest)

	#creo un target cuya dependencia son todos los unit tests ( deben ser agregados manualmente )
	add_custom_target( all_tests ALL
		           DEPENDS ${UNIT_TEST_TARGETS}
	)
	
	#antes de ejecutar los tests limpio lcov y empiezo captura
	add_custom_command(	TARGET all_tests
			   	COMMENT "borrando zero counters"
			   	PRE_BUILD 
				# Cleanup lcov
				COMMAND ${LCOV_PATH} --directory . --zerocounters 
				COMMAND ${LCOV_PATH} --capture --initial --directory . --output-file output.info
	)


	# al terminarse de compilar todos los unit tests... se ejecuta ctest y luego lcov y genhtml para ver cobertura de tests
	add_custom_command(	TARGET all_tests
		           	COMMENT "Run tests"
		           	POST_BUILD 
				COMMAND ctest ARGS --output-on-failure
				# Capturing lcov counters and generating report

				COMMAND ${LCOV_PATH} --no-checksum --directory . --capture --output-file output.info
				COMMAND ${GENHTML_PATH} output.info
	)
endif()

