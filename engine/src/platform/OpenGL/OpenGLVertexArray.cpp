#include "glbinding/gl/boolean.h"
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

  const auto &layout = vertexBuffer->getLayout();

  uint32_t index = 0;

  for (const auto &element : layout) {
    gl::glEnableVertexAttribArray(index);
    gl::glVertexAttribPointer(
        index, static_cast<gl::GLint>(element.getCompenentCount()),
        gl::GL_FLOAT, element.normalized ? gl::GL_TRUE : gl::GL_FALSE,
        static_cast<gl::GLsizei>(layout.getStride()),
        reinterpret_cast<const void *>(static_cast<uintptr_t>(element.offset)));

    index++;
  }
}

void OpenGLVertexArray::setIndexBuffer(
    const std::shared_ptr<IndexBuffer> &indexBuffer) {
  bind();
  indexBuffer->bind();

  m_indexBuffer = indexBuffer;
}

const std::shared_ptr<IndexBuffer> &OpenGLVertexArray::getIndexBuffer() const {
  return m_indexBuffer;
}
} // namespace Engine
