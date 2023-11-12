cmake_minimum_required(VERSION 3.27)

add_library(gauss STATIC src/gauss.cpp)

target_include_directories(gauss PUBLIC include)

