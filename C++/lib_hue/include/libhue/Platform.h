#pragma once

#include <time.h>
#ifdef LINUX
#include <unistd.h>
#include <chrono>
#else
#include <windows.h>
#endif // LINUX

namespace HUEPLATFORM
{
	inline void SLEEP(std::chrono::milliseconds ms)
	{
#ifdef LINUX
		usleep((unsigned int)std::chrono::duration_cast<std::chrono::microseconds>(ms).count());
#else
		Sleep((DWORD)ms.count());
#endif
	}

	inline void SLEEP(std::chrono::seconds sec)
	{
		SLEEP(std::chrono::duration_cast<std::chrono::milliseconds>(sec));
	}
}