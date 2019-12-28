project(maze)

include(${PROJECT_NAME}.cmake)
add_library(${PROJECT_NAME}
    ${${PROJECT_NAME}_SRC}
        src/maze/mazeArray.cpp include/maze/mazeElement.h include/maze/mazeObject.h include/maze/mazeType.h src/maze/mazeType.cpp include/maze/helpers.h src/maze/helpers.cpp)

add_library(vortex::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PUBLIC ${Boost_INCLUDE_DIRS}
    # TODO: Includes for mongodb, v8...
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC ${Boost_LIBRARIES}
    # TODO: References to mongodb, v8...
)
