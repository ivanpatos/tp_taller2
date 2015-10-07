cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/test/cmake/Modules/")

# Locate GTest
find_package(GMock REQUIRED)
include_directories(${GMock_INCLUDE_DIRS})

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Setea flags del compilador
SET(CMAKE_CXX_FLAGS "-std=c++11")

#variable con los cpp
SET(SRC_FILES 
${CMAKE_SOURCE_DIR}/main/code/database/Database.cpp 
${CMAKE_SOURCE_DIR}/main/code/resources/File.cpp 
${CMAKE_SOURCE_DIR}/main/code/resources/Folder.cpp 
${CMAKE_SOURCE_DIR}/main/code/resources/User.cpp 
${CMAKE_SOURCE_DIR}/main/code/resources/Version.cpp
${CMAKE_SOURCE_DIR}/main/code/server/HttpResponse.cpp 
${CMAKE_SOURCE_DIR}/main/code/server/Server.cpp 
${CMAKE_SOURCE_DIR}/main/code/server/ServiceFactory.cpp 
${CMAKE_SOURCE_DIR}/main/code/server/Services/CreateFileService.cpp 
${CMAKE_SOURCE_DIR}/main/code/server/Services/CreateFolderService.cpp 
${CMAKE_SOURCE_DIR}/main/code/server/Services/CreateUserService.cpp 
${CMAKE_SOURCE_DIR}/main/code/server/Services/GetFileService.cpp 
${CMAKE_SOURCE_DIR}/main/code/server/Services/GetFolderService.cpp 
${CMAKE_SOURCE_DIR}/main/code/server/Services/GetUserService.cpp 
${CMAKE_SOURCE_DIR}/main/code/server/Services/LoginService.cpp 
${CMAKE_SOURCE_DIR}/main/code/server/Services/LogoutService.cpp 
${CMAKE_SOURCE_DIR}/main/code/server/Services/NonExistentService.cpp 
${CMAKE_SOURCE_DIR}/main/code/server/Services/UpdateUserService.cpp 
${CMAKE_SOURCE_DIR}/main/code/server/Services/DeleteFolderService.cpp 
${CMAKE_SOURCE_DIR}/main/code/server/Services/DeleteFileService.cpp 
${CMAKE_SOURCE_DIR}/main/code/server/Services/UpdateFileService.cpp
${CMAKE_SOURCE_DIR}/main/others/jsoncpp.cpp
${CMAKE_SOURCE_DIR}/main/others/mongoose.c 
${CMAKE_SOURCE_DIR}/main/code/utilities/Time.cpp 
${CMAKE_SOURCE_DIR}/main/code/utilities/WrapperMongoose.cpp 
../Mock/MockWrapperMongoose.h )

# Variable con las librerías
SET(LINK_LIBRARIES rocksdb pthread z bz2 snappy)

add_subdirectory (UserTest)

