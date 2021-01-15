#include "Window.h"
#include "Platform/WindowsConsoleWindow.h"


namespace Engine
{
	Window* Window::Create(const WindowSettings& windowSettings)
	{
#ifdef ENGINE_PLATFORM_WINDOWS
		return new WindowsConsoleWindow(windowSettings);
#else
#error Only Windows platform is supported
#endif
	}
}