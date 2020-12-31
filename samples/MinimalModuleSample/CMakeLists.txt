project(MinimalModuleSample)


#
# Include project file list variables
#
include(Module.cmake)


add_library(${PROJECT_NAME} SHARED ${MODULE_SOURCES})
add_library(Vortex::App::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_compile_definitions(${PROJECT_NAME} PUBLIC VORTEX_APP_EXPORTS)

target_link_libraries(${PROJECT_NAME}
    PUBLIC Vortex::Core
)

include(${PROJECT_SOURCE_DIR}/../../cmake/AddFeaturesEnabledDefinitions.cmake)
