add_executable(view_test view_test.cpp)
target_link_libraries(view_test GTest::Main view_lib)

add_test(NAME view_test COMMAND view_test)