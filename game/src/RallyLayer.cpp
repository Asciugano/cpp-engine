#include <engine/renderer/Rendered.hpp>
#include <game/RallyLayer.hpp>

RallyLayer::RallyLayer() : Layer("Rally") {}

void RallyLayer::onAttach() {}

void RallyLayer::onUpdate(float dt) { m_rotation += dt; }

void RallyLayer::onRender() {}
