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
		ENGINE_CORE_WARN("Application::Run() not implemented. Application runs empty mainloop.");
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

	void Application::OnEvent(Window* pWindow, WindowEvent& event)
	{
	}
}

