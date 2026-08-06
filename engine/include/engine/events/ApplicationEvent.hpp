#pragma once

#include "engine/events/Event.hpp"
#include "engine/events/EventCategory.hpp"

namespace Engine {

class WindowResizeEvent : public Event {
public:
  WindowResizeEvent(int width, int height)
      : m_width(width), m_height(height) {};

  int width() const { return m_width; }

  int height() const { return m_height; }

  static EventType staticType() { return EventType::WindowResize; }
  EventType type() const override { return EventType::WindowResize; }

  const char *name() const override { return "WindowResize"; }

  int categoryFlags() const override { return EventCategoryApplication; }

private:
  int m_width;
  int m_height;
};

class WindowCloseEvent : public Event {
public:
  static EventType staticType() { return EventType::WindowClose; }

  EventType type() const override { return EventType::WindowClose; }

  const char *name() const override { return "WindowClose"; }

  int categoryFlags() const override { return EventCategoryApplication; }
};

} // namespace Engine
