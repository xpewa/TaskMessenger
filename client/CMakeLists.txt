cmake_minimum_required(VERSION 3.5)
project(TaskMessenger)

set(CMAKE_CXX_STANDARD 17)

add_compile_options("-pthread")
add_link_options("-pthread")

#option(WITH_TESTS "Build tests" ON)
#if (WITH_TESTS)
#    enable_testing()
#    find_package(GTest REQUIRED)
#    find_package(PkgConfig REQUIRED)
#    pkg_search_module(GMOCK gmock REQUIRED)
#    set(BUILD_TESTS ON)
#endif()

add_subdirectory(presenter_lib)
add_subdirectory(ui_lib)
add_subdirectory(client_lib)
add_subdirectory(model_lib)
add_subdirectory(view_lib)

add_executable(TaskMessenger src/main.cpp)

target_link_libraries(TaskMessenger PRIVATE presenter_lib client_lib view_lib)
