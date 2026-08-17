#pragma once

#include <memory>
#include <string>
namespace Engine {
class Shader {
public:
  virtual ~Shader() = default;

  virtual void bind() const = 0;
  virtual void unbind() const = 0;

  static std::unique_ptr<Shader> create(const std::string &vertexPath,
                                        const std::string &fragmentPath);
};
} // namespace Engine
