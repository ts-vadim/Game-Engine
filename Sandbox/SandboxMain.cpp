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
		m_Window->SetActiveWindowBuffer(false);
	}

	~MyApp()
	{
		delete m_Window;
	}

	void Run()
	{
		ENGINE_TRACE("Window handle: 0x%.8X", (long long)m_Window->GetSystemHandle());
		WindowEvent event;
		while (IsRunning())
		{
			m_Window->OnUpdate();
			while (m_Window->PollEvent(event))
				OnEvent(event);
		}
	}

private:
	Engine::WindowsConsoleWindow* m_Window = nullptr;

	void OnEvent(WindowEvent windowEvent)
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
			break;

		case WindowEvent::EventType::KeyReleased:
			ENGINE_TRACE("Key released. scan code: %d", windowEvent.keyEvent.scanCode);
			if (windowEvent.keyEvent.keyCode == ' ')
			{
				bool active = !m_Window->IsWindowBufferActive();
				m_Window->SetActiveWindowBuffer(active);
				m_Window->SetTitle((active) ? "Screen buffer" : "Defult screen buffer");
				ENGINE_TRACE("Screen buffer %s", (active) ? "active" : "not active");
			}
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


