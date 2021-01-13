#pragma once

#include "Core.h"

#define PLATFORM_WINDOWS

#ifdef PLATFORM_WINDOWS
#include <Windows.h>
#endif


namespace Engine
{
	struct PlatformInfo
	{
		enum ProcessorArchitecture { X64, ARM, ARM64, X86, UNKOWN };

		ProcessorArchitecture processorArchitecture;
	};

	static bool GetPlatformInfo(PlatformInfo& info)
	{
#ifdef PLATFORM_WINDOWS
		SYSTEM_INFO sysInfo;
		GetSystemInfo(&sysInfo);

		switch (sysInfo.wProcessorArchitecture)
		{
		case PROCESSOR_ARCHITECTURE_AMD64:
			info.processorArchitecture = PlatformInfo::X64;
			break;

		case PROCESSOR_ARCHITECTURE_ARM:
			info.processorArchitecture = PlatformInfo::ARM;

		case PROCESSOR_ARCHITECTURE_ARM64:
			info.processorArchitecture = PlatformInfo::ARM64;
			break;

		case PROCESSOR_ARCHITECTURE_INTEL:
			info.processorArchitecture = PlatformInfo::X86;
			break;

		case PROCESSOR_ARCHITECTURE_UNKNOWN:
			info.processorArchitecture = PlatformInfo::UNKOWN;
			break;
		}
#endif

		return true;
	}
}