cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 20)

project(la-1)

find_package(OpenGL REQUIRED)
find_package(SFML REQUIRED COMPONENTS system window graphics)
find_package(ImGui-SFML REQUIRED)

add_subdirectory(gauss)

add_executable(la-1-bin main.cpp)

target_link_libraries(la-1-bin
    PRIVATE
    sfml-system
    sfml-window
    sfml-graphics

    ImGui-SFML::ImGui-SFML

    gauss)

