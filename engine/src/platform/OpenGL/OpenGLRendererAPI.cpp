#include <engine/platform/OpenGL/OpenGLRendererAPI.hpp>
#include <engine/platform/OpenGL/OpenGLShader.hpp>
#include <engine/platform/OpenGL/OpenGLVertexArray.hpp>
#include <engine/platform/OpenGL/OpenGLVertexBuffer.hpp>
#include <engine/renderer/IndexBuffer.hpp>
#include <engine/renderer/Shader.hpp>
#include <engine/renderer/ShaderDataType.hpp>
#include <glbinding/gl/enum.h>
#include <glbinding/gl/functions.h>
#include <glbinding/gl/gl.h>
#include <glbinding/gl/types.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
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

// void OpenGLRendererAPI::drawTriangle() {
//   static bool initialized = false;
//
//   static std::unique_ptr<VertexArray> vao;
//   static std::shared_ptr<VertexBuffer> vbo;
//   static std::shared_ptr<IndexBuffer> ibo;
//   static std::unique_ptr<Shader> shader;
//
//   if (!initialized) {
//     float vertices[] = {0.0f, 0.5f, 0.0f,  -0.5f, -0.5f,
//                         0.0f, 0.5f, -0.5f, 0.0f};
//
//     uint32_t indices[] = {0, 1, 2};
//
//     vao = VertexArray::create();
//
//     vbo = std::shared_ptr<VertexBuffer>(
//         VertexBuffer::create(vertices, sizeof(vertices)).release());
//
//     vbo->setLayout({{ShaderDataType::Float3, "pos"}});
//
//     vao->addVertexBuffer(vbo);
//
//     ibo =
//         std::shared_ptr<IndexBuffer>(IndexBuffer::create(indices,
//         3).release());
//
//     vao->setIndexBuffer(ibo);
//
//     shader = Shader::create("assets/shaders/basic.vert",
//                             "assets/shaders/basic.frag");
//
//     shader->bind();
//
//     shader->setVec4("u_Color", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
//
//     glm::mat4 model = glm::mat4(1.0f);
//
//     glm::mat4 view =
//         glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), // posizione camera
//                     glm::vec3(0.0f, 0.0f, 0.0f), // punto osservato
//                     glm::vec3(0.0f, 1.0f, 0.0f)  // up
//         );
//
//     glm::mat4 projection = glm::perspective(glm::radians(45.0f), // FOV
//                                             1280.0f / 720.0f,    // aspect
//                                             ratio 0.1f,                //
//                                             near 100.0f               // far
//     );
//
//     shader->setMat4("u_Model", model);
//
//     shader->setMat4("u_View", view);
//
//     shader->setMat4("u_Projection", projection);
//
//     initialized = true;
//   }
//
//   vao->bind();
//   shader->bind();
//
//   gl::glDrawElements(
//       gl::GL_TRIANGLES,
//       static_cast<gl::GLsizei>(vao->getIndexBuffer()->getCount()),
//       gl::GL_UNSIGNED_INT, nullptr);
// }
void OpenGLRendererAPI::drawIndexed(const VertexArray &vertexArray,
                                    const Shader &shader) {
  vertexArray.bind();
  shader.bind();

  const auto &indexBuffer = vertexArray.getIndexBuffer();

  gl::glDrawElements(gl::GL_TRIANGLES,
                     static_cast<gl::GLsizei>(indexBuffer->getCount()),
                     gl::GL_UNSIGNED_INT, nullptr);
}
} // namespace Engine
