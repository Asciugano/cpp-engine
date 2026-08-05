find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

file(GLOB_RECURSE ENGINE_SOURCES
    CONFIGURE_DEPENDS
    src/*.cpp
)

add_library(Engine STATIC
  ${ENGINE_SOURCES}
)

target_include_directories(Engine
    PUBLIC
        include

)

target_link_libraries(Engine
    PUBLIC
        glfw
        glm::glm
        glbinding::glbinding
)

target_compile_features(Engine
    PUBLIC
        cxx_std_23
)
