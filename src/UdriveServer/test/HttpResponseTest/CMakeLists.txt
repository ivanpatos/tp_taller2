CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Variable con los fuentes
SET(SRC_FILES 
#${CMAKE_SOURCE_DIR}/main/code/database/Database.cpp 
${CMAKE_SOURCE_DIR}/main/code/server/HttpResponse.cpp 
${CMAKE_SOURCE_DIR}/main/others/jsoncpp.cpp 
${CMAKE_SOURCE_DIR}/main/others/mongoose.c 
${CMAKE_SOURCE_DIR}/main/code/utilities/Time.cpp 
${CMAKE_SOURCE_DIR}/main/code/utilities/WrapperMongoose.cpp
../Mock/MockWrapperMongoose.h 
${CMAKE_SOURCE_DIR}/main/include/database/MockDatabase.h )

# Genera el ejecutable
ADD_EXECUTABLE(HttpResponseTestRun ${SRC_FILES} HttpResponseTest.cpp )

# Linkea las librerías
TARGET_LINK_LIBRARIES(HttpResponseTestRun ${LINK_LIBRARIES})

set(UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} HttpResponseTestRun PARENT_SCOPE)
add_test( HttpResponseTestRun HttpResponseTestRun )
