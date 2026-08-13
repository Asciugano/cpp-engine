#include <engine/platform/OpenGL/OpenGLVertexBuffer.hpp>
#include <engine/renderer/RendererAPI.hpp>
#include <engine/renderer/VertexBuffer.hpp>
#include <stdexcept>

namespace Engine {
std::unique_ptr<VertexBuffer> VertexBuffer::create(const void *data,
                                                   std::size_t size) {
  switch (RendererAPI::currentAPI()) {
  case Engine::GraphicsAPI::OpenGL:
    return std::make_unique<OpenGLVertexBuffer>(data, size);

  case Engine::GraphicsAPI::Metal:
    throw std::runtime_error("Metal not implemented");

  case Engine::GraphicsAPI::Vulkan:
    throw std::runtime_error("Metal not implemented");

  default:
    throw std::runtime_error("Choose a RendererAPI");
  }

  return nullptr;
}
} // namespace Engine
