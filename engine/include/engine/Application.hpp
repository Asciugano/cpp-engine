#pragma once

#include "engine/layer/LayerStack.hpp"
#include <engine/EngineConfig.hpp>
#include <engine/events/Event.hpp>
#include <engine/layer/Layer.hpp>
#include <memory>

namespace Engine {
class Window;
class GraphicsContext;

class Application {
public:
  explicit Application(const EngineConfig &config);
  ~Application();

  void run();

  void onEvent(Event &event);

  void pushLayer(std::shared_ptr<Layer> layer);

  Window &window() { return *m_window; }

private:
  std::unique_ptr<Window> m_window;
  std::unique_ptr<GraphicsContext> m_context;
  bool m_running{true};
  EngineConfig m_config;
  LayerStack m_layerStack;
};
} // namespace Engine
