#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <memory>
#include <string>

namespace Engine {
class Shader {
public:
  Shader() = default;
  Shader(const Shader &) = default;

  Shader(Shader &&) = delete;
  Shader &operator=(const Shader &) = default;
  Shader &operator=(Shader &&) = delete;

  virtual ~Shader() = default;

  virtual void bind() const = 0;
  virtual void unbind() const = 0;

  static std::unique_ptr<Shader> create(const std::string &vertexPath,
                                        const std::string &fragmentPath);

  virtual void setInt(const char *name, int value) = 0;

  virtual void setFloat(const char *name, float value) = 0;

  virtual void setVec2(const char *name, const glm::vec2 &value) = 0;

  virtual void setVec3(const char *name, const glm::vec3 &value) = 0;

  virtual void setVec4(const char *name, const glm::vec4 &value) = 0;

  virtual void setMat4(const char *name, const glm::mat4 &value) = 0;
};
} // namespace Engine
