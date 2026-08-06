#pragma once

#include <engine/events/EventCategory.hpp>

namespace Engine {
enum class EventType {
  None = 0,

  WindowClose,
  WindowResize,

  KeyPressed,
  KeyReleased,

  MouseMoved,
  MouseScrolled,
  MouseButtonPressed,
  MouseButtonReleased,
};

class Event {
public:
  virtual ~Event() = default;

  bool handled = false;

  virtual EventType type() const = 0;
  virtual const char *name() const = 0;
  virtual int categoryFlags() const = 0;

  bool isInCategory(EventCategory category) const {
    return categoryFlags() & category;
  }
};
} // namespace Engine
