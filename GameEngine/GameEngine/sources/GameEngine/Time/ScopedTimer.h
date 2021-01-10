#pragma once

#include "Core.h"
#include "Time/Time.h"


namespace Engine
{
	/// <summary>
	/// Time in seconds
	/// </summary>
	class ScopedTimer
	{
	public:
		ScopedTimer(double& value)
			: m_ValueRef(value)
		{
			m_ValueRef = 0;
			m_StartTimepoint = Time::NowMicros();
		}

		~ScopedTimer()
		{
			UpdateElapsedTime();
		}

		void UpdateElapsedTime()
		{
			m_ValueRef = (Time::NowMicros() - m_StartTimepoint) / 1000000.0;
		}

	private:
		long long m_StartTimepoint;
		double& m_ValueRef;
	};
}
