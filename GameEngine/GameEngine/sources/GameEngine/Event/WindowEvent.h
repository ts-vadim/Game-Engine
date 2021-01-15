#pragma once

#include "Core.h"


class ENGINE_API WindowEvent
{
public:
	enum class EventType
	{
		Unknown,
		WindowClosed, WindowResized, WindowGainedFocus, WindowLostFocus,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved
	};

	struct SizeEvent
	{
		unsigned int width;
		unsigned int height;
	};

	struct KeyEvent
	{
		int keyCode;
		int scanCode;
		bool capslockPressed;
		bool altPressed;
		bool ctrlPressed;
		bool shiftPressed;
	};

	struct MouseButtonEvent
	{
		int button;
	};

	struct MouseMoveEvent
	{
		int x;
		int y;
	};

public:
	EventType eventType;

	union
	{
		SizeEvent sizeEvent;
		KeyEvent keyEvent;
		MouseButtonEvent mouseButton;
		MouseMoveEvent mouseMove;
	};
};