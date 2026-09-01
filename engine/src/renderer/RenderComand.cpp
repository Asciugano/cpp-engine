#include <engine/renderer/RenderComand.hpp>
#include <engine/renderer/RendererAPI.hpp>
#include <memory>

namespace Engine {

std::unique_ptr<RendererAPI> RenderComand::s_rendererAPI =
    RendererAPI::create();

void RenderComand::init() { s_rendererAPI->init(); }

void RenderComand::clear() { s_rendererAPI->clear(); }

void RenderComand::setClearColor(float r, float g, float b, float a) {
  s_rendererAPI->setClearColor(r, g, b, a);
}

void RenderComand::drawIndexed(const VertexArray &vertexArray,
                               const Shader &shader) {
  s_rendererAPI->drawIndexed(vertexArray, shader);
}

void RenderComand::setViewport(uint32_t x, uint32_t y, uint32_t width,
                               uint32_t height) {
  s_rendererAPI->setViewport(x, y, width, height);
}
} // namespace Engine
