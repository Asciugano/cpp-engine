#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <engine/platform/OpenGL/OpenGLWindowAPI.hpp>

#include <stdexcept>

namespace Engine {

void OpenGLWindowAPI::init() {

  if (!glfwInit())
    throw std::runtime_error("Failed to initialize GLFW");

  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif
}

GLFWwindow *OpenGLWindowAPI::createWindow(const WindowConfig &config) {

  GLFWwindow *window = glfwCreateWindow(config.width, config.height,
                                        config.title, nullptr, nullptr);

  if (!window)
    throw std::runtime_error("Failed to create window");

  glfwMakeContextCurrent(window);

  return window;
}

void OpenGLWindowAPI::destroyWindow(GLFWwindow *window) {

  if (window)
    glfwDestroyWindow(window);
}

void OpenGLWindowAPI::pollEvents() { glfwPollEvents(); }

bool OpenGLWindowAPI::shouldClose(GLFWwindow *window) const {
  return glfwWindowShouldClose(window);
}

void OpenGLWindowAPI::swapBuffers(GLFWwindow *window) {
  glfwSwapBuffers(window);
}

void OpenGLWindowAPI::makeContextCurrent(GLFWwindow *window) {
  glfwMakeContextCurrent(window);
}

} // namespace Engine
