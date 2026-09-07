#include <catch2/catch_test_macros.hpp>

#include <engine/EngineConfig.hpp>
#include <engine/renderer/Renderer.hpp>
#include <engine/renderer/RendererAPI.hpp>

#include <memory>
#include <stdexcept>

TEST_CASE("RendererAPI selects OpenGL backend", "[RendererAPI]") {
  Engine::RendererAPI::setGraphicsAPIs(Engine::GraphicsAPI::OpenGL);

  REQUIRE(Engine::RendererAPI::currentAPI() == Engine::GraphicsAPI::OpenGL);
}

TEST_CASE("RendererAPI changes graphics API", "[Renderer]") {
  Engine::RendererAPI::setGraphicsAPIs(Engine::GraphicsAPI::OpenGL);

  REQUIRE(Engine::RendererAPI::currentAPI() == Engine::GraphicsAPI::OpenGL);

  Engine::RendererAPI::setGraphicsAPIs(Engine::GraphicsAPI::Vulkan);

  REQUIRE(Engine::RendererAPI::currentAPI() == Engine::GraphicsAPI::Vulkan);

  Engine::RendererAPI::setGraphicsAPIs(Engine::GraphicsAPI::Metal);

  REQUIRE(Engine::RendererAPI::currentAPI() == Engine::GraphicsAPI::Metal);
}

TEST_CASE("RendererAPI creates OpenGL backend", "[RendererAPI]") {
  Engine::RendererAPI::setGraphicsAPIs(Engine::GraphicsAPI::OpenGL);

  std::unique_ptr<Engine::RendererAPI> rendererAPI;

  REQUIRE_NOTHROW(rendererAPI = Engine::RendererAPI::create());

  REQUIRE(rendererAPI != nullptr);
}

TEST_CASE("RendererAPI rejects unsupported Vulkan backend", "[RendererAPI]") {
  Engine::RendererAPI::setGraphicsAPIs(Engine::GraphicsAPI::Vulkan);

  REQUIRE_THROWS_AS(Engine::RendererAPI::create(), std::runtime_error);
}

TEST_CASE("RendererAPI rejects unsupported Metal backend", "[RendererAPI]") {
  Engine::RendererAPI::setGraphicsAPIs(Engine::GraphicsAPI::Metal);

  REQUIRE_THROWS_AS(Engine::RendererAPI::create(), std::runtime_error);
}
