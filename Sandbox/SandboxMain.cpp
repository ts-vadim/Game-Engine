// Sandbox.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <GameEngine.h>
#include <iostream>


using namespace Engine;

class MyApp : public Application
{
public:
	MyApp()
		: Application("MyApp")
	{
		ENGINE_TRACE("App \"%s\" created", GetName());
	}

	void Run()
	{
		
		for (int i = 0; IsRunning(); i++)
		{
			if (i % 2)
				ENGINE_TRACE("running: %d", IsRunning());
			else
				ENGINE_CORE_TRACE("running: %d", IsRunning());
		}
	}

	~MyApp()
	{
	}
};


Engine::Application* Engine::CreateApplication()
{
	return new MyApp();
}


