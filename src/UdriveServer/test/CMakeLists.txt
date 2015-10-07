cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/test/cmake/Modules/")

enable_testing()

# Locate GTest
find_package(GMock REQUIRED)
include_directories(${GMock_INCLUDE_DIRS})

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Setea flags del compilador
SET(CMAKE_CXX_FLAGS "-std=c++11")

# Variable con las librerías
SET(LINK_LIBRARIES rocksdb pthread z bz2 snappy gtest gmock)

add_subdirectory (UserTest)
add_subdirectory (HttpResponseTest)
add_subdirectory (VersionTest)
add_subdirectory (ServiceFactoryTest)

