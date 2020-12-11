#
# This scripts adds the duktape-cpp library as dependency to the project.
#


#
# Include dependencies into project
#
target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/../dependencies/duktape-cpp/src
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


#
# Add has_feature flag
#
target_compile_definitions(${PROJECT_NAME}
    PUBLIC HAS_FEATURE_DUKTAPE=1
)
