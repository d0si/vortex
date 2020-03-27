cmake_minimum_required(VERSION 3.10)
project(VortexProject)

# Options
option(VORTEX_ENABLE_FEATURE_MONGO "Enable support for mongo-cxx-driver and mongo-c-driver" OFF)
option(VORTEX_ENABLE_FEATURE_REDIS "Enable support for cpp_redis and tacopie" OFF)
option(VORTEX_ENABLE_FEATURE_DUKTAPE "Enable support for duktape and duktape-cpp" OFF)
option(VORTEX_ENABLE_FEATURE_CRYPTOPP "Enable support for crypto++" OFF)

# Include subprojects
add_subdirectory(dependencies/Maze)
#add_subdirectory(dependencies/duktape-cpp)
#add_subdirectory(dependencies/GraphQL-cpp)
add_subdirectory(Core)
add_subdirectory(Server)
add_subdirectory(Vortex)
