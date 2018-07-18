cmake_minimum_required(VERSION 3.10)

project(software-renderer CXX)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(GCC_COMPILE_FLAGS "-Wall -Wextra -pedantic -Weffc++")
add_definitions(${GCC_COMPILE_FLAGS})

include_directories(include/)

set(INCLUDES
    include/ppm_image.h
    include/drawing_utils.h
    include/math_utils.h
    include/obj_model.h
    include/image_buffer.h
    include/matrix.h
)
set(SOURCES
    src/main.cpp
    src/drawing_utils.cpp
    src/ppm_image.cpp
    src/obj_model.cpp
    src/image_buffer.cpp
)

add_executable(softrender ${SOURCES} ${INCLUDES})
