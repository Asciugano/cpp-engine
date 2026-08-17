#pragma once

#include <engine/renderer/IndexBuffer.hpp>
#include <engine/renderer/VertexBuffer.hpp>
#include <memory>

namespace Engine {
class VertexArray {
public:
  virtual ~VertexArray() = default;

  virtual void bind() const = 0;
  virtual void unbind() const = 0;

  virtual void
  addVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) = 0;

  virtual void
  setIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer) = 0;

  virtual const std::shared_ptr<IndexBuffer> &getIndexBuffer() const = 0;

  static std::unique_ptr<VertexArray> create();
};
} // namespace Engine
