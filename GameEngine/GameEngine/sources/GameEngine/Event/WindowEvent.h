#pragma once

#include "Core.h"
#include "Event/EventBase.h"
#include "Math/Vector2.h"


class WindowEvent : public EventBase
{
public:
	enum class Action { None, Closed, Minimized, Resized, Moved, GainedFocus, LostFocus };

public:
	Action action = Action::None;
	Vector2 newSize;
	Vector2 newPosition;
	bool closed = false;
	bool minimized = false;
	bool hasFocus = false;

	WindowEvent() {}
	WindowEvent(const WindowEvent& other)
	{
		action = other.action;
		newSize = other.newSize;
		newPosition = other.newPosition;
		closed = other.closed;
		minimized = other.minimized;
		hasFocus = other.hasFocus;
	}

	WindowEvent& operator=(const WindowEvent& other)
	{
		action = other.action;
		newSize = other.newSize;
		newPosition = other.newPosition;
		closed = other.closed;
		minimized = other.minimized;
		hasFocus = other.hasFocus;
		return *this;
	}
};