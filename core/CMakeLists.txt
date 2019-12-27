project(core)

include(${PROJECT_NAME}.cmake)
add_library(${PROJECT_NAME}
    ${${$PROJECT_NAME}_SRC}
)

add_library(vortex::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    # TODO: Includes for boost, mongodb, v8...
)

target_link_libraries(${PROJECT_NAME}
    # TODO: References to boost, mongodb, v8...
)
