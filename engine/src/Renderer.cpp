#include <engine/Rendered.hpp>
#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>

namespace Engine {
void Renderer::init() { glEnable(gl::GL_DEPTH_TEST); }

void Renderer::clear() {
  gl::glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
  gl::glClear(gl::GL_COLOR_BUFFER_BIT | gl::GL_DEPTH_BUFFER_BIT);
}
} // namespace Engine
