list(APPEND CMAKE_MODULE_PATH
    ${Catch2_SOURCE_DIR}/extras
)

include(Catch)

file(GLOB_RECURSE TEST_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_executable(EngineTests
    ${TEST_SOURCES}
)


target_include_directories(EngineTests
    PRIVATE
        ${CMAKE_SOURCE_DIR}/engine/include
)


target_link_libraries(EngineTests
    PRIVATE
        Engine
        Catch2::Catch2WithMain
)

target_compile_definitions(EngineTests
    PRIVATE
        TEST_ASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets"
)

add_test(EngineTests EngineTests)

catch_discover_tests(EngineTests)
