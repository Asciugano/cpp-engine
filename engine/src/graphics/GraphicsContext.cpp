#include <engine/EngineConfig.hpp>
#include <engine/graphics/GraphicsContext.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glbinding/glbinding.h>

namespace Engine {
GraphicsContext::GraphicsContext(GLFWwindow *window) : m_window(window) {}

void GraphicsContext::init(const WindowConfig &config) {
  glfwMakeContextCurrent(m_window);

  glbinding::initialize(glfwGetProcAddress);

  glfwSwapInterval(config.vsync ? 1 : 0);
}

void GraphicsContext::swapBuffers() const { glfwSwapBuffers(m_window); }
} // namespace Engine
