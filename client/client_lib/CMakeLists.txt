find_package(Boost)
#include_directories(${Boost_INCLUDE_DIRS})

add_library(client_lib STATIC src/client.cpp)
target_include_directories(client_lib PUBLIC include)

target_link_libraries(client_lib PRIVATE model_lib Boost::boost)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()