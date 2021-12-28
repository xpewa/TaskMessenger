add_library(model_lib STATIC src/user.cpp src/task.cpp src/message.cpp)
target_include_directories(model_lib PUBLIC include)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()