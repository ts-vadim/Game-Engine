#pragma once

#include "Core.h"
#include <ctime>
#include <chrono>


namespace Engine
{
	class ENGINE_API Time
	{
	public:
		class ENGINE_API SinceStartup
		{
		public:
			/// <returns>
			/// hours count since startup [0-...]
			/// </returns>
			static int Hours();
			/// <returns>
			/// minutes count since startup [0-...]
			/// </returns>
			static int Minutes();
			/// <returns>
			/// seconds count since startup [0-...]
			/// </returns>
			static long long Seconds();
			/// <returns>
			/// milliseconds count since startup [0-...]
			/// </returns>
			static long long Milliseconds();
			/// <returns>
			/// microseconds count since startup [0-...]
			/// </returns>
			static long long Microseconds();
		};

		class ENGINE_API Actual
		{
		public:
			/// <returns>
			/// hours [0-23]
			/// </returns>
			static int Hours();
			/// <returns>
			/// minutes [0-59]
			/// </returns>
			static int Minutes();
			/// <returns>
			/// seconds [0-59]
			/// </returns>
			static int Seconds();
			/// <returns>
			/// milliseconds [0-999]
			/// </returns>
			static int Milliseconds();
			/// <returns>
			/// seconds [0-999]
			/// </returns>
			static int Microseconds();
		};

		static std::chrono::high_resolution_clock::time_point GetTimePoint();
	};


	class ENGINE_API Date
	{
	public:
		/// <returns>
		/// month day [1-31]
		/// </returns>
		static int Day();
		/// <returns>
		/// week day [1-7]
		/// </returns>
		static int WeekDay();
		/// <returns>
		/// month [1-12]
		/// </returns>
		static int Month();
		/// <returns>
		/// year [1900-...]
		/// </returns>
		static int Year();
	};
}
