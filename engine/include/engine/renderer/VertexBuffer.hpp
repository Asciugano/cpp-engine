#pragma once

#include "engine/renderer/BufferLayout.hpp"
#include <cstddef>
#include <memory>

namespace Engine {
class VertexBuffer {
public:
  virtual ~VertexBuffer() = default;

  virtual void bind() const = 0;
  virtual void unbind() const = 0;

  virtual void setData(const void *data, std::size_t size) = 0;

  static std::unique_ptr<VertexBuffer> create(const void *data,
                                              std::size_t size);

  virtual void setLayout(const BufferLayout &layout) = 0;

  virtual const BufferLayout &getLayout() const = 0;
};
} // namespace Engine
