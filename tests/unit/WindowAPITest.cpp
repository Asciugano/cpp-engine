#include <catch2/catch_test_macros.hpp>

#include <engine/EngineConfig.hpp>
#include <engine/window/WindowAPI.hpp>

#include <memory>
#include <stdexcept>

TEST_CASE("WindowAPI creates OpenGL backend", "[WindowAPI]") {
  std::unique_ptr<Engine::WindowAPI> api;
  REQUIRE_NOTHROW(api = Engine::WindowAPI::create(Engine::GraphicsAPI::OpenGL));

  REQUIRE(api != nullptr);
}

TEST_CASE("WindowAPI creates Vulkan backend", "[WindowAPI]") {
  REQUIRE_THROWS_AS(Engine::WindowAPI::create(Engine::GraphicsAPI::Vulkan),
                    std::runtime_error);
}

TEST_CASE("WindowAPI rejects unsupported backend", "[WindowAPI]") {
  REQUIRE_THROWS_AS(Engine::WindowAPI::create(Engine::GraphicsAPI::None),
                    std::runtime_error);
}
