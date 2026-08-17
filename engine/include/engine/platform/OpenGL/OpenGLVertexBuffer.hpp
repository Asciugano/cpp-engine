#pragma once

#include <engine/renderer/VertexBuffer.hpp>

namespace Engine {
class OpenGLVertexBuffer : public VertexBuffer {
public:
  OpenGLVertexBuffer(const void *data, std::size_t size);
  ~OpenGLVertexBuffer() override;

  void bind() const override;
  void unbind() const override;

  void setData(const void *data, std::size_t size) override;

  void setLayout(const BufferLayout &layout) override;
  const BufferLayout &getLayout() const override;

private:
  unsigned int m_rendererID = 0;
  BufferLayout m_layout;
};
} // namespace Engine
