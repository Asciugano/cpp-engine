#include <catch2/catch_test_macros.hpp>

#include <engine/renderer/RendererAPI.hpp>

#include <memory>
#include <stdexcept>

class RendererAPIFixture {
  Engine::GraphicsAPI prev;

public:
  RendererAPIFixture() : prev(Engine::RendererAPI::currentAPI()) {}
  ~RendererAPIFixture() { Engine::RendererAPI::setGraphicsAPIs(prev); }
};

TEST_CASE_METHOD(RendererAPIFixture, "RendererAPI selects OpenGL backend",
                 "[RendererAPI]") {
  Engine::RendererAPI::setGraphicsAPIs(Engine::GraphicsAPI::OpenGL);

  REQUIRE(Engine::RendererAPI::currentAPI() == Engine::GraphicsAPI::OpenGL);
}

TEST_CASE_METHOD(RendererAPIFixture, "RendererAPI changes graphics API",
                 "[Renderer]") {
  Engine::RendererAPI::setGraphicsAPIs(Engine::GraphicsAPI::OpenGL);

  REQUIRE(Engine::RendererAPI::currentAPI() == Engine::GraphicsAPI::OpenGL);

  Engine::RendererAPI::setGraphicsAPIs(Engine::GraphicsAPI::Vulkan);

  REQUIRE(Engine::RendererAPI::currentAPI() == Engine::GraphicsAPI::Vulkan);

  Engine::RendererAPI::setGraphicsAPIs(Engine::GraphicsAPI::Metal);

  REQUIRE(Engine::RendererAPI::currentAPI() == Engine::GraphicsAPI::Metal);
}

TEST_CASE_METHOD(RendererAPIFixture, "RendererAPI creates OpenGL backend",
                 "[RendererAPI]") {
  Engine::RendererAPI::setGraphicsAPIs(Engine::GraphicsAPI::OpenGL);

  std::unique_ptr<Engine::RendererAPI> rendererAPI;

  REQUIRE_NOTHROW(rendererAPI = Engine::RendererAPI::create());

  REQUIRE(rendererAPI != nullptr);
}

TEST_CASE_METHOD(RendererAPIFixture,
                 "RendererAPI rejects unsupported Vulkan backend",
                 "[RendererAPI]") {
  Engine::RendererAPI::setGraphicsAPIs(Engine::GraphicsAPI::Vulkan);

  REQUIRE_THROWS_AS(Engine::RendererAPI::create(), std::runtime_error);
}

TEST_CASE_METHOD(RendererAPIFixture,
                 "RendererAPI rejects unsupported Metal backend",
                 "[RendererAPI]") {
  Engine::RendererAPI::setGraphicsAPIs(Engine::GraphicsAPI::Metal);

  REQUIRE_THROWS_AS(Engine::RendererAPI::create(), std::runtime_error);
}
