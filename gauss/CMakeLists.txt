cmake_minimum_required(VERSION 3.22)

add_library(gauss STATIC src/gauss.cpp)

target_include_directories(gauss PUBLIC include)

add_executable(gauss-tests tests/gauss-tests.cpp)

enable_testing()

target_link_libraries(gauss-tests PRIVATE
    GTest::gtest
    GTest::gtest_main

    gauss)

add_test(gauss-tests gauss-tests)

