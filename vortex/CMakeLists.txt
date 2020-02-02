project(vortex)

include(${PROJECT_NAME}.cmake)
add_executable(${PROJECT_NAME}
    ${${PROJECT_NAME}_SRC}
)

find_package(Boost REQUIRED COMPONENTS system filesystem)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
    vortex::core
    vortex::server
    pthread
    ${Boost_LIBRARIES}
)
