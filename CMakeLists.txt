cmake_minimum_required(VERSION 3.10)
project(vortexProject)

# Set output properties
set(CMAKE_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/build/lib)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_LIBRARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_BUILD_TYPE Debug)

# Include dependency projects (should be added as submodules ASAP)
add_subdirectory(libs/duktape-cpp)

# Include subprojects
add_subdirectory(maze)
add_subdirectory(core)
add_subdirectory(server)
add_subdirectory(vortex)
