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
			ENGINE_TRACE(
				"Time now: %02d-%02d-%04d %02d:%02d:%02d.%04d",
				Engine::Date::Day(),
				Engine::Date::Month(),
				Engine::Date::Year(),
				Engine::Time::Actual::Hours(),
				Engine::Time::Actual::Minutes(),
				Engine::Time::Actual::Seconds(),
				Engine::Time::Actual::Milliseconds()
			);
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


