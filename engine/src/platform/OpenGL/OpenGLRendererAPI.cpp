#include "glbinding/gl/functions.h"
#include <engine/platform/OpenGL/OpenGLRendererAPI.hpp>
#include <glbinding/gl/gl.h>

using namespace gl;

namespace Engine {
void OpenGLRendererAPI::init() {

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);
}

void OpenGLRendererAPI::clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::setClearColor(float r, float g, float b, float a) {
  glClearColor(r, g, b, a);
}
} // namespace Engine
