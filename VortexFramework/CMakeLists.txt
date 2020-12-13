project(VortexFramework)


#
# Include project file list variables
#
include(VortexFramework.cmake)


#
# Add library
#
add_library(${PROJECT_NAME} SHARED ${VORTEXFRAMEWORK_SOURCES})
add_library(Vortex::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_compile_definitions(${PROJECT_NAME} PUBLIC VORTEX_APP_EXPORTS)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC Vortex::Core
)

include(${PROJECT_SOURCE_DIR}/../cmake/AddFeaturesEnabledDefinitions.cmake)


#
# Configure enabled features
#
if (VORTEX_ENABLE_FEATURE_DELTASCRIPT)
    include(${PROJECT_SOURCE_DIR}/../cmake/AddDeltaScript.cmake)
endif()
if (VORTEX_ENABLE_FEATURE_DUKTAPE)
    include(${PROJECT_SOURCE_DIR}/../cmake/AddDuktapeCpp.cmake)
endif()