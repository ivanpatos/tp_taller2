CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Variable con los fuentes
SET(SRC_FILES 
${CMAKE_SOURCE_DIR}/main/code/database/Database.cpp 
${CMAKE_SOURCE_DIR}/main/code/resources/File.cpp 
${CMAKE_SOURCE_DIR}/main/code/resources/Folder.cpp 
${CMAKE_SOURCE_DIR}/main/others/jsoncpp.cpp 
${CMAKE_SOURCE_DIR}/main/others/mongoose.c
${CMAKE_SOURCE_DIR}/main/code/resources/User.cpp 
${CMAKE_SOURCE_DIR}/main/code/utilities/Time.cpp 
${CMAKE_SOURCE_DIR}/main/code/utilities/WrapperMongoose.cpp
../Utils/Utils.h
../Mock/MockDatabase.h )

# Genera el ejecutable
ADD_EXECUTABLE(FolderTestRun ${SRC_FILES} FolderTest.cpp )

# Linkea las librerías
TARGET_LINK_LIBRARIES(FolderTestRun ${LINK_LIBRARIES})

set(UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} FolderTestRun PARENT_SCOPE)
add_test( FolderTestRun FolderTestRun )
