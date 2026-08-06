#pragma once

#include <engine/events/Event.hpp>

namespace Engine {

class EventDispacher {
public:
  EventDispacher(Event &event) : m_event(event) {}

  template <typename T, typename F> bool dispatch(const F &func) {
    if (m_event.type() == T::staticType()) {
      m_event.handled = func(static_cast<T &>(m_event));
      return true;
    }

    return false;
  }

private:
  Event &m_event;
};
} // namespace Engine
