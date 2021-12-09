cmake_minimum_required(VERSION 3.21)
project(Task_Server)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-pthread")

add_executable(Task_Server main_task_server.cpp)
