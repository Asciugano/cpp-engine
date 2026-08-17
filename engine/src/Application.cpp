#include <engine/EngineConfig.hpp>
#include <engine/events/ApplicationEvent.hpp>
#include <engine/events/Event.hpp>
#include <engine/events/EventDispacher.hpp>
#include <engine/graphics/GraphicsContext.hpp>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <engine/Application.hpp>
#include <engine/Time.hpp>
#include <engine/Window.hpp>
#include <engine/inputs/Input.hpp>
#include <engine/inputs/KeyCodes.hpp>
#include <engine/renderer/Renderer.hpp>
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

  Input::setWindow(m_window->native());
}

Application::~Application() { glfwTerminate(); }

void Application::run() {
  bool debugMode = false;
  while (m_running) {
    Time::update();

    if (m_window->shoudClose()) {
      m_running = false;
    }

    float dt = Time::deltaTime();

    // INFO: UPDATE

    for (auto &layer : m_layerStack) {
      layer->onUpdate(dt);
    }

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

    // INFO: Events

    m_window->pollEvents();

    // INFO: Renderer
    Renderer::beginFrame();

    for (auto &layer : m_layerStack) {
      layer->onRender();
    }

    Renderer::endFrame();
    m_context->swapBuffers();
  }
}

void Application::onEvent(Event &event) {
  // DEBUG:
  // std::cout << event.name() << std::endl;

  EventDispacher dispacher(event);
  dispacher.dispatch<WindowCloseEvent>([this](WindowCloseEvent &) {
    m_running = false;

    return true;
  });

  if (event.handled)
    return;

  for (auto it = m_layerStack.end(); it != m_layerStack.begin();) {
    auto &layer = *--it;

    layer->onEvent(event);

    if (event.handled)
      break;
  }
}

void Application::pushLayer(std::shared_ptr<Layer> layer) {
  m_layerStack.pushLayer(layer);
}

void Application::pushOverlay(std::shared_ptr<Layer> overlay) {
  m_layerStack.pushOverlay(overlay);
}
} // namespace Engine
