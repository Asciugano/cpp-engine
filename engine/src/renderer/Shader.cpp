#include <engine/platform/OpenGL/OpenGLShader.hpp>
#include <engine/renderer/RendererAPI.hpp>
#include <engine/renderer/Shader.hpp>
#include <fstream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

namespace Engine {

static std::string readFile(const std::string &path) {
  std::ifstream file(path);

  if (!file.is_open()) {
    throw std::runtime_error("Failed to open shader file: " + path);
  }

  std::stringstream buffer;
  buffer << file.rdbuf();

  return buffer.str();
}

std::unique_ptr<Shader> Shader::create(const std::string &vertexPath,
                                       const std::string &fragmentPath) {

  const std::string &vertexSource = readFile(vertexPath);
  const std::string &fragmentSource = readFile(fragmentPath);

  switch (RendererAPI::currentAPI()) {
  case GraphicsAPI::OpenGL:
    return std::make_unique<OpenGLShader>(vertexSource, fragmentSource);

  case GraphicsAPI::Vulkan:
    throw std::runtime_error("Vulkan not implemented");
  case GraphicsAPI::Metal:
    throw std::runtime_error("Metal not implemented");

  default:
    throw std::runtime_error("You must choose a GraphicsAPI");
  }
}
} // namespace Engine
