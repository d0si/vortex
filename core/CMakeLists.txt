project(core)

include(${PROJECT_NAME}.cmake)
add_library(${PROJECT_NAME}
    ${${PROJECT_NAME}_SRC}
)

add_library(vortex::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

find_package(Boost REQUIRED COMPONENTS system)
find_package(libmongocxx REQUIRED)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PUBLIC ${Boost_INCLUDE_DIRS}
    PUBLIC ${LIBMONGOCXX_INCLUDE_DIRS}
    # TODO: Includes for v8...
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC vortex::maze
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC ${LIBMONGOCXX_LIBRARIES}
    # TODO: References to v8...
)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC ${LIBMONGOCXX_DEFINITIONS}
)
