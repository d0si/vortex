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
    PUBLIC ${CMAKE_SOURCE_DIR}/libs/cpp_redis/includes
    PUBLIC ${CMAKE_SOURCE_DIR}/libs/cpp_redis/tacopie/includes
    PUBLIC ${CMAKE_SOURCE_DIR}/libs/duktape-cpp/src
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC vortex::maze
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC ${LIBMONGOCXX_LIBRARIES}
    PUBLIC cpp_redis
    PUBLIC duktape
    PUBLIC tacopie
)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC ${LIBMONGOCXX_DEFINITIONS}
)
