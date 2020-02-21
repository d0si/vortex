project(core)

include(${PROJECT_NAME}.cmake)
add_library(${PROJECT_NAME}
    ${${PROJECT_NAME}_SRC}
)

add_library(vortex::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

find_package(Boost REQUIRED COMPONENTS system)

if (VORTEX_ENABLE_FEATURE_MONGO)
    find_package(libmongocxx REQUIRED)
endif()

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PUBLIC ${Boost_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC maze
    PUBLIC ${Boost_LIBRARIES}
)

if (VORTEX_ENABLE_FEATURE_MONGO)
    target_include_directories(${PROJECT_NAME}
        PUBLIC ${LIBMONGOCXX_INCLUDE_DIRS}
    )

    target_link_libraries(${PROJECT_NAME}
        PUBLIC ${LIBMONGOCXX_LIBRARIES}
    )

    target_compile_definitions(${PROJECT_NAME}
        PRIVATE VORTEX_HAS_FEATURE_MONGO=1
    )
endif()

if (VORTEX_ENABLE_FEATURE_REDIS)
    target_include_directories(${PROJECT_NAME}
        PUBLIC ${CMAKE_SOURCE_DIR}/libs/cpp_redis/includes
        PUBLIC ${CMAKE_SOURCE_DIR}/libs/cpp_redis/tacopie/includes
    )

    target_link_libraries(${PROJECT_NAME}
        PUBLIC cpp_redis
        PUBLIC tacopie
    )

    target_compile_definitions(${PROJECT_NAME}
        PRIVATE VORTEX_HAS_FEATURE_REDIS=1
    )
endif()

if (VORTEX_ENABLE_FEATURE_DUKTAPE)
    target_include_directories(${PROJECT_NAME}
        PUBLIC ${CMAKE_SOURCE_DIR}/libs/duktape-cpp/src
    )

    target_link_libraries(${PROJECT_NAME}
        PUBLIC duktape
    )
    
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE VORTEX_HAS_FEATURE_DUKTAPE=1
    )
endif()

if (VORTEX_ENABLE_FEATURE_CRYPTOPP)
    target_link_libraries(${PROJECT_NAME}
	    PUBLIC cryptopp
    )

    target_compile_definitions(${PROJECT_NAME}
        PRIVATE VORTEX_HAS_FEATURE_CRYPTOPP=1
    )
endif()

target_compile_definitions(${PROJECT_NAME}
    PUBLIC ${LIBMONGOCXX_DEFINITIONS}
)
