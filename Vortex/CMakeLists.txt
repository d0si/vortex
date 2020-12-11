project(Vortex)


#
# Include project file list variables
#
include(Vortex.cmake)


#
# Add executable
#
add_executable(${PROJECT_NAME} ${VORTEX_SOURCES})

find_package(Boost REQUIRED COMPONENTS system filesystem)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}
    PUBLIC ${PROJECT_SOURCE_DIR}/../dependencies/Maze/dependencies/nlohmann/json/include
)

target_link_libraries(${PROJECT_NAME}
    Vortex::Core
#    Vortex::Server
    ${Boost_LIBRARIES}
)

if (!WIN32)
    target_link_libraries(${PROJECT_NAME}
        pthread
    )
endif()


#
# Copy sample config file into build directory
#
configure_file(${PROJECT_SOURCE_DIR}/../samples/server_config.json ../server_config.json COPYONLY)
