#pragma once

#include "Core.h"
#include "Event/EventBase.h"
#include "Math/Vector2.h"


class WindowEvent : public EventBase
{
public:
	enum class Action { None, Closed, Minimized, Resized, Moved, GainedFocus, LostFocus, Unknown };

public:
	Action action = Action::None;
	unsigned int newSize[2] = { 0, 0 };
	unsigned int newPosition[2] = { 0, 0 };
	bool closed = false;
	bool minimized = false;
	bool hasFocus = false;

	WindowEvent() {}
	WindowEvent(const WindowEvent& other)
	{
		action = other.action;
		newSize[0] = other.newSize[0];
		newSize[1] = other.newSize[1];
		newPosition[0] = other.newPosition[0];
		newPosition[1] = other.newPosition[1];
		closed = other.closed;
		minimized = other.minimized;
		hasFocus = other.hasFocus;
	}

	WindowEvent& operator=(const WindowEvent& other)
	{
		action = other.action;
		newPosition[0] = other.newPosition[0];
		newPosition[1] = other.newPosition[1];
		closed = other.closed;
		minimized = other.minimized;
		hasFocus = other.hasFocus;
		return *this;
	}
};