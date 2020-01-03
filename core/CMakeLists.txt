project(core)

include(${PROJECT_NAME}.cmake)
add_library(${PROJECT_NAME}
    ${${PROJECT_NAME}_SRC}
)

add_library(vortex::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

find_package(Boost REQUIRED COMPONENTS system)
find_package(libmongocxx REQUIRED)
find_path(DUKTAPE_INCLUDE_DIR duktape.h)
find_library(DUKTAPE_LIBRARIES duktape)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PUBLIC ${Boost_INCLUDE_DIRS}
    PUBLIC ${LIBMONGOCXX_INCLUDE_DIRS}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/cpp_redis/includes
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/cpp_redis/tacopie/includes
    PUBLIC ${DUKTAPE_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC vortex::maze
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC ${LIBMONGOCXX_LIBRARIES}
    PUBLIC ${DUKTAPE_LIBRARIES}
    PUBLIC cpp_redis
)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC ${LIBMONGOCXX_DEFINITIONS}
)
