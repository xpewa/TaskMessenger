add_executable(presenter_test presenter_test.cpp)
target_link_libraries(presenter_test GTest::Main presenter_lib)

add_test(NAME presenter_test COMMAND presenter_test)