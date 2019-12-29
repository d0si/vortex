project(core)

include(${PROJECT_NAME}.cmake)
add_library(${PROJECT_NAME}
    ${${PROJECT_NAME}_SRC}
)

add_library(vortex::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PUBLIC ${Boost_INCLUDE_DIRS}
    # TODO: Includes for mongodb, v8...
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC vortex::maze
    PUBLIC ${Boost_LIBRARIES}
    # TODO: References to mongodb, v8...
)
