set(CMAKE_BUILD_TYPE Debug)
set(GCC_COMPILE_FLAGS "-Wall -Wextra -pedantic -Weffc++")
add_definitions(${GCC_COMPILE_FLAGS})

FILE(GLOB SOURCES *.cpp)
add_executable(softrender ${SOURCES})
target_link_libraries(softrender ${SDL2_LIBRARY})
