#pragma once

#include <memory>
namespace Engine {

class RendererAPI;

class Renderer {
public:
  static void init();

  static void beginFrame();
  static void endFrame();

  static void setClearColor(float r, float g, float b, float a);

private:
  static std::unique_ptr<RendererAPI> s_rendererAPI;
};

} // namespace Engine
