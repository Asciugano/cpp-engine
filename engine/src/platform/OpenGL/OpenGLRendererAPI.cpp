#include <engine/platform/OpenGL/OpenGLRendererAPI.hpp>
#include <engine/platform/OpenGL/OpenGLShader.hpp>
#include <engine/platform/OpenGL/OpenGLVertexArray.hpp>
#include <engine/platform/OpenGL/OpenGLVertexBuffer.hpp>
#include <engine/renderer/IndexBuffer.hpp>
#include <engine/renderer/Shader.hpp>
#include <engine/renderer/ShaderDataType.hpp>
#include <glbinding/gl/enum.h>
#include <glbinding/gl/functions.h>
#include <glbinding/gl/gl.h>
#include <glbinding/gl/types.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <memory>

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

void OpenGLRendererAPI::drawIndexed(const VertexArray &vertexArray,
                                    const Shader &shader) {
  vertexArray.bind();
  shader.bind();

  const auto &indexBuffer = vertexArray.getIndexBuffer();

  gl::glDrawElements(gl::GL_TRIANGLES,
                     static_cast<gl::GLsizei>(indexBuffer->getCount()),
                     gl::GL_UNSIGNED_INT, nullptr);
}

void OpenGLRendererAPI::setViewport(uint32_t x, uint32_t y, uint32_t width,
                                    uint32_t height) {
  gl::glViewport(x, y, width, height);
}
} // namespace Engine
