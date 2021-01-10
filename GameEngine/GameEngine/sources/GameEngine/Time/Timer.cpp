#include "Timer.h"


namespace Engine
{
	Timer::Timer()
		: m_Name("Timer")
	{
		Reset();
	}

	Timer::Timer(const char* name)
		: m_Name(name)
	{
		Reset();
	}

	Timer::~Timer()
	{
	}

	void Timer::Reset()
	{
		m_StartTimepoint = Time::NowMicros();
	}

	double Timer::GetElapsedTimeSec() const
	{
		return (Time::NowMicros() - m_StartTimepoint) / 1000000.0;
	}

	double Timer::GetElapsedTimeMs() const
	{
		return (Time::NowMicros() - m_StartTimepoint) / 1000.0;
	}

	const char* Timer::GetName() const
	{
		return m_Name;
	}
}