#include <engine/window/WindowCommand.hpp>
#include <stdexcept>

namespace Engine {

std::unique_ptr<WindowAPI> WindowCommand::s_windowAPI = nullptr;

void WindowCommand::init(GraphicsAPI api) {

  s_windowAPI = WindowAPI::create(api);

  if (!s_windowAPI)
    throw std::runtime_error("WindowCommand: invalid GraphicsAPI");

  s_windowAPI->init();
}

GLFWwindow *WindowCommand::createWindow(const WindowConfig &config) {

  if (!s_windowAPI)
    throw std::runtime_error(
        "WindowCommand: window API has not been initialized");

  return s_windowAPI->createWindow(config);
}

void WindowCommand::destroyWindow(GLFWwindow *window) {

  if (!s_windowAPI)
    return;

  s_windowAPI->destroyWindow(window);
}

void WindowCommand::pollEvents() {

  if (!s_windowAPI)
    return;

  s_windowAPI->pollEvents();
}

bool WindowCommand::shouldClose(GLFWwindow *window) {

  if (!s_windowAPI)
    return true;

  return s_windowAPI->shouldClose(window);
}

void WindowCommand::swapBuffers(GLFWwindow *window) {

  if (!s_windowAPI)
    return;

  s_windowAPI->swapBuffers(window);
}

void WindowCommand::makeContextCurrent(GLFWwindow *window) {

  if (!s_windowAPI)
    return;

  s_windowAPI->makeContextCurrent(window);
}

} // namespace Engine
