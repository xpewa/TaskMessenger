cmake_minimum_required(VERSION 3.5)

project(TaskMessenger)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(presenter_lib)
add_subdirectory(ui_lib)
add_subdirectory(client_lib)
add_subdirectory(model_lib)
add_subdirectory(view_lib)

add_executable(TaskMessenger src/main.cpp)

target_link_libraries(TaskMessenger PRIVATE presenter_lib client_lib view_lib)
