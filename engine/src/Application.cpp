#include "engine/Key.hpp"
#include <GLFW/glfw3.h>
#include <engine/Application.hpp>
#include <engine/Input.hpp>
#include <engine/Time.hpp>
#include <engine/Window.hpp>
#include <iostream>
#include <memory>

namespace Engine {
Application::Application() {
  glfwInit();

  m_window = std::make_unique<Window>(1280, 720, "Rally");
  Input::init(m_window->native());
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
  bool debugMode = false;
  while (m_running) {
    Time::update();

    if (m_window->shoudClose()) {
      m_running = false;
    }

    m_window->pollEvents();

    // INFO: UPDATE

    float dt = Time::deltaTime();

    if (Input::isKeyPressed(Key::Up)) {
      debugMode = !debugMode;
    }
    if (debugMode) {
      std::cout << "FPS: " << Time::fps() << std::endl;
    }
    if (Input::isKeyPressed(Key::W)) {
      std::cout << "W" << std::endl;
    }

    if (Input::isKeyPressed(Key::Escape)) {
      m_running = false;
    }

    // INFO: RENDER

    m_window->swapBuffers();
  }
}
} // namespace Engine
