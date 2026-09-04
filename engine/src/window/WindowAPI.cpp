#include <engine/platform/OpenGL/OpenGLWindowAPI.hpp>
#include <engine/window/WindowAPI.hpp>
#include <stdexcept>

namespace Engine {

std::unique_ptr<WindowAPI> WindowAPI::create(GraphicsAPI api) {

  switch (api) {

  case GraphicsAPI::OpenGL:
    return std::make_unique<OpenGLWindowAPI>();

  case GraphicsAPI::Vulkan:
    throw std::runtime_error(
        "WindowAPI: Vulkan window backend not implemented");

  case GraphicsAPI::Metal:
    throw std::runtime_error("WindowAPI: Metal window backend not implemented");

  case GraphicsAPI::None:
    throw std::runtime_error("WindowAPI: GraphicsAPI::None is not supported");

  default:
    throw std::runtime_error("WindowAPI: unknown GraphicsAPI");
  }
}

} // namespace Engine
