#pragma once

#include <cstdint>

#include <engine/renderer/RendererAPI.hpp>

namespace Engine {
struct WindowConfig {
  const char *title = "Rally";
  uint32_t width = 1280;
  uint32_t height = 720;

  bool fullscreen = false;
  bool resizable = true;
  bool vsinc = true;
};

struct RendererConfig {
  GraphicsAPI api = GraphicsAPI::OpenGL;

  bool enableDepthTest = true;
  bool enableDebug = true;
};

struct EngineConfig {
  WindowConfig window;
  RendererConfig renderer;
};
} // namespace Engine
