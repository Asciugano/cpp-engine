#include <engine/platform/OpenGL/OpenGLShader.hpp>
#include <engine/renderer/RendererAPI.hpp>
#include <engine/renderer/Shader.hpp>

#include <memory>
#include <stdexcept>
#include <string>

namespace Engine {

std::unique_ptr<Shader> Shader::create(const std::string &vertexPath,
                                       const std::string &fragmentPath) {
  switch (RendererAPI::currentAPI()) {
  case GraphicsAPI::OpenGL:
    return std::make_unique<OpenGLShader>(vertexPath, fragmentPath);

  case GraphicsAPI::Vulkan:
    throw std::runtime_error("Vulkan not implemented");

  case GraphicsAPI::Metal:
    throw std::runtime_error("Metal not implemented");

  default:
    throw std::runtime_error("You must choose a GraphicsAPI");
  }
}

} // namespace Engine
