#include "HueBridgeLocator.h"
#include "HueBridge.h"
#include <curl/curl.h>

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

	CommandLineCommands cmdArgs;
	cmdArgs.Parse(argc, argv);

    HueBridge* bridge = HueBridgeLocator::Locate();
    if(!bridge)
    {
        return -1;
    }

	cmdArgs.SetBridge(bridge);
	cmdArgs.Execute();

// 	for (CommandLineCommands::ACTIONS action : cmdArgs.GetActions())
// 	{
// 		switch (action)
// 		{
// 		case CommandLineCommands::FLASH:
// 			bridge->FlashLights();
// 			break;
// 
// 		case CommandLineCommands::SWITCH_BATHROOM:
// 			SwitchSceneForLight(bridge);
// 			break;
// 
// 		case CommandLineCommands::SET_BATHROOM_DAY:
// 			SetBathroomSceneForDay(bridge);
// 			break;
// 
// 		case CommandLineCommands::SET_BATHROOM_NIGHT:
// 			SetBathroomSceneForNight(bridge);
// 			break;
// 
// 		default:
// 			continue;
// 		}
// 	}

    return 0;
}