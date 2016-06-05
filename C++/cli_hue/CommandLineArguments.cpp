#include "CommandLineArguments.h"
#include <string.h>

void CommandLineArguments::Parse(int argc, char ** argv)
{
	for (int i = 0; i < argc; ++i)
	{
		if (strcmp(argv[i], "-flash") == 0)
		{
			m_actions.push_back(FLASH);
		}
		else if (strcmp(argv[i], "-switch_bathroom") == 0)
		{
			m_actions.push_back(SWITCH_BATHROOM);
		}
		else if (strcmp(argv[i], "-set_bathroom_day") == 0)
		{
			m_actions.push_back(SET_BATHROOM_DAY);
		}
		else if (strcmp(argv[i], "-set_bathroom_night") == 0)
		{
			m_actions.push_back(SET_BATHROOM_NIGHT);
		}
	}
}
