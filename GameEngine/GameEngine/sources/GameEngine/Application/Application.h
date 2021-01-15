#pragma once

#include "Core.h"
#include "Log/Log.h"
#include "Window/Window.h"
#include "Event/WindowEvent.h"
#include <string>
#include <vector>
#include <memory>


namespace Engine
{
	class ENGINE_API Application
	{
	public:
		Application();
		Application(const char* name);
		virtual ~Application();

		virtual void Run();

		void Close();

		void SetName(const char* name);
		inline const char* GetName() const;

		inline bool IsRunning() const;

		virtual void OnEvent(Window* pWindow, WindowEvent& event);

	private:
		const char* m_Name = "Application";
		bool m_Running = true;
	};

	Application* CreateApplication();
}