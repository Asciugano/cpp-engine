#pragma once

#include <cstdint>
#include <engine/renderer/ShaderDataType.hpp>
#include <string>

namespace Engine {
struct BufferElement {
  std::string name;
  ShaderDataType type;
  uint32_t size;
  uint32_t offset;
  bool normalized;

  BufferElement(ShaderDataType type, const std::string &name,
                bool normalized = false)
      : name(name), type(type), size(shaderDataTypeSize(type)), offset(0),
        normalized(normalized) {}

  uint32_t getCompenentCount() const {
    return shaderDataTypeComponentCount(type);
  }
};
} // namespace Engine
