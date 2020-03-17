project(Vortex)

SET(VORTEX_SOURCES
    src/main.cpp
    src/Vortex/Vortex.cpp
)

add_executable(${PROJECT_NAME}
    ${VORTEX_SOURCES}
)

find_package(Boost REQUIRED COMPONENTS system filesystem)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
    Vortex::Core
    Vortex::Server
    ${Boost_LIBRARIES}
)

if (!WIN32)
target_link_libraries(${PROJECT_NAME}
    pthread
)
endif()
