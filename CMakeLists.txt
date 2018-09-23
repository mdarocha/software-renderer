cmake_minimum_required(VERSION 3.10)
project(software-renderer CXX)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

include_directories(${PROJECT_SOURCE_DIR}/include/)
add_subdirectory(src)

enable_testing()
add_subdirectory(tests)
