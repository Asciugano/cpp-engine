#pragma once

#include <engine/renderer/IndexBuffer.hpp>

namespace Engine {
class OpenGLIndexBuffer : public IndexBuffer {
public:
  OpenGLIndexBuffer(const uint32_t *indices, uint32_t count);
  ~OpenGLIndexBuffer() override;

  void bind() const override;
  void unbind() const override;

  uint32_t getCount() const override;

private:
  unsigned int m_rendererID = 0;
  uint32_t m_count = 0;
};
} // namespace Engine
