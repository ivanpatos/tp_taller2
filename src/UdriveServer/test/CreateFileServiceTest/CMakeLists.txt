CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Variable con los fuentes
SET(SRC_FILES 
${CMAKE_SOURCE_DIR}/main/code/resources/File.cpp 
${CMAKE_SOURCE_DIR}/main/code/resources/User.cpp 
${CMAKE_SOURCE_DIR}/main/code/resources/Folder.cpp 
${CMAKE_SOURCE_DIR}/main/code/resources/Version.cpp 
${CMAKE_SOURCE_DIR}/main/code/server/HttpResponse.cpp 

${CMAKE_SOURCE_DIR}/main/code/server/Services/CreateFileService.cpp 

${CMAKE_SOURCE_DIR}/main/others/jsoncpp.cpp  
${CMAKE_SOURCE_DIR}/main/others/mongoose.c 
${CMAKE_SOURCE_DIR}/main/code/utilities/Time.cpp 
${CMAKE_SOURCE_DIR}/main/code/utilities/WrapperMongoose.cpp 
../Mock/MockWrapperMongoose.h 
${CMAKE_SOURCE_DIR}/main/include/database/MockDatabase.h )

# Genera el ejecutable
ADD_EXECUTABLE(CreateFileServiceTestRun ${SRC_FILES} CreateFileServiceTest.cpp)

# Linkea las librerías
TARGET_LINK_LIBRARIES(CreateFileServiceTestRun ${LINK_LIBRARIES})

set(UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} CreateFileServiceTestRun PARENT_SCOPE)
add_test(CreateFileServiceTestRun CreateFileServiceTestRun)
