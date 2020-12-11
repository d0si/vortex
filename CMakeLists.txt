cmake_minimum_required(VERSION 3.13)
project(VortexProject)


#
# Project build configuration options
#
option(VORTEX_ENABLE_FEATURE_MONGO "Enable support for mongo-cxx-driver and mongo-c-driver" OFF)
option(VORTEX_ENABLE_FEATURE_REDIS "Enable support for cpp_redis and tacopie" OFF)
option(VORTEX_ENABLE_FEATURE_DUKTAPE "Enable support for duktape and duktape-cpp" OFF)
option(VORTEX_ENABLE_FEATURE_DELTASCRIPT "Enable support for DeltaScript engine" OFF)
option(VORTEX_ENABLE_FEATURE_CRYPTOPP "Enable support for crypto++" OFF)


#
# Global build settings
#
if(MSVC)
    add_definitions(/MP)    # Build with multiple processes
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

# Build libraries and executables into same directory
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})


#
# Include solution projects
#
###add_subdirectory(dependencies/duktape-cpp)
###add_subdirectory(dependencies/GraphQL-cpp)
add_subdirectory(Core)
###add_subdirectory(Server)
add_subdirectory(Vortex)
