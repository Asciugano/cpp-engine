#include <engine/platform/OpenGL/OpenGLVertexArray.hpp>
#include <glbinding/gl/functions.h>
#include <glbinding/gl/gl.h>
#include <glbinding/gl/types.h>
#include <memory>

namespace Engine {
OpenGLVertexArray::OpenGLVertexArray() {
  gl::GLuint id;
  gl::glGenVertexArrays(1, &id);

  m_rendererID = id;
}

OpenGLVertexArray::~OpenGLVertexArray() {
  gl::glDeleteVertexArrays(1, &m_rendererID);
}

void OpenGLVertexArray::bind() const { gl::glBindVertexArray(m_rendererID); }

void OpenGLVertexArray::unbind() const { gl::glBindVertexArray(0); }

void OpenGLVertexArray::addVertexBuffer(
    const std::shared_ptr<VertexBuffer> &vertexBuffer) {

  bind();
  vertexBuffer->bind();

  // INFO:
  // location 0 = vec3 position

  gl::glEnableVertexAttribArray(0);
  gl::glVertexAttribPointer(0, 3, gl::GL_FLOAT, gl::GL_FALSE, 3 * sizeof(float),
                            nullptr);
}
} // namespace Engine
