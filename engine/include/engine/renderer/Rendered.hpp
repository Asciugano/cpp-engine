#pragma once

#include "engine/EngineConfig.hpp"
#include <memory>
namespace Engine {

class RendererAPI;

class Renderer {
public:
  static void init(const RendererConfig &config);

  static void beginFrame();
  static void endFrame();

  static void setClearColor(float r, float g, float b, float a);

private:
  static std::unique_ptr<RendererAPI> s_rendererAPI;
};

} // namespace Engine
