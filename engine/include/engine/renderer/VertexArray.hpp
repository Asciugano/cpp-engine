#pragma once

#include <memory>

namespace Engine {
class VertexArray {
public:
  virtual ~VertexArray() = default;

  virtual void bind() const = 0;
  virtual void unbind() const = 0;

  static std::unique_ptr<VertexArray> create();
};
} // namespace Engine
