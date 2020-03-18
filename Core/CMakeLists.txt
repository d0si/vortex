project(Core)

# Set cpp sources
set(CORE_SOURCES
    src/Core/Framework.cpp
    src/Core/CommonRuntime.cpp
    src/Core/Router.cpp
    src/Core/Host.cpp
    src/Core/Application.cpp
    src/Core/Controller.cpp
    src/Core/View.cpp

    src/Core/Storage/Storage.cpp
    src/Core/Storage/Mongo/Mongo.cpp
    src/Core/Storage/Mongo/Db.cpp
    src/Core/Storage/Mongo/Collection.cpp
    src/Core/Storage/Mongo/MongoBackend.cpp
    src/Core/Storage/Filesystem/Filesystem.cpp
    src/Core/Storage/Filesystem/Database.cpp
    src/Core/Storage/Filesystem/Collection.cpp
    src/Core/Storage/Filesystem/FilesystemBackend.cpp

    src/Core/Cache/Cache.cpp
    src/Core/Cache/Backends/RedisBackend.cpp

    src/Core/Script/Script.cpp
    src/Core/Script/Duktape.cpp

    src/Core/Util/Time.cpp
    src/Core/Util/Random.cpp
    src/Core/Util/Password.cpp
    src/Core/Util/String.cpp
    src/Core/Util/Hash.cpp

    src/Core/Exception/VortexException.cpp
    src/Core/Exception/StorageException.cpp
    src/Core/Exception/CacheException.cpp
)

add_library(${PROJECT_NAME}
    ${CORE_SOURCES}
)

add_library(Vortex::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

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
#    PUBLIC graphqlparser
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
        PUBLIC VORTEX_HAS_FEATURE_MONGO=1
    )
endif()

if (VORTEX_ENABLE_FEATURE_REDIS)
    target_include_directories(${PROJECT_NAME}
        PUBLIC ${CMAKE_SOURCE_DIR}/libs/cpp_redis/includes
        PUBLIC ${CMAKE_SOURCE_DIR}/libs/cpp_redis/tacopie/includes
    )

    if (VCPKG_TOOLCHAIN)
        if (CMAKE_BUILD_TYPE STREQUAL "Debug")
            target_link_directories(${PROJECT_NAME}
                PUBLIC ${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/debug/lib
            )
        else()
            target_link_directories(${PROJECT_NAME}
                PUBLIC ${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/lib
            )
        endif()
    endif()

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
        PUBLIC ${CMAKE_SOURCE_DIR}/dependencies/duktape-cpp/src
    )

    target_link_libraries(${PROJECT_NAME}
        PUBLIC duktape
    )
    
    if (VCPKG_TOOLCHAIN)
        if (CMAKE_BUILD_TYPE STREQUAL "Debug")
            target_link_directories(${PROJECT_NAME}
                PUBLIC ${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/debug/lib
            )
        else()
            target_link_directories(${PROJECT_NAME}
                PUBLIC ${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/lib
            )
        endif()
    endif()

    target_compile_definitions(${PROJECT_NAME}
        PUBLIC VORTEX_HAS_FEATURE_DUKTAPE=1
    )
endif()

if (VORTEX_ENABLE_FEATURE_CRYPTOPP)
    if (VCPKG_TOOLCHAIN)
        find_package(cryptopp CONFIG REQUIRED)

        target_link_libraries(${PROJECT_NAME}
	        PUBLIC cryptopp-static
        )
    else()
        target_link_libraries(${PROJECT_NAME}
	        PUBLIC cryptopp
        )
    endif()

    target_compile_definitions(${PROJECT_NAME}
        PUBLIC VORTEX_HAS_FEATURE_CRYPTOPP=1
    )
endif()

target_compile_definitions(${PROJECT_NAME}
    PUBLIC ${LIBMONGOCXX_DEFINITIONS}
)
