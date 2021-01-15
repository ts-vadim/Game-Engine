#pragma once


#ifdef ENGINE_BUILD_DLL
	#define ENGINE_API __declspec(dllexport)
#else
	#define ENGINE_API __declspec(dllimport)
#endif


#if defined(_WIN32)
	#define ENGINE_PLATFORM_WINDOWS
#elif defined(__APPLE__)
	#define ENGINE_PLATFORM_MAC
#else
	#define ENGINE_PLATFORM_UNIX
#endif


#define ENGINE_FUNC_SIG __FUNCTION__ 
#define ENGINE_FILE_SIG __FILE__
#define ENGINE_LINE_SIG __LINE__


#ifdef ENGINE_ENABLE_ASSERTS
	#include <iostream>
	#define ASSERT(cond, msg) if (!cond) { std::cout << "ASSERT ERROR in " << ENGINE_FILE_SIG << ":" << ENGINE_LINE_SIG << " " << ENGINE_FUNC_SIG << "(): " << msg << std::endl; }
	#define ASSERT_HALT(cond, msg) if (!cond) { ASSERT(false, msg); while (true); }
	#define ASSERT_RETURN(cond, msg) if (!cond) { ASSERT(false, msg); return; }
#else
	#define ASSERT(cond, msg)
	#define ASSERT_HALT(cond, msg)
	#define ASSERT_RETURN(cond, msg)
#endif
