add_executable(client_test client_test.cpp)
target_link_libraries(client_test GTest::Main client_lib model_lib)

add_test(NAME client_test COMMAND client_test)