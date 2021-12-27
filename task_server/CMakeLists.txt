cmake_minimum_required(VERSION 3.20)
project(Task_Server)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-pthread")

add_executable(Task_Server main_task_server.cpp)

add_compile_options(-lmysqlcppconn8)
set(FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR /usr/local/mysql/connector-c++-8.0.27)

find_package(Boost)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

include_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include)
include_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include/mysqlx)
link_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/lib64)

target_link_libraries(Task_Server mysqlcppconn8)
target_link_libraries(Task_Server ${Boost_LIBRARIES})

add_library(dbmanager DBConnection.cpp tables.h)
add_library(userdbmanager IUserDBManager.h UserDBManager.cpp)
add_library(taskdbmanager ITaskDBManager.h TaskDBManager.cpp)

target_link_libraries(Task_Server userdbmanager taskdbmanager dbmanager)