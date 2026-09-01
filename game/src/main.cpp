#include <engine/Application.hpp>
#include <engine/EngineConfig.hpp>
#include <game/RallyLayer.hpp>
#include <memory>

int main(int argc, char *argv[]) {
  Engine::EngineConfig config;
  Engine::Application app(config);

  app.pushLayer(std::make_shared<RallyLayer>(config.window));

  app.run();

  return 0;
}
