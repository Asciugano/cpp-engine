#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <engine/Window.hpp>
#include <stdexcept>

namespace Engine {
Window::Window(unsigned int width, unsigned int height, const char *title) {
  if (!glfwInit())
    throw std::runtime_error("Failed to init GLFW");

  m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);

  if (!m_window) {
    glfwTerminate();
    throw std::runtime_error("Failed to create window");
  }

  glfwMakeContextCurrent(m_window);
}

Window::~Window() { glfwDestroyWindow(m_window); }

bool Window::shoudClose() const { return glfwWindowShouldClose(m_window); }

void Window::pollEvents() const { glfwPollEvents(); }

void Window::swapBuffers() const { glfwSwapBuffers(m_window); }

GLFWwindow *Window::native() const { return m_window; }
} // namespace Engine
