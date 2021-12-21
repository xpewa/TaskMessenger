cmake_minimum_required(VERSION 3.8)
set (CMAKE_CXX_STANDARD 14)

project(server)

#find_package(Boost)
#include_directories(${Boost_INCLUDE_DIRS})
add_compile_options(-lmysqlcppconn8)
set(FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR /usr/local/mysql/connector-c++-8.0.27)

find_package(Boost)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

include_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include)
include_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include/mysqlx)
link_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/lib64)


add_library(Server Server/Server.cpp)
add_library(Connection Connection/Connection.cpp)

add_executable(server Main/main.cpp)
target_link_libraries(server Server Connection)
target_link_libraries(server  pthread ${Boost_LIBRARIES})
add_compile_options(-pthread)
add_link_options(-pthread)

#add_compile_options(-lmysqlcppconn8)
include_directories(/home/user/install_connector/mysql-connector-cpp/include/)
target_link_libraries(server mysqlcppconn8)


#target_link_libraries(server mysqlcppconn8)
#target_link_libraries(server ${Boost_LIBRARIES})

add_library(dbmanager DBConnection.cpp tables.h)
add_library(userdbmanager IUserDBManager.h UserDBManager.cpp)
add_library(taskdbmanager IMessageDBManager.h MessageDBManager.cpp)

target_link_libraries(server userdbmanager taskdbmanager dbmanager)
