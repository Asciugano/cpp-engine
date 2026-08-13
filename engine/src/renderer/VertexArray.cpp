#include <engine/renderer/VertexArray.hpp>

#include <engine/platform/OpenGL/OpenGLVertexArray.hpp>
#include <engine/renderer/RendererAPI.hpp>
#include <memory>
#include <stdexcept>

namespace Engine {
std::unique_ptr<VertexArray> VertexArray::create() {
  switch (RendererAPI::currentAPI()) {
  case GraphicsAPI::OpenGL:
    return std::make_unique<OpenGLVertexArray>();
  case GraphicsAPI::Vulkan:
    throw std::runtime_error("Vulkan not implemented");
  case GraphicsAPI::Metal:
    throw std::runtime_error("Metal not implemented");

  default:
    throw std::runtime_error("Choose a RendererAPI");
  }

  return nullptr;
}
} // namespace Engine
