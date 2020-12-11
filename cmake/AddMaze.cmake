#
# This scripts adds the Maze library as dependency to the project.
#


#
# Add the Maze project
#
cmake_policy(SET CMP0077 NEW) # This allows new policy to override option variables
set(MAZE_BUILD_SHARED_LIBS OFF)
set(MAZE_BUILD_TESTS OFF)
set(MAZE_CODE_COVERAGE OFF)

add_subdirectory(${PROJECT_SOURCE_DIR}/../dependencies/Maze ${CMAKE_CURRENT_BINARY_DIR}/Maze)


#
# Include dependencies into project
#
target_link_libraries(${PROJECT_NAME}
    PUBLIC Maze::Maze
)


#
# Add has_feature flag
#
target_compile_definitions(${PROJECT_NAME}
    PRIVATE HAS_FEATURE_MAZE=1
)
