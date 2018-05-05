cmake_minimum_required(VERSION 3.10)

project(software-renderer CXX)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(GCC_COMPILE_FLAGS "-Wall -Wextra -pedantic")
add_definitions(${GCC_COMPILE_FLAGS})

set(SOURCES drawing_utils.cpp ppm_image.cpp obj_model.cpp)
add_executable(softrender main.cpp ${SOURCES})
