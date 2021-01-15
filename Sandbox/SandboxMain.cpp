// Sandbox.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <GameEngine.h>
#include "GameEngine/Platform/WindowsConsoleWindow.h"
#include <iostream>


class MyApp : public Engine::Application
{
public:
	MyApp() : Application("MyApp")
	{
		m_Window = (Engine::WindowsConsoleWindow*)Engine::Window::Create();
		m_Window->Init();
		m_Window->SetEventCallback(EventHandler);
	}

	~MyApp()
	{
		delete m_Window;
	}

	void Run()
	{
		ENGINE_TRACE("Window handle: 0x%.8X", (long long)m_Window->GetSystemHandle());
		while (IsRunning())
			m_Window->OnUpdate();
	}

private:
	Engine::WindowsConsoleWindow* m_Window = nullptr;

	static void EventHandler(WindowEvent windowEvent)
	{
		switch (windowEvent.eventType)
		{
		case WindowEvent::EventType::WindowResized:
			ENGINE_TRACE("Resized. new size: %d,%d", windowEvent.sizeEvent.width, windowEvent.sizeEvent.height);
			break;

		case WindowEvent::EventType::WindowGainedFocus:
			ENGINE_TRACE("Gained focus");
			break;

		case WindowEvent::EventType::WindowLostFocus:
			ENGINE_TRACE("Lost focus");
			break;

		case WindowEvent::EventType::KeyPressed:
			ENGINE_TRACE("Key pressed. scan code: %d", windowEvent.keyEvent.scanCode);
			ENGINE_TRACE(
				"shift pressed: %d, ctrl pressed: %d, alt pressed: %d",
				windowEvent.keyEvent.shiftPressed,
				windowEvent.keyEvent.ctrlPressed,
				windowEvent.keyEvent.altPressed
			);
			break;

		case WindowEvent::EventType::KeyReleased:
			ENGINE_TRACE("Key released. scan code: %d", windowEvent.keyEvent.scanCode);
			break;

		case WindowEvent::EventType::MouseMoved:
			ENGINE_TRACE("Mouse moved. position: %d,%d", windowEvent.mouseMove.x, windowEvent.mouseMove.y);
			break;

		case WindowEvent::EventType::MouseButtonPressed:
			ENGINE_TRACE("Mouse pressed. button: %d", windowEvent.mouseButton.button);
			break;

		case WindowEvent::EventType::MouseButtonReleased:
			ENGINE_TRACE("Mouse released. button: %d", windowEvent.mouseButton.button);
			break;

		default:
			ENGINE_TRACE("other event");
			break;
		}
	}
};


Engine::Application* Engine::CreateApplication()
{
	return new MyApp();
}


