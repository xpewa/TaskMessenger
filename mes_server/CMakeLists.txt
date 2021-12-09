#cmake_minimum_required(VERSION 3.8)
#set (CMAKE_CXX_STANDARD 14)
#
#project(server)
#
#find_package(Boost)
#include_directories(${Boost_INCLUDE_DIRS})
#
#
#add_executable(server server.cpp )
#target_link_libraries(server  pthread ${Boost_LIBRARIES})
#add_compile_options(-pthread)
#add_link_options(-pthread)

#ту ду