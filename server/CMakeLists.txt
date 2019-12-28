project(server)

include(${PROJECT_NAME}.cmake)
add_library(${PROJECT_NAME}
    ${${PROJECT_NAME}_SRC}
)

add_library(vortex::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

find_package(Boost REQUIRED COMPONENTS system)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PUBLIC ${Boost_INCLUDE_DIRS}
    # TODO: Includes for mongodb, v8...
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC vortex::core
    PUBLIC ${Boost_LIBRARIES}
    # TODO: References to mongodb, v8...
)
