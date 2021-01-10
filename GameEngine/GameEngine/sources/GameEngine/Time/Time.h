#pragma once

#include "Core.h"
#include <chrono>


namespace Engine
{
	class ENGINE_API Time
	{
	public:
		static long long NowHours()
		{
			return std::chrono::time_point_cast<std::chrono::hours>(Now()).time_since_epoch().count();
		}

		static long long NowMinutes()
		{
			return std::chrono::time_point_cast<std::chrono::minutes>(Now()).time_since_epoch().count();
		}

		static long long NowSeconds()
		{
			return std::chrono::time_point_cast<std::chrono::seconds>(Now()).time_since_epoch().count();
		}

		static long long NowMillis()
		{
			return std::chrono::time_point_cast<std::chrono::milliseconds>(Now()).time_since_epoch().count();
		}

		static long long NowMicros()
		{
			return std::chrono::time_point_cast<std::chrono::microseconds>(Now()).time_since_epoch().count();
		}

	private:
		static std::chrono::time_point<std::chrono::high_resolution_clock> Now()
		{
			return std::chrono::high_resolution_clock::now();
		}
	};
}
