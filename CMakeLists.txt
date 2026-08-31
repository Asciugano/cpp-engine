cmake_minimum_required(VERSION 3.24)

project(
    Rally
    VERSION 0.1.0
    DESCRIPTION "Low Poly Rally Game"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/CPM.cmake)
include(cmake/Dependencies.cmake)

set(RALLY_ASSETS_DIR
    ${CMAKE_SOURCE_DIR}/assets
)

set(RALLY_ASSETS_BINARY_DIR
    ${CMAKE_BINARY_DIR}/assets
)

add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${RALLY_ASSETS_DIR}
        ${RALLY_ASSETS_BINARY_DIR}
    COMMENT "Copying game assets..."
)

add_subdirectory(engine)
add_subdirectory(game)
# add_subdirectory(sandbox)
