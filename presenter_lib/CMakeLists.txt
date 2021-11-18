add_library(presenter_lib STATIC src/presenter.cpp)
target_include_directories(presenter_lib PUBLIC include)

target_link_libraries(presenter_lib PUBLIC view_lib client_lib model_lib)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()