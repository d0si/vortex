#
# This scripts adds the cpp_redis library as dependency to the project.
#


#
# Include dependencies into project
#
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


#
# Add has_feature flag
#
target_compile_definitions(${PROJECT_NAME}
    PRIVATE HAS_FEATURE_CPPREDIS=1
)
