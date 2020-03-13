cmake_minimum_required(VERSION 3.10)
project(VortexProject)

# Options
option(VORTEX_ENABLE_FEATURE_MONGO "Enable support for mongo-cxx-driver and mongo-c-driver" OFF)
option(VORTEX_ENABLE_FEATURE_REDIS "Enable support for cpp_redis and tacopie" OFF)
option(VORTEX_ENABLE_FEATURE_DUKTAPE "Enable support for duktape and duktape-cpp" OFF)
option(VORTEX_ENABLE_FEATURE_CRYPTOPP "Enable support for crypto++" OFF)

# Set output properties
set(CMAKE_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/build/lib)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_LIBRARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_BUILD_TYPE Debug)

# Include subprojects
add_subdirectory(dependencies/Maze)
add_subdirectory(dependencies/GraphQL-cpp)
add_subdirectory(Core)
add_subdirectory(Server)
add_subdirectory(Vortex)
