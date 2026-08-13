#pragma once

#include <engine/renderer/VertexArray.hpp>

namespace Engine {
class OpenGLVertexArray : public VertexArray {
public:
  OpenGLVertexArray();
  ~OpenGLVertexArray() override;

  void bind() const override;
  void unbind() const override;

private:
  unsigned int m_rendererID = 0;
};
} // namespace Engine
