add_executable(model_test model_test.cpp)
target_link_libraries(model_test GTest::Main model_lib)

add_test(NAME model_test COMMAND model_test)