#include "HueBridgeLocator.h"
#include "HueBridge.h"
#include <curl/curl.h>

#include "CommandLineArguments.h"
#include "HueHelpers.h"
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

    return 0;
}