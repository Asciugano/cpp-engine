#pragma once

#include <engine/EngineConfig.hpp>

namespace Engine {

class RendererAPI;

class Renderer {
public:
  static void init(const RendererConfig &config);

  static void beginFrame();
  static void endFrame();

  static void setClearColor(float r, float g, float b, float a);

  static void draw(const VertexArray &vertexArray, const Shader &shader);

  static void setViewport(uint32_t x, uint32_t y, uint32_t width,
                          uint32_t height);
};

} // namespace Engine
