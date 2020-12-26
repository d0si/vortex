#
# This scripts adds the spdlog library as dependency to the project.
#


#
# Add the spdlog project
#
cmake_policy(SET CMP0077 NEW) # This allows new policy to override option variables using normal variables
set(SPDLOG_BUILD_SHARED ON)

add_subdirectory(${PROJECT_SOURCE_DIR}/../dependencies/spdlog ${CMAKE_CURRENT_BINARY_DIR}/spdlog)


#
# Include dependencies into project
#
target_link_libraries(${PROJECT_NAME}
    PUBLIC
		spdlog::spdlog
		spdlog::spdlog_header_only
)
