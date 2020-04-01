project(Core)

# Set cpp sources
set(CORE_SOURCES
    Core/Framework.cpp
    Core/CommonRuntime.cpp
    Core/Router.cpp
    Core/Host.cpp
    Core/Application.cpp
    Core/Controller.cpp
    Core/View.cpp
    Core/User.cpp

    Core/Storage/Storage.cpp
    Core/Storage/Mongo/Mongo.cpp
    Core/Storage/Mongo/Db.cpp
    Core/Storage/Mongo/Collection.cpp
    Core/Storage/Mongo/MongoBackend.cpp
    Core/Storage/Filesystem/FilesystemBackend.cpp

    Core/Cache/Cache.cpp
    Core/Cache/Backends/RedisBackend.cpp
    Core/Cache/Backends/MemoryCacheBackend.cpp
    Core/Cache/Backends/DummyCacheBackend.cpp

    Core/Script/Script.cpp
    Core/Script/Duktape.cpp

    Core/Util/Time.cpp
    Core/Util/Random.cpp
    Core/Util/Password.cpp
    Core/Util/String.cpp
    Core/Util/Hash.cpp

    Core/Exception/VortexException.cpp
    Core/Exception/StorageException.cpp
    Core/Exception/CacheException.cpp
    Core/Exception/FrameworkExitException.cpp
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
    PUBLIC ${PROJECT_SOURCE_DIR}
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
