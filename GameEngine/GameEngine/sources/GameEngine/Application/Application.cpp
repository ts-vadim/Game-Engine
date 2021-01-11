#include "Application.h"


namespace Engine
{
	Application::Application()
	{
	}

	Application::Application(const char* name)
	{
		SetName(name);
	}

	Application::~Application()
	{
		Close();
	}

	void Application::Run()
	{
		while (m_Running);
	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::SetName(const char* name)
	{
		m_Name = name;
	}

	const char* Application::GetName() const
	{
		return m_Name;
	}

	bool Application::IsRunning() const
	{
		return m_Running;
	}
}

