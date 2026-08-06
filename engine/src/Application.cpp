#include "engine/EngineConfig.hpp"
#include "engine/events/ApplicationEvent.hpp"
#include "engine/events/Event.hpp"
#include "engine/events/EventDispacher.hpp"
#include <engine/Key.hpp>
#include <engine/graphics/GraphicsContext.hpp>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <engine/Application.hpp>
#include <engine/Input.hpp>
#include <engine/Time.hpp>
#include <engine/Window.hpp>
#include <engine/renderer/Rendered.hpp>
#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>
#include <iostream>
#include <memory>

namespace Engine {
Application::Application(const EngineConfig &config) : m_config(config) {
  glfwInit();

  m_window = std::make_unique<Window>(config.window);
  m_window->setEventCallback([this](Event &event) { onEvent(event); });

  m_context = std::make_unique<GraphicsContext>(m_window->native());

  m_context->init();

  Renderer::init(config.renderer);
  Renderer::setClearColor(0.15f, 0.18f, 0.22f, 1);

  Input::init(m_window->native());
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
    Renderer::beginFrame();

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

    Renderer::endFrame();
    m_context->swapBuffers();
  }
}

void Application::onEvent(Event &event) {
  EventDispacher dispacher(event);
  dispacher.dispatch<WindowCloseEvent>([this](WindowCloseEvent &) {
    m_running = false;

    return true;
  });
}
} // namespace Engine
