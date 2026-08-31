#include <engine/EngineConfig.hpp>
#include <engine/platform/OpenGL/OpenGLRendererAPI.hpp>
#include <engine/renderer/RenderComand.hpp>
#include <engine/renderer/Renderer.hpp>
#include <engine/renderer/RendererAPI.hpp>
#include <glbinding/gl/gl.h>

using namespace gl;

namespace Engine {

void Renderer::init(const RendererConfig &config) {
  RendererAPI::setGraphicsAPIs(config.api);

  RenderComand::init();
}

void Renderer::beginFrame() { RenderComand::clear(); }

void Renderer::endFrame() {}

void Renderer::setClearColor(float r, float g, float b, float a) {
  RenderComand::setClearColor(r, g, b, a);
}

void Renderer::draw(const VertexArray &vertexArray, const Shader &shader) {
  RenderComand::drawIndexed(vertexArray, shader);
}
} // namespace Engine
