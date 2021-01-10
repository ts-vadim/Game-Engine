#pragma once

#include "Core.h"
#include "Time/Time.h"


namespace Engine
{
	class ENGINE_API Timer
	{
	public:
		Timer();
		Timer(const char* name);
		~Timer();

		void Reset();

		/// <summary>
		/// Returns elapsed time in seconds
		/// </summary>
		/// <returns></returns>
		double GetElapsedTimeSec() const;
		double GetElapsedTimeMs() const;
		const char* GetName() const;

	private:
		long long m_StartTimepoint;
		const char* m_Name;
	};
}
