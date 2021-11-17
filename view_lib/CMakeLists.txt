add_library(view_lib STATIC src/view.cpp)
target_include_directories(view_lib PUBLIC include)

target_link_libraries(view_lib ui_lib presenter_lib model_lib)