#include <engine/platform/OpenGL/OpenGLRendererAPI.hpp>
#include <engine/renderer/Rendered.hpp>
#include <engine/renderer/RendererAPI.hpp>
#include <glbinding/gl/gl.h>
#include <memory>

using namespace gl;

namespace Engine {
std::unique_ptr<RendererAPI> Renderer::s_rendererAPI = nullptr;

void Renderer::init() {
  s_rendererAPI = std::make_unique<OpenGLRendererAPI>();

  s_rendererAPI->init();
}

void Renderer::beginFrame() { s_rendererAPI->clear(); }

void Renderer::endFrame() {}

void Renderer::setClearColor(float r, float g, float b, float a) {
  s_rendererAPI->setClearColor(r, g, b, a);
}
} // namespace Engine
