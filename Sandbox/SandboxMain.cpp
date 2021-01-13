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
		switch (windowEvent.action)
		{
		case WindowEvent::Action::Resized:
			ENGINE_TRACE("Event type: RESIZED. new size: %d,%d", windowEvent.newSize[0], windowEvent.newSize[1]);
			break;

		case WindowEvent::Action::GainedFocus:
			ENGINE_TRACE("Event type: GAINEDFOCUS");
			break;

		case WindowEvent::Action::LostFocus:
			ENGINE_TRACE("Event type: LOSTFOCUS");
			break;

		default:
			ENGINE_TRACE("Event type: other");
			break;
		}
	}
};


Engine::Application* Engine::CreateApplication()
{
	return new MyApp();
}


