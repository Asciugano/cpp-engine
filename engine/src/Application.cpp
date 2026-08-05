#include <GLFW/glfw3.h>
#include <engine/Application.hpp>
#include <engine/Time.hpp>
#include <engine/Window.hpp>
#include <iostream>
#include <memory>

namespace Engine {
Application::Application() {
  glfwInit();

  m_window = std::make_unique<Window>(1280, 720, "Rally");
}

Application::Application(const char *title) {
  glfwInit();

  m_window = std::make_unique<Window>(1280, 720, title);
}

Application::Application(unsigned int width, unsigned int height,
                         const char *title) {
  glfwInit();

  m_window = std::make_unique<Window>(width, height, title);
}

Application::~Application() { glfwTerminate(); }

void Application::run() {
  while (m_running) {
    Time::update();

    if (m_window->shoudClose()) {
      m_running = false;
    }

    m_window->pollEvents();

    // INFO: UPDATE

    float dt = Time::deltaTime();
    std::cout << "FPS: " << Time::fps() << std::endl;

    // INFO: RENDER

    m_window->swapBuffers();
  }
}
} // namespace Engine
