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
};
} // namespace Engine
