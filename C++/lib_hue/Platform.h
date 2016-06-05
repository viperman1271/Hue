#pragma once

#include <time.h>
#include <unistd.h>

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
