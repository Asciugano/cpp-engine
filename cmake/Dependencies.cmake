CPMAddPackage(
    NAME glfw
    GITHUB_REPOSITORY glfw/glfw
    GIT_TAG 3.4
    OPTIONS
        "GLFW_BUILD_DOCS OFF"
        "GLFW_BUILD_TESTS OFF"
        "GLFW_BUILD_EXAMPLES OFF"
)

CPMAddPackage(
    NAME glm
    GITHUB_REPOSITORY g-truc/glm
    GIT_TAG 1.0.1
    OPTIONS
        "GLFW_BUILD_DOCS OFF"
        "GLFW_BUILD_TESTS OFF"
        "GLFW_BUILD_EXAMPLES OFF"
)

CPMAddPackage(
    NAME glbinding
    GITHUB_REPOSITORY cginternals/glbinding
    GIT_TAG v3.5.0
    OPTIONS
        "OPTION_BUILD_EXAMPLES OFF"
        "OPTION_BUILD_TESTS OFF"
        "OPTION_BUILD_TOOLS OFF"
)
