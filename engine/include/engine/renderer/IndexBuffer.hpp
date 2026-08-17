#pragma once

#include <cstdint>
#include <memory>

namespace Engine {
class IndexBuffer {
public:
  virtual ~IndexBuffer() = default;

  virtual void bind() const = 0;
  virtual void unbind() const = 0;

  virtual uint32_t getCount() const = 0;

  static std::unique_ptr<IndexBuffer> create(const uint32_t *indices,
                                             uint32_t count);
};
} // namespace Engine
