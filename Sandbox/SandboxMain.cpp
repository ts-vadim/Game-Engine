// Sandbox.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <GameEngine.h>
#include <iostream>


class MyApp : public Engine::Application
{
public:
	MyApp() : Application("MyApp")
	{
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
			Close();
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


