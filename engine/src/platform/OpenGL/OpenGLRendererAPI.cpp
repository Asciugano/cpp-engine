#include <engine/platform/OpenGL/OpenGLRendererAPI.hpp>
#include <engine/platform/OpenGL/OpenGLShader.hpp>
#include <engine/platform/OpenGL/OpenGLVertexArray.hpp>
#include <engine/platform/OpenGL/OpenGLVertexBuffer.hpp>
#include <glbinding/gl/functions.h>
#include <glbinding/gl/gl.h>
#include <memory>

using namespace gl;

namespace Engine {
void OpenGLRendererAPI::init() {

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);
}

void OpenGLRendererAPI::clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::setClearColor(float r, float g, float b, float a) {
  glClearColor(r, g, b, a);
}

void OpenGLRendererAPI::drawTriangle() {
  static bool initialized = false;

  static std::unique_ptr<VertexArray> vao;
  static std::shared_ptr<VertexBuffer> vbo;
  static std::unique_ptr<Shader> shader;

  if (!initialized) {
    float vertices[] = {0, 0.5f, 0, -0.5f, -0.5f, 0, 0.5f, -0.5f, 0};

    vao = VertexArray::create();
    vbo = std::shared_ptr<VertexBuffer>(
        VertexBuffer::create(vertices, sizeof(vertices)).release());

    vao->addVertexBuffer(vbo);

    const std::string vertexSource = R"(
            #version 330 core

            layout(location = 0) in vec3 pos;

            void main() {
                gl_Position = vec4(pos, 1.0);
            }
        )";

    const std::string fragmentSource = R"(
    #version 330 core

    out vec4 color;

    void main() {
      color = vec4(1, 0, 0, 1);
    }
    )";

    shader = Shader::create(vertexSource, fragmentSource);

    initialized = true;
  }

  vao->bind();
  shader->bind();

  gl::glDrawArrays(gl::GL_TRIANGLES, 0, 3);
}
} // namespace Engine
