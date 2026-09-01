#pragma once

#include <engine/renderer/RendererAPI.hpp>

namespace Engine {
class OpenGLRendererAPI : public RendererAPI {
public:
  void init() override;

  void clear() override;

  void setClearColor(float r, float g, float b, float a) override;

  void drawIndexed(const VertexArray &vertexArray,
                   const Shader &shader) override;

  void setViewport(uint32_t x, uint32_t y, uint32_t width,
                   uint32_t height) override;
};
} // namespace Engine
