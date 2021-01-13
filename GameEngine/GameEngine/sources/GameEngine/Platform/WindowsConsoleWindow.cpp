#include "WindowsConsoleWindow.h"


namespace Engine
{
	WindowsConsoleWindow::WindowsConsoleWindow()
	{
	}

	WindowsConsoleWindow::WindowsConsoleWindow(const WindowSettings& settings)
	{
		m_WindowSettings = settings;
	}

	WindowsConsoleWindow::~WindowsConsoleWindow()
	{
		if (!CloseHandle(m_ConsoleHandle))
			ENGINE_CORE_ERROR("Failed to close console handle. Error: %ld", GetLastError());
	}

	void WindowsConsoleWindow::Init()
	{
		m_ConsoleHandle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

		if (m_ConsoleHandle == INVALID_HANDLE_VALUE)
		{
			ENGINE_CORE_ERROR("Failed to create console buffer. Error: %ld", GetLastError());
			while (true);
		}
			
		if (!SetConsoleActiveScreenBuffer(m_ConsoleHandle))
		{
			ENGINE_CORE_ERROR("Failed to set active console buffer. Error: %ld", GetLastError());
			while (true);
		}

		ENGINE_CORE_INFO("New WindowsConsoleWindow created.");
	}

	void WindowsConsoleWindow::OnUpdate()
	{

	}

	std::string WindowsConsoleWindow::GetTitle() const
	{
		return m_WindowSettings.title;
	}

	uint32_t WindowsConsoleWindow::GetWidth() const
	{
		return m_WindowSettings.width;
	}

	uint32_t WindowsConsoleWindow::GetHeight() const
	{
		return m_WindowSettings.height;
	}

	void* WindowsConsoleWindow::GetSystemHandle() const
	{
		return m_ConsoleHandle;
	}

	void WindowsConsoleWindow::Resize(unsigned int width, unsigned int height)
	{
		if (!SetConsoleScreenBufferSize(m_ConsoleHandle, { (SHORT)width, (SHORT)height }))
			ENGINE_CORE_ERROR("Failed to resize console. Handle: %d, Size: %d,%d, ErrorCode: %ld", m_ConsoleHandle, width, height, GetLastError());
	}

	void WindowsConsoleWindow::SetEventCallback(const EventCallback& callback)
	{
		m_EventCallback = callback;
	}
}