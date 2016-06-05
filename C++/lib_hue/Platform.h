#pragma once

#include <time.h>
#ifdef LINUX
#include <unistd.h>
#endif // LINUX

namespace HUEPLATFORM
{
	void SLEEP(unsigned int milliseconds)
	{
#ifdef LINUX
		usleep(milliseconds * 1000);
#else
		Sleep(milliseconds);
#endif
	}
}
