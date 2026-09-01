#include <engine/renderer/IndexBuffer.hpp>
#include <engine/renderer/Mesh.hpp>
#include <engine/renderer/VertexArray.hpp>
#include <engine/renderer/VertexBuffer.hpp>
#include <memory>

namespace Engine {
std::unique_ptr<Mesh> Mesh::create(const float *vertices, uint32_t vertexSize,
                                   const uint32_t *indices, uint32_t indexCount,
                                   const BufferLayout &layout) {

  return std::unique_ptr<Mesh>(
      new Mesh(vertices, vertexSize, indices, indexCount, layout));
}

Mesh::Mesh(const float *vertices, uint32_t vertexSize, const uint32_t *indices,
           uint32_t indexCount, const BufferLayout &layout) {
  m_vao = VertexArray::create();

  m_vbo = std::shared_ptr<VertexBuffer>(
      VertexBuffer::create(vertices, vertexSize).release());

  m_vbo->setLayout(layout);

  m_vao->addVertexBuffer(m_vbo);

  m_ibo = std::shared_ptr<IndexBuffer>(
      IndexBuffer::create(indices, indexCount).release());

  m_vao->setIndexBuffer(m_ibo);
}

const VertexArray &Mesh::getVertexArray() const { return *m_vao; }
const IndexBuffer &Mesh::getIndexBuffer() const { return *m_ibo; }
const VertexBuffer &Mesh::getVertexBuffer() const { return *m_vbo; }
} // namespace Engine
