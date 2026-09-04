#include "GraphicsAPI.hpp"
#include <engine/events/ApplicationEvent.hpp>
#include <engine/window/Window.hpp>
#include <engine/window/WindowCommand.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Engine {

Window::Window(const WindowConfig &config)
    : m_width(config.width), m_height(config.height), m_title(config.title) {

  WindowCommand::init(config.api);

  m_window = WindowCommand::createWindow(config);

  glfwSetWindowUserPointer(m_window, this);

  glfwSetFramebufferSizeCallback(
      m_window, [](GLFWwindow *window, int width, int height) {
        auto *win = static_cast<Window *>(glfwGetWindowUserPointer(window));

        win->m_width = width;
        win->m_height = height;

        WindowResizeEvent event(width, height);

        if (win->m_eventCallback)
          win->m_eventCallback(event);
      });

  glfwSetWindowCloseCallback(m_window, [](GLFWwindow *window) {
    auto *win = static_cast<Window *>(glfwGetWindowUserPointer(window));

    WindowCloseEvent event;

    if (win->m_eventCallback)
      win->m_eventCallback(event);
  });
}

Window::~Window() { WindowCommand::destroyWindow(m_window); }

void Window::setEventCallback(const EventCallbackFn &callback) {
  m_eventCallback = callback;
}

bool Window::shouldClose() const {
  return WindowCommand::shouldClose(m_window);
}

void Window::pollEvents() const { WindowCommand::pollEvents(); }

void Window::swapBuffers() const { WindowCommand::swapBuffers(m_window); }

GLFWwindow *Window::native() const { return m_window; }

uint32_t Window::width() const { return m_width; }
uint32_t Window::height() const { return m_height; }
} // namespace Engine
