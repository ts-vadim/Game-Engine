#include "Window.h"
#include "Platform/WindowsConsoleWindow.h"


namespace Engine
{
	Window* Window::Create(const WindowSettings& windowSettings)
	{
		return new WindowsConsoleWindow(windowSettings);
//#ifdef PLATFORM_WINDOWS
//		return new WindowsWindow(windowSettings);
//#else
//#error No platform-specific Window implementation available
//#endif
	}
}