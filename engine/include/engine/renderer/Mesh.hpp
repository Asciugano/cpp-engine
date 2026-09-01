#pragma once

#include "engine/renderer/IndexBuffer.hpp"
#include <engine/renderer/BufferLayout.hpp>
#include <engine/renderer/VertexArray.hpp>
#include <memory>

namespace Engine {
class Mesh {
public:
  Mesh(const Mesh &) = delete;
  Mesh(Mesh &&) = delete;

  Mesh &operator=(const Mesh &) = delete;
  Mesh &operator=(Mesh &&) = delete;

  ~Mesh() = default;

  static std::unique_ptr<Mesh>
  create(const float *vertices, uint32_t vertexSize, const uint32_t *indices,
         uint32_t indexCount, const BufferLayout &layout);

  const VertexArray &getVertexArray() const;
  const IndexBuffer &getIndexBuffer() const;
  const VertexBuffer &getVertexBuffer() const;

private:
  Mesh(const float *vertices, uint32_t vertexSize, const uint32_t *indices,
       uint32_t indexCount, const BufferLayout &layout);

private:
  std::unique_ptr<VertexArray> m_vao;
  std::shared_ptr<VertexBuffer> m_vbo;
  std::shared_ptr<IndexBuffer> m_ibo;
};
} // namespace Engine
