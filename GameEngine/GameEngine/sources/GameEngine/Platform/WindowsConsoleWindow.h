#pragma once

#include "Core.h"
#include "Window/Window.h"
#include "Log/Log.h"
#include <Windows.h>
#include <string>


namespace Engine
{
	class ENGINE_API WindowsConsoleWindow : public Window
	{
	public:
		WindowsConsoleWindow();
		WindowsConsoleWindow(const WindowSettings& settings);
		~WindowsConsoleWindow();

		void Init() override;

		void OnUpdate() override;

		std::string GetTitle() const;
		inline uint32_t GetWidth() const override;
		inline uint32_t GetHeight() const override;

		inline void* GetSystemHandle() const override;

		void Resize(unsigned int width, unsigned int height);

		void SetEventCallback(const EventCallback& callback) override;

	private:
		EventCallback m_EventCallback;
		WindowSettings m_WindowSettings;

		HANDLE m_ConsoleHandle;
		DWORD m_ConsoleMode;
		DWORD m_SaveConsoleMode;
		INPUT_RECORD m_InputRecord;
	};
}


