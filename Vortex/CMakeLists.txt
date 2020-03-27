project(Vortex)

SET(VORTEX_SOURCES
    main.cpp
    Vortex/Vortex.cpp
)

add_executable(${PROJECT_NAME}
    ${VORTEX_SOURCES}
)

find_package(Boost REQUIRED COMPONENTS system filesystem)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    Vortex::Core
    Vortex::Server
    ${Boost_LIBRARIES}
)

configure_file(${PROJECT_SOURCE_DIR}/../samples/server_config.json server_config.json COPYONLY)

if (!WIN32)
target_link_libraries(${PROJECT_NAME}
    pthread
)
endif()
