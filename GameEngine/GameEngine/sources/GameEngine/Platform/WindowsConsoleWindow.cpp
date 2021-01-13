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
		Close();
	}

	void WindowsConsoleWindow::Init()
	{
		m_ConsoleScreenBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		m_ConsoleInputHandle = GetStdHandle(STD_INPUT_HANDLE);

		if (m_ConsoleScreenBuffer == INVALID_HANDLE_VALUE)
		{
			ENGINE_CORE_ERROR("Failed to create console buffer. Error: %ld", GetLastError());
			while (true);
		}

		if (m_ConsoleInputHandle == INVALID_HANDLE_VALUE)
		{
			ENGINE_CORE_ERROR("Failed to recieve input handle. Error: %ld", GetLastError());
			while (true);
		}

		if (!GetConsoleMode(m_ConsoleInputHandle, &m_SaveConsoleMode))
		{
			ENGINE_CORE_ERROR("Failed to recieve input mode. Error: %ld", GetLastError());
			while (true);
		}
		
		if (!SetConsoleMode(m_ConsoleInputHandle, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT))
		{
			ENGINE_CORE_ERROR("Failed to set console input mode. Error: %ld", GetLastError());
			while (true);
		}

		/*if (!SetConsoleActiveScreenBuffer(m_ConsoleScreenBuffer))
		{
			ENGINE_CORE_ERROR("Failed to set active console buffer. Error: %ld", GetLastError());
			while (true);
		}*/

		ENGINE_CORE_INFO("New WindowsConsoleWindow created.");
	}

	void WindowsConsoleWindow::Close()
	{
		if (!CloseHandle(m_ConsoleScreenBuffer))
			ENGINE_CORE_ERROR("Failed to close console handle. Error: %ld", GetLastError());
		if (!SetConsoleMode(m_ConsoleInputHandle, m_SaveConsoleMode))
			ENGINE_CORE_ERROR("Failed to set saved input mode. Error: %ld", GetLastError());
	}

	void WindowsConsoleWindow::OnUpdate()
	{
		DWORD unread_events_count;
		if (!GetNumberOfConsoleInputEvents(m_ConsoleInputHandle, &unread_events_count))
		{
			ENGINE_CORE_ERROR("Failed to get unread console input events. Handle: 0x%.8X, Error: %ld", (long long)m_ConsoleInputHandle, GetLastError());
			return;
		}

		if (unread_events_count > 0)
		{
			DWORD events_count;
			if (!ReadConsoleInputA(m_ConsoleInputHandle, &m_InputRecord, 1, &events_count))
			{
				ENGINE_CORE_ERROR("Failed to read console input. Error: %ld", GetLastError());
				return;
			}
			
			WindowEvent windowEvent;
			CreateWindowEvent(&m_InputRecord, windowEvent);
			if (m_EventCallback)
				m_EventCallback(windowEvent);
		}
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
		return (void*)&m_ConsoleScreenBuffer;
	}

	void WindowsConsoleWindow::Resize(unsigned int width, unsigned int height)
	{
		if (!SetConsoleScreenBufferSize(m_ConsoleScreenBuffer, { (SHORT)width, (SHORT)height }))
			ENGINE_CORE_ERROR("Failed to resize console. Handle: %d, Size: %d,%d, ErrorCode: %ld", m_ConsoleScreenBuffer, width, height, GetLastError());
	}

	void WindowsConsoleWindow::SetEventCallback(const EventCallback& callback)
	{
		m_EventCallback = callback;
	}

	void WindowsConsoleWindow::CreateWindowEvent(PINPUT_RECORD pInputRecord, WindowEvent& windowEvent)
	{
		windowEvent = WindowEvent();

		switch (pInputRecord->EventType)
		{
		case WINDOW_BUFFER_SIZE_EVENT:
			windowEvent.action = WindowEvent::Action::Resized;
			COORD sz = pInputRecord->Event.WindowBufferSizeEvent.dwSize;
			windowEvent.newSize[0] = sz.X;
			windowEvent.newSize[1] = sz.Y;
			break;

		case FOCUS_EVENT:
			if (pInputRecord->Event.FocusEvent.bSetFocus)
				windowEvent.action = WindowEvent::Action::GainedFocus;
			else
				windowEvent.action = WindowEvent::Action::LostFocus;
			break;

		default:
			windowEvent.action = WindowEvent::Action::Unknown;
			break;
		}
	}
}