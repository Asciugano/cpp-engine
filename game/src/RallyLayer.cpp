#include "engine/events/Event.hpp"
#include <engine/renderer/Rendered.hpp>
#include <game/RallyLayer.hpp>
#include <iostream>

RallyLayer::RallyLayer() : Layer("Rally") {}

void RallyLayer::onAttach() { std::cout << "RallyLayer Attached" << std::endl; }

void RallyLayer::onDetach() { std::cout << "RallyLayer Detached" << std::endl; }

void RallyLayer::onUpdate(float dt) { std::cout << "dt: " << dt << std::endl; }

void RallyLayer::onEvent(Engine::Event &event) {
  std::cout << event.name() << std::endl;
}

void RallyLayer::onRender() {}
