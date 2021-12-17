cmake_minimum_required(VERSION 3.20)
project(TaskManager_DB)

set(CMAKE_CXX_STANDARD 20)

add_executable(main main.cpp)

add_compile_options(-lmysqlcppconn8)

set(FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR /usr/local/mysql/connector-c++-8.0.27)

find_package(Boost COMPONENTS locale REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

include_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include)
include_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include/mysqlx)
link_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/lib64)

target_link_libraries(main mysqlcppconn8)
target_link_libraries(main ${Boost_LIBRARIES})

add_library(dbmanager IDBManager.cpp tables.h)
add_library(userdbmanager UserDBManager.cpp)
add_library(taskdbmanager TaskDBManager.cpp)
add_library(messagedbmanager MessageDBManager.cpp)

target_link_libraries(main userdbmanager taskdbmanager messagedbmanager dbmanager)

#enable_testing()
#find_package(GTest REQUIRED)
#
#include_directories(${GTEST_INCLUDE_DIRS})
#add_executable(tests tests.cpp)
#target_link_libraries(tests ${GTEST_LIBRARIES} userdbmanager taskdbmanager messagedbmanager dbmanager pthread)