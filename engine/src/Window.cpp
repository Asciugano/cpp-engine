#include "engine/EngineConfig.hpp"
#include "engine/events/ApplicationEvent.hpp"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <engine/Window.hpp>
#include <stdexcept>

namespace Engine {
Window::Window(const WindowConfig &config)
    : m_width(config.width), m_height(config.height), m_title(config.title) {
  init();
}

void Window::init() {
  if (!glfwInit())
    throw std::runtime_error("Failed to init GLFW");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

  m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);

  if (!m_window) {
    glfwTerminate();
    throw std::runtime_error("Failed to create window");
  }

  glfwMakeContextCurrent(m_window);
  glfwSetWindowUserPointer(m_window, this);

  glfwSetFramebufferSizeCallback(
      m_window, [](GLFWwindow *window, int width, int height) {
        Window *win = static_cast<Window *>(glfwGetWindowUserPointer(window));

        win->m_width = width;
        win->m_height = height;

        WindowResizeEvent event(width, height);

        if (win->m_eventCallback)
          win->m_eventCallback(event);
      });

  glfwSetWindowCloseCallback(m_window, [](GLFWwindow *window) {
    Window *win = static_cast<Window *>(glfwGetWindowUserPointer(window));

    // TODO: creare l'evento
    WindowCloseEvent event;

    if (win->m_eventCallback)
      win->m_eventCallback(event);
  });
}

void Window::setEventCallback(const EventCallbackFn &callback) {
  m_eventCallback = callback;
}

Window::Window(unsigned int width, unsigned int height, const char *title) {
  if (!glfwInit())
    throw std::runtime_error("Failed to init GLFW");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

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
