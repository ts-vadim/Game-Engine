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
	}
};


Engine::Application* Engine::CreateApplication()
{
	return new MyApp();
}


