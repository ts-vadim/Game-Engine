// Sandbox.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <GameEngine.h>
#include <iostream>


class MyApp : public Engine::Application
{
public:
	MyApp() : Application("MyApp")
	{
		m_Window = Engine::Window::Create();
		m_Window->Init();
	}

	~MyApp()
	{
		delete m_Window;
	}

	void Run()
	{
		ENGINE_TRACE("Window handle: 0x%.8X", (long long)m_Window->GetSystemHandle());
		Close();
	}

private:
	Engine::Window* m_Window = nullptr;
};


Engine::Application* Engine::CreateApplication()
{
	return new MyApp();
}


