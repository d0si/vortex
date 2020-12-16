#
# This scripts adds the DeltaScript library as dependency to the project.
#


#
# Add the DeltaScript project
#
add_subdirectory(${PROJECT_SOURCE_DIR}/../dependencies/DeltaScript ${CMAKE_CURRENT_BINARY_DIR}/DeltaScript)


#
# Include dependencies into project
#
target_link_libraries(${PROJECT_NAME}
    PUBLIC DeltaScript
)


#
# Add has_feature flag
#
target_compile_definitions(${PROJECT_NAME}
    PRIVATE HAS_FEATURE_DELTASCRIPT=1
)
