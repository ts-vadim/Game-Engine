#pragma once

//	Problems with s_CoreLogger, s_ClientLogger etc.
//	"needs to have dll-interface to be used by clients of class 'Engine::Log'"
#pragma warning (disable : 4251)

#include "Core.h"
#include <memory>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <ctime>
#include <chrono>


#define __FILEPOS __FILE__, __LINE__, __FUNCTION__
#define __FILEPOS_ARGS const char* FILE, const int LINE, const char* FUNCTION


namespace Engine
{
	class ENGINE_API Log
	{
	public:
		static void Trace(const char* title, const char* format, ...);
		static void Info(const char* title, const char* format, ...);
		static void Warning(const char* title, const char* format, ...);
		static void Error(__FILEPOS_ARGS, const char* title, const char* format, ...);
		static void Critical(__FILEPOS_ARGS, const char* title, const char* format, ...);

	public:
		static void CreateTimePattern(char* buffer, size_t bmax);
		static void CreateFilePosPattern(char* buffer, size_t bmax, __FILEPOS_ARGS);
		static void CreatePrefix(char* buffer, size_t bmax, const char* timePattern);
		static void PrintLogMessage(const char* title, const char* loglevel, const char* format);

		static const int s_TimeBufferLength;
		static const int s_FilePosBufferLength;
		static const int s_PrefixBufferLength;
		static const int s_MessageBufferLength;
		static const int s_LogLevelMaxPadding;
		static const int s_TitleMaxPadding;

		static char s_TimeBuffer[];
		static char s_FilePosBuffer[];
		static char s_PrefixBuffer[];
		static char s_MessageBuffer[];
	};
}


#ifdef ENGINE_DEBUG
	#define ENGINE_CORE_TRACE(...) Engine::Log::Trace("CORE", __VA_ARGS__)
	#define ENGINE_CORE_INFO(...) Engine::Log::Info("CORE", __VA_ARGS__)
	#define ENGINE_CORE_WARN(...) Engine::Log::Warning("CORE", __VA_ARGS__)
	#define ENGINE_CORE_ERROR(...) Engine::Log::Error(__FILEPOS, "CORE", __VA_ARGS__)
	#define ENGINE_CORE_CRITICAL(...) Engine::Log::Critical(__FILEPOS, "CORE", __VA_ARGS__)
#else
	#define ENGINE_CORE_TRACE(...)
	#define ENGINE_CORE_INFO(...)
	#define ENGINE_CORE_WARN(...)
	#define ENGINE_CORE_ERROR(...)
	#define ENGINE_CORE_CRITICAL(...)
#endif


#define ENGINE_TRACE(...) Engine::Log::Trace(0, __VA_ARGS__)
#define ENGINE_INFO(...) Engine::Log::Info(0, __VA_ARGS__)
#define ENGINE_WARN(...) Engine::Log::Warning(0, __VA_ARGS__)
#define ENGINE_ERROR(...) Engine::Log::Error(__FILEPOS, 0, __VA_ARGS__)
#define ENGINE_CRITICAL(...) Engine::Log::Critical(__FILEPOS, 0, __VA_ARGS__)


