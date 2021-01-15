#pragma once
#pragma warning(disable : 4251)

#include "Core.h"
#include "Event/WindowEvent.h"
#include <string>
#include <functional>


namespace Engine
{
	struct ENGINE_API WindowSettings
	{
		std::string title;
		uint32_t width;
		uint32_t height;

		WindowSettings()
			: title(""), width(0), height(0) {}

		WindowSettings(const std::string& p_title, uint32_t p_width, uint32_t p_height)
			: title(p_title), width(p_width), height(p_height) {}

		WindowSettings(const WindowSettings& other)
		{
			title = other.title;
			width = other.width;
			height = other.height;
		}

		WindowSettings& operator=(const WindowSettings& other)
		{
			title = other.title;
			width = other.width;
			height = other.height;
			return *this;
		}
	};

	class ENGINE_API Window
	{
	public:
		using EventCallback = std::function<void(WindowEvent)>;

	public:
		virtual ~Window() {}

		virtual void Init() = 0;
		virtual void Close() = 0;

		virtual void OnUpdate() = 0;

		inline virtual uint32_t GetWidth() const = 0;
		inline virtual uint32_t GetHeight() const = 0;
		inline virtual void* GetSystemHandle() const = 0;

		virtual bool PollEvent(WindowEvent& event) = 0;

		/// <summary>
		/// Creates platform-specific window instance
		/// </summary>
		static Window* Create(const WindowSettings& windowSettings = WindowSettings());
	};
}
