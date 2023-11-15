cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)

project(la-1)

find_package(OpenGL REQUIRED)
find_package(SFML REQUIRED COMPONENTS system window graphics)
find_package(ImGui-SFML REQUIRED)
find_package(fmt REQUIRED)
find_package(GTest REQUIRED)

add_subdirectory(gauss)

add_executable(gauss-ui gauss-ui.cpp)

target_link_libraries(gauss-ui
    PRIVATE
    sfml-system
    sfml-window
    sfml-graphics

    ImGui-SFML::ImGui-SFML

    fmt::fmt

    gauss)

add_executable(mvc mvc.cpp)

target_link_libraries(mvc
    PRIVATE
    sfml-system
    sfml-window
    sfml-graphics)

