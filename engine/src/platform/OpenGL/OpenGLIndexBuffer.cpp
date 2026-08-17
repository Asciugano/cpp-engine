#include "glbinding/gl/enum.h"
#include "glbinding/gl/functions.h"
#include "glbinding/gl/types.h"
#include <engine/platform/OpenGL/OpenGLIndexBuffer.hpp>
#include <glbinding/gl/gl.h>

namespace Engine {
OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t *indices, uint32_t count)
    : m_count(count) {

  gl::GLuint id;
  gl::glGenBuffers(1, &id);

  m_rendererID = id;

  bind();

  gl::glBufferData(gl::GL_ELEMENT_ARRAY_BUFFER,
                   static_cast<gl::GLsizeiptr>(count * sizeof(uint32_t)),
                   indices, gl::GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer() {
  gl::glDeleteBuffers(1, &m_rendererID);
}

void OpenGLIndexBuffer::bind() const {
  gl::glBindBuffer(gl::GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
}

void OpenGLIndexBuffer::unbind() const {
  gl::glBindBuffer(gl::GL_ELEMENT_ARRAY_BUFFER, 0);
}

uint32_t OpenGLIndexBuffer::getCount() const { return m_count; }
} // namespace Engine
