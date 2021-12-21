cmake_minimum_required(VERSION 3.8)
set (CMAKE_CXX_STANDARD 14)

project(server)

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

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
