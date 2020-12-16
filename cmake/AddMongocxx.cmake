#
# This scripts adds the mongocxx library as dependency to the project.
#


#
# Find the mongocxx library
#
find_package(libmongocxx REQUIRED)


#
# Include dependencies into project
#
target_include_directories(${PROJECT_NAME}
    PUBLIC ${LIBMONGOCXX_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC ${LIBMONGOCXX_LIBRARIES}
)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC ${LIBMONGOCXX_DEFINITIONS}
)


#
# Add has_feature flag
#
target_compile_definitions(${PROJECT_NAME}
    PUBLIC HAS_FEATURE_MONGOCXX=1
)
