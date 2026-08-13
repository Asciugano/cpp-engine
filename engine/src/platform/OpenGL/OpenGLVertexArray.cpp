#include "glbinding/gl/functions.h"
#include <engine/platform/OpenGL/OpenGLVertexArray.hpp>
#include <glbinding/gl/gl.h>

namespace Engine {
OpenGLVertexArray::OpenGLVertexArray() {
  gl::glGenVertexArrays(1, &m_rendererID);
}

OpenGLVertexArray::~OpenGLVertexArray() {
  gl::glDeleteVertexArrays(1, &m_rendererID);
}

void OpenGLVertexArray::bind() const { gl::glBindVertexArray(m_rendererID); }

void OpenGLVertexArray::unbind() const { gl::glBindVertexArray(0); }
} // namespace Engine
