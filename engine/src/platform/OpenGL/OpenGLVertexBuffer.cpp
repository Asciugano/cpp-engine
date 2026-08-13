#include "glbinding/gl/enum.h"
#include "glbinding/gl/functions.h"
#include "glbinding/gl/types.h"
#include <cstddef>
#include <engine/platform/OpenGL/OpenGLVertexBuffer.hpp>
#include <glbinding/gl/gl.h>

namespace Engine {
OpenGLVertexBuffer::OpenGLVertexBuffer(const void *data, std::size_t size) {
  gl::glGenBuffers(1, &m_rendererID);

  bind();

  gl::glBufferData(gl::GL_ARRAY_BUFFER, static_cast<gl::GLsizeiptr>(size), data,
                   gl::GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer() {
  gl::glDeleteBuffers(1, &m_rendererID);
}

void OpenGLVertexBuffer::bind() const {
  gl::glBindBuffer(gl::GL_ARRAY_BUFFER, m_rendererID);
}

void OpenGLVertexBuffer::unbind() const {
  gl::glBindBuffer(gl::GL_ARRAY_BUFFER, 0);
}

void OpenGLVertexBuffer::setData(const void *data, std::size_t size) {
  bind();

  gl::glBufferData(gl::GL_ARRAY_BUFFER, static_cast<gl::GLsizeiptr>(size), data,
                   gl::GL_STATIC_DRAW);
}

} // namespace Engine
