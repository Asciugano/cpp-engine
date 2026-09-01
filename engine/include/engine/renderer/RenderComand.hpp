#pragma once

#include <engine/renderer/RendererAPI.hpp>
#include <memory>

namespace Engine {
class RenderComand {
public:
  static void init();
  static void clear();

  static void setClearColor(float r, float g, float b, float a);

  static void drawIndexed(const VertexArray &vertexArray, const Shader &shader);

  static void setViewport(uint32_t x, uint32_t y, uint32_t width,
                          uint32_t height);

private:
  static std::unique_ptr<RendererAPI> s_rendererAPI;
};
} // namespace Engine
