CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Variable con los fuentes
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
${CMAKE_SOURCE_DIR}/main/code/server/Services/UpdateFolderService.cpp
${CMAKE_SOURCE_DIR}/main/others/jsoncpp.cpp  
${CMAKE_SOURCE_DIR}/main/others/mongoose.c 
${CMAKE_SOURCE_DIR}/main/code/utilities/Time.cpp 
${CMAKE_SOURCE_DIR}/main/code/utilities/WrapperMongoose.cpp 
../Mock/MockWrapperMongoose.h)

# Genera el ejecutable
ADD_EXECUTABLE(VersionTestRun ${SRC_FILES} VersionTest.cpp)

# Linkea las librerías
TARGET_LINK_LIBRARIES(VersionTestRun ${LINK_LIBRARIES})

set(UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} VersionTestRun PARENT_SCOPE)
add_test(VersionTestRun VersionTestRun)
