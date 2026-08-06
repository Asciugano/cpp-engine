#include <engine/graphics/GraphicsContext.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glbinding/glbinding.h>

namespace Engine {
GraphicsContext::GraphicsContext(GLFWwindow *window) : m_window(window) {}

void GraphicsContext::init() {
  glfwMakeContextCurrent(m_window);

  glbinding::initialize(glfwGetProcAddress);

  glfwSwapInterval(1); // INFO: VSync
}

void GraphicsContext::swapBuffers() const { glfwSwapBuffers(m_window); }
} // namespace Engine
