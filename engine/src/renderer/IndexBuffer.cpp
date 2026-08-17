#include <engine/platform/OpenGL/OpenGLIndexBuffer.hpp>
#include <engine/renderer/IndexBuffer.hpp>
#include <engine/renderer/RendererAPI.hpp>
#include <memory>
#include <stdexcept>

namespace Engine {
std::unique_ptr<IndexBuffer> IndexBuffer::create(const uint32_t *indices,
                                                 uint32_t count) {
  switch (RendererAPI::currentAPI()) {
  case GraphicsAPI::OpenGL:
    return std::make_unique<OpenGLIndexBuffer>(indices, count);
  case GraphicsAPI::Vulkan:
    throw std::runtime_error("Vulkan not implemented");
  case GraphicsAPI::Metal:
    throw std::runtime_error("Metal not implemented");

  default:
    throw std::runtime_error("You must choose a RendererAPI");
  }
}
} // namespace Engine
