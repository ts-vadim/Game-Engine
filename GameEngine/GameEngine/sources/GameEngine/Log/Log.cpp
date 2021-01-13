#include "Log.h"


namespace Engine
{
	const int Log::s_TimeBufferLength = 20;
	const int Log::s_FilePosBufferLength = 500;
	const int Log::s_PrefixBufferLength = s_TimeBufferLength + s_FilePosBufferLength;
	const int Log::s_MessageBufferLength = 1000;
	const int Log::s_LogLevelMaxPadding = 11;
	const int Log::s_TitleMaxPadding = 6;

	char Log::s_TimeBuffer[s_TimeBufferLength];
	char Log::s_FilePosBuffer[s_FilePosBufferLength];
	char Log::s_PrefixBuffer[s_PrefixBufferLength];
	char Log::s_MessageBuffer[s_MessageBufferLength];


	void Log::Trace(const char* title, const char* format, ...)
	{
		CreateTimePattern(s_TimeBuffer, s_TimeBufferLength);
		CreatePrefix(s_PrefixBuffer, s_PrefixBufferLength, s_TimeBuffer);

		va_list args;
		va_start(args, format);
		vsnprintf_s(s_MessageBuffer, s_MessageBufferLength, s_MessageBufferLength, format, args);
		va_end(args);

		PrintLogMessage(title, "[TRACE]", "%s %-*s %-*s %s\n");
	}

	void Log::Info(const char* title, const char* format, ...)
	{
		CreateTimePattern(s_TimeBuffer, s_TimeBufferLength);
		CreatePrefix(s_PrefixBuffer, s_PrefixBufferLength, s_TimeBuffer);

		va_list args;
		va_start(args, format);
		vsnprintf_s(s_MessageBuffer, s_MessageBufferLength, s_MessageBufferLength, format, args);
		va_end(args);

		PrintLogMessage(title, "[INFO]", "%s %-*s %-*s %s\n");
	}

	void Log::Warning(const char* title, const char* format, ...)
	{
		CreateTimePattern(s_TimeBuffer, s_TimeBufferLength);
		CreatePrefix(s_PrefixBuffer, s_PrefixBufferLength, s_TimeBuffer);

		va_list args;
		va_start(args, format);
		vsnprintf_s(s_MessageBuffer, s_MessageBufferLength, s_MessageBufferLength, format, args);
		va_end(args);

		PrintLogMessage(title, "[WARNING]", "%s %-*s %-*s %s\n");
	}

	void Log::Error(__FILEPOS_ARGS, const char* title, const char* format, ...)
	{
		CreateTimePattern(s_TimeBuffer, s_TimeBufferLength);
		CreateFilePosPattern(s_FilePosBuffer, s_FilePosBufferLength, FILE, LINE, FUNCTION);
		CreatePrefix(s_PrefixBuffer, s_PrefixBufferLength, s_TimeBuffer);

		va_list args;
		va_start(args, format);
		vsnprintf_s(s_MessageBuffer, s_MessageBufferLength, s_MessageBufferLength, format, args);
		va_end(args);

		PrintLogMessage(title, "[ERROR]", "%s %-*s %-*s %s\n");
		printf("  Location %s\n", s_FilePosBuffer);
	}

	void Log::Critical(__FILEPOS_ARGS, const char* title, const char* format, ...)
	{
		CreateTimePattern(s_TimeBuffer, s_TimeBufferLength);
		CreateFilePosPattern(s_FilePosBuffer, s_FilePosBufferLength, FILE, LINE, FUNCTION);
		CreatePrefix(s_PrefixBuffer, s_PrefixBufferLength, s_TimeBuffer);

		va_list args;
		va_start(args, format);
		vsnprintf_s(s_MessageBuffer, s_MessageBufferLength, s_MessageBufferLength, format, args);
		va_end(args);

		PrintLogMessage(title, "[CRITICAL]", "%s %-*s %-*s %s\n");
		printf("  Location %s\n", s_FilePosBuffer);
	}

	void Log::PrintLogMessage(const char* title, const char* loglevel, const char* format)
	{
		printf(format, s_PrefixBuffer, s_LogLevelMaxPadding, loglevel, s_TitleMaxPadding, ((title) ? title : ""), s_MessageBuffer);
	}

	void Log::CreateTimePattern(char* buffer, size_t bmax)
	{
		using namespace std::chrono;

		int ms = time_point_cast<milliseconds>(system_clock::now()).time_since_epoch().count() % 1000;
		time_t time_t_now = time(0);
		tm tm_now;
		localtime_s(&tm_now, &time_t_now);

		sprintf_s(buffer, bmax, "%02d:%02d:%02d.%03d", tm_now.tm_hour, tm_now.tm_min, tm_now.tm_sec, ms);
	}

	void Log::CreateFilePosPattern(char* buffer, size_t bmax, __FILEPOS_ARGS)
	{
		sprintf_s(buffer, bmax, "%s:%d %s()", FILE, LINE, FUNCTION);
	}

	void Log::CreatePrefix(char* buffer, size_t bmax, const char* timePattern)
	{
		sprintf_s(buffer, bmax, "[%s]", timePattern);
	}
}
