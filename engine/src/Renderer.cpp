#include <engine/Rendered.hpp>
#include <glbinding/gl/gl.h>

using namespace gl;

namespace Engine {
void Renderer::init() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);
}

void Renderer::beginFrame() { clear(); }

void Renderer::endFrame() {}

void Renderer::setClearColor(float r, float g, float b, float a) {
  glClearColor(r, g, b, a);
}

void Renderer::clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
} // namespace Engine
