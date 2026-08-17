#pragma once

#include <engine/renderer/RendererAPI.hpp>
#include <memory>

namespace Engine {
class RenderComand {
public:
  static void init();
  static void clear();

  static void setClearColor(float r, float g, float b, float a);

  static void drawTriangle();

private:
  static std::unique_ptr<RendererAPI> s_rendererAPI;
};
} // namespace Engine
