file(GLOB_RECURSE GAME_SOURCES
    CONFIGURE_DEPENDS
    src/*.cpp
)

add_executable(game
  ${SANDBOX_SOURCES}
)

target_include_directories(Rally
    PRIVATE
        include
)

target_link_libraries(Rally
    PRIVATE
        Engine
)

target_compile_features(Rally
    PRIVATE
        cxx_std_23
)
