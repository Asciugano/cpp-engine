#include "engine/EngineConfig.hpp"
#include <engine/Application.hpp>

int main(int argc, char *argv[]) {
  Engine::EngineConfig config;
  Engine::Application app(config);

  app.run();

  return 0;
}
