cmake_minimum_required(VERSION 3.27)

add_library(gauss STATIC src/gauss.cpp)

target_include_directories(gauss PUBLIC include)

add_executable(gauss-tests tests/gauss-tests.cpp)

target_link_libraries(gauss-tests PRIVATE
    GTest::gtest
    GTest::gtest_main

    gauss)

