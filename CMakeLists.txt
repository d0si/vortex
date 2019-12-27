cmake_minimum_required(VERSION 3.11)
project(vortexProject)

# Set output properties
set(CMAKE_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/build/lib)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_LIBRARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_BUILD_TYPE Debug)

# Include subprojects
add_subdirectory(core)
add_subdirectory(server)
add_subdirectory(vortex)
