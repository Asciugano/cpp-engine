#include "glbinding/gl/functions.h"
#include <engine/platform/OpenGL/OpenGLShader.hpp>

#include <glbinding/gl/gl.h>

#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace Engine {

OpenGLShader::OpenGLShader(const std::string &vertexPath,
                           const std::string &fragmentPath) {
  const std::string vertexSource = readFile(vertexPath);
  const std::string fragmentSource = readFile(fragmentPath);

  m_rendererID = createProgram(vertexSource, fragmentSource);
}

OpenGLShader::~OpenGLShader() {
  if (m_rendererID != 0) {
    gl::glDeleteProgram(m_rendererID);
  }
}

void OpenGLShader::bind() const { gl::glUseProgram(m_rendererID); }

void OpenGLShader::unbind() const { gl::glUseProgram(0); }

void OpenGLShader::setInt(const std::string &name, int value) {
  const gl::GLint location = getUniformLocation(name);

  if (location == -1) {
    return;
  }

  gl::glUniform1i(location, value);
}

void OpenGLShader::setFloat(const std::string &name, float value) {
  const gl::GLint location = getUniformLocation(name);

  if (location == -1) {
    return;
  }

  gl::glUniform1f(location, value);
}

void OpenGLShader::setVec2(const std::string &name, const glm::vec2 &value) {
  const gl::GLint location = getUniformLocation(name);

  if (location == -1) {
    return;
  }

  gl::glUniform2fv(location, 1, glm::value_ptr(value));
}

void OpenGLShader::setVec3(const std::string &name, const glm::vec3 &value) {
  const gl::GLint location = getUniformLocation(name);

  if (location == -1) {
    return;
  }

  gl::glUniform3fv(location, 1, glm::value_ptr(value));
}

void OpenGLShader::setVec4(const std::string &name, const glm::vec4 &value) {
  const gl::GLint location = getUniformLocation(name);

  if (location == -1) {
    return;
  }

  gl::glUniform4fv(location, 1, glm::value_ptr(value));
}

void OpenGLShader::setMat4(const std::string &name, const glm::mat4 &value) {
  const gl::GLint location = getUniformLocation(name);

  if (location == -1) {
    return;
  }

  gl::glUniformMatrix4fv(location, 1, gl::GL_FALSE, glm::value_ptr(value));
}

gl::GLint OpenGLShader::getUniformLocation(const std::string &name) {
  const auto it = m_uniformLocations.find(name);

  if (it != m_uniformLocations.end()) {
    return it->second;
  }

  const gl::GLint location =
      gl::glGetUniformLocation(m_rendererID, name.c_str());

  if (location == -1)
    std::cerr << "Warning: uniform '" << name << "'not found in shader"
              << std::endl;

  m_uniformLocations.emplace(name, location);

  std::cout << "Locking up uniform: " << name << std::endl;

  return location;
}

std::string OpenGLShader::readFile(const std::string &path) {
  std::ifstream file(path);

  if (!file.is_open()) {
    throw std::runtime_error("Failed to open shader file: " + path);
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  if (!file)
    throw std::runtime_error("Failed to read shader file: " + path);

  return buffer.str();
}

gl::GLuint OpenGLShader::compileShader(gl::GLenum type,
                                       const std::string &source) {
  const gl::GLuint shader = gl::glCreateShader(type);

  const char *sourceCStr = source.c_str();

  gl::glShaderSource(shader, 1, &sourceCStr, nullptr);

  gl::glCompileShader(shader);

  gl::GLint compiled = 0;

  gl::glGetShaderiv(shader, gl::GL_COMPILE_STATUS, &compiled);

  if (!compiled) {
    gl::GLint length = 0;

    gl::glGetShaderiv(shader, gl::GL_INFO_LOG_LENGTH, &length);

    std::string log(static_cast<std::size_t>(length), '\0');

    gl::glGetShaderInfoLog(shader, length, nullptr, log.data());

    gl::glDeleteShader(shader);

    throw std::runtime_error("Shader compilation failed:\n" + log);
  }

  return shader;
}

gl::GLuint OpenGLShader::createProgram(const std::string &vertexSource,
                                       const std::string &fragmentSource) {
  const gl::GLuint vertexShader =
      compileShader(gl::GL_VERTEX_SHADER, vertexSource);

  const gl::GLuint fragmentShader =
      compileShader(gl::GL_FRAGMENT_SHADER, fragmentSource);

  const gl::GLuint program = gl::glCreateProgram();
  if (program == 0)
    throw std::runtime_error("Failed to create shader program");

  gl::glAttachShader(program, vertexShader);

  gl::glAttachShader(program, fragmentShader);

  gl::glLinkProgram(program);

  gl::GLint linked = 0;

  gl::glGetProgramiv(program, gl::GL_LINK_STATUS, &linked);

  if (!linked) {
    gl::GLint length = 0;

    gl::glGetProgramiv(program, gl::GL_INFO_LOG_LENGTH, &length);

    std::string log(static_cast<std::size_t>(length), '\0');

    gl::glGetProgramInfoLog(program, length, nullptr, log.data());

    gl::glDeleteProgram(program);

    gl::glDeleteShader(vertexShader);
    gl::glDeleteShader(fragmentShader);

    throw std::runtime_error("Shader linking failed:\n" + log);
  }

  gl::glDetachShader(program, vertexShader);

  gl::glDetachShader(program, fragmentShader);

  gl::glDeleteShader(vertexShader);
  gl::glDeleteShader(fragmentShader);

  return program;
}

} // namespace Engine
