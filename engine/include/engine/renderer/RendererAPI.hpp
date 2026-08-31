#pragma once

#include <engine/renderer/Shader.hpp>
#include <engine/renderer/VertexArray.hpp>
#include <memory>

namespace Engine {
enum class GraphicsAPI {
  None = 0,
  OpenGL,
  Vulkan,
  Metal,
};

class RendererAPI {
public:
  virtual ~RendererAPI() = default;

  virtual void init() = 0;
  virtual void clear() = 0;

  virtual void setClearColor(float r, float g, float b, float a) = 0;

  virtual void drawIndexed(const VertexArray &vertexArray,
                           const Shader &shader) = 0;

  static std::unique_ptr<RendererAPI> create();

  static GraphicsAPI currentAPI();
  static void setGraphicsAPIs(GraphicsAPI api);

private:
  static GraphicsAPI s_currentAPI;
};
} // namespace Engine
