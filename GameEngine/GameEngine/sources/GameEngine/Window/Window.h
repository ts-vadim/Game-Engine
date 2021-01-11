#pragma once

#include "Core.h"
#include <string>


namespace Engine
{
	struct WindowSettings
	{
		std::string title;
		uint32_t width;
		uint32_t height;

		WindowSettings()
			: title(""), width(0), height(0) {}

		WindowSettings(const std::string& p_title, uint32_t p_width, uint32_t p_height)
			: title(p_title), width(p_width), height(p_height) {}
	};

	class Window
	{
	public:
		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void* GetSystemHandle() const = 0;

		static Window* Create(const WindowSettings& windowSettings = WindowSettings());
	};
}
