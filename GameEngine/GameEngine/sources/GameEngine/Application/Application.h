#pragma once

#include "Core.h"
#include "Window/Window.h"
#include <string>


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

	private:
		const char* m_Name = "Application";
		bool m_Running = true;

	};

	Application* CreateApplication();
}