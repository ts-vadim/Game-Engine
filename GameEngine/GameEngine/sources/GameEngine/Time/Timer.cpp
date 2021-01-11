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
		m_StartTimepoint = Time::Actual::Microseconds();
	}

	double Timer::GetElapsedTimeSec() const
	{
		return (Time::Actual::Microseconds() - m_StartTimepoint) / 1000000.0;
	}

	double Timer::GetElapsedTimeMs() const
	{
		return (Time::Actual::Microseconds() - m_StartTimepoint) / 1000.0;
	}

	const char* Timer::GetName() const
	{
		return m_Name;
	}
}