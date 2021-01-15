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
			CreateWindowEvent(m_InputRecord, windowEvent);
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

	void WindowsConsoleWindow::CreateWindowEvent(INPUT_RECORD& inputRecord, WindowEvent& windowEvent)
	{
		switch (inputRecord.EventType)
		{
		case WINDOW_BUFFER_SIZE_EVENT:
			CreateResizeEvent(inputRecord, windowEvent);
			break;

		case FOCUS_EVENT:
			CreateFocusEvent(inputRecord, windowEvent);
			break;
			
		case KEY_EVENT:
			CreateKeyEvent(inputRecord, windowEvent);
			break;

		case MOUSE_EVENT:
			CreateMouseEvent(inputRecord, windowEvent);
			break;

		default:
			windowEvent.eventType = WindowEvent::EventType::Unknown;
			break;
		}

		
	}

	void WindowsConsoleWindow::CreateFocusEvent(INPUT_RECORD& inputRecord, WindowEvent& windowEvent)
	{
		if (inputRecord.Event.FocusEvent.bSetFocus)
			windowEvent.eventType = WindowEvent::EventType::WindowGainedFocus;
		else
			windowEvent.eventType = WindowEvent::EventType::WindowLostFocus;
	}

	void WindowsConsoleWindow::CreateResizeEvent(INPUT_RECORD& inputRecord, WindowEvent& windowEvent)
	{
		windowEvent.eventType = WindowEvent::EventType::WindowResized;
		COORD sz = inputRecord.Event.WindowBufferSizeEvent.dwSize;
		windowEvent.sizeEvent.width = sz.X;
		windowEvent.sizeEvent.height = sz.Y;
	}

	void WindowsConsoleWindow::CreateMouseEvent(INPUT_RECORD& inputRecord, WindowEvent& windowEvent)
	{
		static int prevMouseButtons = 0;

		// Move event
		if (inputRecord.Event.MouseEvent.dwEventFlags & MOUSE_MOVED)
		{
			windowEvent.eventType = WindowEvent::EventType::MouseMoved;
			windowEvent.mouseMove.x = inputRecord.Event.MouseEvent.dwMousePosition.X;
			windowEvent.mouseMove.y = inputRecord.Event.MouseEvent.dwMousePosition.Y;
			return;
		}
		
		// Button event
		int currentMouseButtons =
			((inputRecord.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) ? 1 : 0) |
			((inputRecord.Event.MouseEvent.dwButtonState & RIGHTMOST_BUTTON_PRESSED) ? 0b10 : 0) |
			((inputRecord.Event.MouseEvent.dwButtonState & FROM_LEFT_2ND_BUTTON_PRESSED) ? 0b100 : 0) |
			((inputRecord.Event.MouseEvent.dwButtonState & FROM_LEFT_3RD_BUTTON_PRESSED) ? 0b1000 : 0) |
			((inputRecord.Event.MouseEvent.dwButtonState & FROM_LEFT_4TH_BUTTON_PRESSED) ? 0b10000 : 0);

		for (int i = 0; i < 5; i++)
		{
			bool prevPressed = prevMouseButtons >> i & 1;
			bool currentPressed = currentMouseButtons >> i & 1;
			if (!prevPressed && currentPressed)
			{
				windowEvent.eventType = WindowEvent::EventType::MouseButtonPressed;
				windowEvent.mouseButton.button = i + 1;
				break;
			}
			else if (prevPressed && !currentPressed)
			{
				windowEvent.eventType = WindowEvent::EventType::MouseButtonReleased;
				windowEvent.mouseButton.button = i + 1;
				break;
			}
			windowEvent.eventType = WindowEvent::EventType::Unknown;
		}
		prevMouseButtons = currentMouseButtons;
	}

	void WindowsConsoleWindow::CreateKeyEvent(INPUT_RECORD& inputRecord, WindowEvent& windowEvent)
	{
		if (inputRecord.Event.KeyEvent.bKeyDown)
			windowEvent.eventType = WindowEvent::EventType::KeyPressed;
		else
			windowEvent.eventType = WindowEvent::EventType::KeyReleased;

		windowEvent.keyEvent.keyCode = inputRecord.Event.KeyEvent.uChar.AsciiChar;
		windowEvent.keyEvent.scanCode = inputRecord.Event.KeyEvent.wVirtualScanCode;
		windowEvent.keyEvent.altPressed = inputRecord.Event.KeyEvent.dwControlKeyState &
			(LEFT_ALT_PRESSED | RIGHT_ALT_PRESSED);
		windowEvent.keyEvent.ctrlPressed = inputRecord.Event.KeyEvent.dwControlKeyState &
			(LEFT_CTRL_PRESSED | RIGHT_CTRL_PRESSED);
		windowEvent.keyEvent.shiftPressed = inputRecord.Event.KeyEvent.dwControlKeyState & SHIFT_PRESSED;
		windowEvent.keyEvent.capslockPressed = inputRecord.Event.KeyEvent.dwControlKeyState & CAPSLOCK_ON;
	}
}// namespace Engine