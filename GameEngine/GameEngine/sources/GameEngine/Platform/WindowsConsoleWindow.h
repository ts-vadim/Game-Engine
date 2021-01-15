#pragma once

#include "Core.h"
#include "Window/Window.h"
#include "Event/WindowEvent.h"
#include "Log/Log.h"
#include <Windows.h>
#include <string>
#include <queue>


namespace Engine
{
	class ENGINE_API WindowsConsoleWindow : public Window
	{
	public:
		WindowsConsoleWindow();
		WindowsConsoleWindow(const WindowSettings& settings);
		~WindowsConsoleWindow();

		void Init() override;
		void Close() override;

		void OnUpdate() override;

		std::string GetTitle() const;
		inline uint32_t GetWidth() const override;
		inline uint32_t GetHeight() const override;

		inline void* GetSystemHandle() const override;

		void Resize(unsigned int width, unsigned int height);

		bool PollEvent(WindowEvent& event) override;

	private:
		std::queue<WindowEvent> m_WindowEventQueue;
		WindowSettings m_WindowSettings;

		HANDLE m_ConsoleScreenBuffer;
		HANDLE m_ConsoleInputHandle;
		DWORD m_SaveConsoleMode;
		INPUT_RECORD m_InputRecord;

	private:
		bool ReadConsoleInputEvent(INPUT_RECORD& inputRecord);

		void CreateWindowEvent(INPUT_RECORD& pInputRecord, WindowEvent& windowEvent);
		void CreateFocusEvent(INPUT_RECORD& pInputRecord, WindowEvent& windowEvent);
		void CreateResizeEvent(INPUT_RECORD& pInputRecord, WindowEvent& windowEvent);
		void CreateMouseEvent(INPUT_RECORD& pInputRecord, WindowEvent& windowEvent);
		void CreateKeyEvent(INPUT_RECORD& pInputRecord, WindowEvent& windowEvent);

		void UpdateWindowSettings(WindowEvent& windowEvent);
	};
}


