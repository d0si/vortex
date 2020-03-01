project(Server)

SET(SERVER_SOURCES
    src/Server/Http/HttpServer.cpp
    src/Server/Http/HttpListener.cpp
    src/Server/Http/HttpSession.cpp
)

add_library(${PROJECT_NAME}
    ${SERVER_SOURCES}
)

add_library(Vortex::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

find_package(Boost REQUIRED COMPONENTS system)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PUBLIC ${Boost_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC Vortex::Core
    PUBLIC ${Boost_LIBRARIES}
)
