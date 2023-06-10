cmake_minimum_required(VERSION 3.21)
project(PlasmaEngine)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(libraries/glfw)
add_subdirectory(libraries/glm)
include_directories(libraries/glm)
add_executable(PlasmaEngine source/main.cpp)
target_link_libraries(PlasmaEngine glfw)