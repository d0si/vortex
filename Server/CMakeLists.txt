project(Server)


#
# Include project file list variables
#
include(Server.cmake)


#
# Add library
#
add_library(${PROJECT_NAME} SHARED ${SERVER_SOURCES})
add_library(Vortex::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_compile_definitions(${PROJECT_NAME} PUBLIC VORTEX_SERVER_EXPORTS)

find_package(Boost REQUIRED COMPONENTS system)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}
    PUBLIC ${Boost_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC Vortex::Core
    PUBLIC ${Boost_LIBRARIES}
)

include(${PROJECT_SOURCE_DIR}/../cmake/AddFeaturesEnabledDefinitions.cmake)
