#include <engine/platform/OpenGL/OpenGLRendererAPI.hpp>
#include <engine/renderer/RendererAPI.hpp>
#include <memory>
#include <stdexcept>

namespace Engine {
GraphicsAPI RendererAPI::s_currentAPI = GraphicsAPI::OpenGL;

GraphicsAPI RendererAPI::currentAPI() { return s_currentAPI; }

void RendererAPI::setGraphicsAPIs(GraphicsAPI api) { s_currentAPI = api; }

std::unique_ptr<RendererAPI> RendererAPI::create() {
  switch (s_currentAPI) {

  case GraphicsAPI::OpenGL:
    return std::make_unique<OpenGLRendererAPI>();

  case GraphicsAPI::Vulkan:
    throw std::runtime_error("Vulkan backend not implemented.");

  case GraphicsAPI::Metal:
    throw std::runtime_error("Vulkan backend not implemented.");

  default:
    throw std::runtime_error("No graphics backend selected.");
  }
}
} // namespace Engine
