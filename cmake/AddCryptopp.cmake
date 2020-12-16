#
# This scripts adds the cryptopp library as dependency to the project.
#


#
# Find the cryptopp library
#
if (VCPKG_TOOLCHAIN)
    find_package(cryptopp CONFIG REQUIRED)
endif()


#
# Include dependencies into project
#
if (VCPKG_TOOLCHAIN)
    target_link_libraries(${PROJECT_NAME}
        PUBLIC cryptopp-static
    )
else()
    target_link_libraries(${PROJECT_NAME}
        PUBLIC cryptopp
    )
endif()


#
# Add has_feature flag
#
target_compile_definitions(${PROJECT_NAME}
    PUBLIC HAS_FEATURE_CRYPTOPP=1
)
