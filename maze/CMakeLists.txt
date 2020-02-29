cmake_minimum_required(VERSION 3.10)
project(maze)

add_library(${PROJECT_NAME}
    src/maze/element.cpp
    src/maze/array.cpp
    src/maze/object.cpp
    src/maze/type.cpp
    src/maze/helpers.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)
