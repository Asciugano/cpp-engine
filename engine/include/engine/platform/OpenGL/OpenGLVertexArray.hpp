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

private:
  unsigned int m_rendererID = 0;
};
} // namespace Engine
