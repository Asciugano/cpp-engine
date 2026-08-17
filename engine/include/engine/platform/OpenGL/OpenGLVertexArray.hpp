#pragma once

#include <engine/renderer/VertexArray.hpp>
#include <memory>

namespace Engine {
class OpenGLVertexArray : public VertexArray {
public:
  OpenGLVertexArray();
  ~OpenGLVertexArray() override;

  void bind() const override;
  void unbind() const override;

  void
  addVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) override;

  void setIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer) override;
  const std::shared_ptr<IndexBuffer> &getIndexBuffer() const override;

private:
  unsigned int m_rendererID = 0;
  std::shared_ptr<IndexBuffer> m_indexBuffer = {nullptr};
};
} // namespace Engine
