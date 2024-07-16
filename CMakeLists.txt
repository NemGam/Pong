cmake_minimum_required(VERSION 3.13)
project(pong)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/dist)

add_compile_definitions(
    RESOURCES_PATH="${CMAKE_INSTALL_PREFIX}/share")

message(STATUS "${CMAKE_INSTALL_PREFIX}/share")

add_executable(
    ${PROJECT_NAME}
    src/ball.cpp
    src/game.cpp
    src/logger.cpp
    src/main.cpp
    src/middle_line.cpp
    src/paddle.cpp
    src/text.cpp
    src/window.cpp
    src/unique_ptrs_destructors.cpp
    src/texture_data.cpp
    src/texture.cpp
    src/asset_database.cpp
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -pedantic)

target_link_libraries(
    ${PROJECT_NAME}
    SDL2
    SDL2_ttf
    SDL2_image
)

install(DIRECTORY resources TYPE DATA)
install(TARGETS ${PROJECT_NAME})

