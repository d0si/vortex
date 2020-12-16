project(Core)


#
# Include project file list variables
#
include(Core.cmake)


#
# Add library
#
add_library(${PROJECT_NAME} SHARED ${CORE_SOURCES})
add_library(Vortex::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_compile_definitions(${PROJECT_NAME} PUBLIC VORTEX_CORE_EXPORTS)

find_package(Boost REQUIRED COMPONENTS system filesystem)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}
    PUBLIC ${Boost_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC Maze::Maze
    PUBLIC ${Boost_LIBRARIES}
)

include(${PROJECT_SOURCE_DIR}/../cmake/AddMaze.cmake)


#
# Configure enabled features
#
if (VORTEX_ENABLE_FEATURE_MONGO)
    include(${PROJECT_SOURCE_DIR}/../cmake/AddMongocxx.cmake)
endif()
if (VORTEX_ENABLE_FEATURE_REDIS)
    include(${PROJECT_SOURCE_DIR}/../cmake/AddCppRedis.cmake)
endif()
if (VORTEX_ENABLE_FEATURE_DELTASCRIPT)
    include(${PROJECT_SOURCE_DIR}/../cmake/AddDeltaScript.cmake)
endif()
if (VORTEX_ENABLE_FEATURE_DUKTAPE)
    include(${PROJECT_SOURCE_DIR}/../cmake/AddDuktapeCpp.cmake)
endif()
if (VORTEX_ENABLE_FEATURE_CRYPTOPP)
    include(${PROJECT_SOURCE_DIR}/../cmake/AddCryptopp.cmake)
endif()
