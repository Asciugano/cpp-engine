#include "engine/renderer/RendererAPI.hpp"
#include <engine/renderer/RenderComand.hpp>
#include <memory>

namespace Engine {

std::unique_ptr<RendererAPI> RenderComand::s_rendererAPI =
    RendererAPI::create();

void RenderComand::init() { s_rendererAPI->init(); }

void RenderComand::clear() { s_rendererAPI->clear(); }

void RenderComand::setClearColor(float r, float g, float b, float a) {
  s_rendererAPI->setClearColor(r, g, b, a);
}

void RenderComand::drawTriangle() { s_rendererAPI->drawTriangle(); }
} // namespace Engine
