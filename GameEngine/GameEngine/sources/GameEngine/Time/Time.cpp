#include "Time.h"


static tm GetTmStruct()
{
	static time_t time_t_now;
	static tm tm_now;

	time_t_now = time(0);
	localtime_s(&tm_now, &time_t_now);
	return tm_now;
}


namespace Engine
{
	using namespace std::chrono;

	std::chrono::high_resolution_clock::time_point Time::GetTimePoint()
	{
		return std::chrono::high_resolution_clock::now();
	}

	//	############### Actual ###############
	int Time::Actual::Hours()
	{
		return GetTmStruct().tm_hour;
	}

	int Time::Actual::Minutes()
	{
		return GetTmStruct().tm_min;
	}

	int Time::Actual::Seconds()
	{
		return GetTmStruct().tm_sec;
	}

	int Time::Actual::Milliseconds()
	{
		return time_point_cast<milliseconds>(system_clock::now()).time_since_epoch().count() % 1000;
	}

	int Time::Actual::Microseconds()
	{
		return time_point_cast<microseconds>(system_clock::now()).time_since_epoch().count() % 1000;
	}

	//	############### SinceStartup ###############
	int Time::SinceStartup::Hours()
	{
		return time_point_cast<hours>(system_clock::now()).time_since_epoch().count();
	}

	int Time::SinceStartup::Minutes()
	{
		return time_point_cast<minutes>(system_clock::now()).time_since_epoch().count();
	}

	long long Time::SinceStartup::Seconds()
	{
		return time_point_cast<seconds>(system_clock::now()).time_since_epoch().count();
	}

	long long Time::SinceStartup::Milliseconds()
	{
		return time_point_cast<milliseconds>(system_clock::now()).time_since_epoch().count();
	}

	long long Time::SinceStartup::Microseconds()
	{
		return time_point_cast<microseconds>(system_clock::now()).time_since_epoch().count();
	}

	//	############### Date ###############
	int Date::Day()
	{
		return GetTmStruct().tm_mday;
	}

	int Date::WeekDay()
	{
		return GetTmStruct().tm_wday + 1;
	}

	int Date::Month()
	{
		return GetTmStruct().tm_mon + 1;
	}

	int Date::Year()
	{
		return GetTmStruct().tm_year + 1900;
	}
}