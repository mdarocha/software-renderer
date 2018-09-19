find_package(Catch2 REQUIRED)

add_executable(test_vector test_vector.cpp)
target_link_libraries(test_vector Catch2::Catch2)

add_test(NAME math_vector COMMAND test_vector)
