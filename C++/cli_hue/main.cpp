#include "HueBridgeLocator.h"
#include "HueBridge.h"
#include "curl/curl.h"

#include "CommandLineArguments.h"
#include "HueRules.h"
#include <iostream>
#include <string.h>

namespace libhue_callbacks
{
    void RegistationError(int error)
    {
        if (error == 101)
        {
            std::cout << "Press the button on the link bridge" << std::endl;
        }
    }
}

void ExceptionHandler()
{
    std::cerr << "Unhandled exception caught" << std::endl;
    abort();
}

int main(int argc, char** argv)
{
    std::set_terminate(ExceptionHandler);

	CommandLineArguments cmdArgs;
	cmdArgs.Parse(argc, argv);

    HueBridge* bridge = HueBridgeLocator::Locate();
    if(!bridge)
    {
        return -1;
    }

	for (CommandLineArguments::ACTIONS action : cmdArgs.GetActions())
	{
		switch (action)
		{
		case CommandLineArguments::FLASH:
			bridge->FlashLights();
			break;

		case CommandLineArguments::SWITCH_BATHROOM:
			SwitchSceneForLight(bridge);
			break;

		case CommandLineArguments::SET_BATHROOM_DAY:
			SetBathroomSceneForDay(bridge);
			break;

		case CommandLineArguments::SET_BATHROOM_NIGHT:
			SetBathroomSceneForNight(bridge);
			break;

		default:
			continue;
		}
	}

    return 0;
}