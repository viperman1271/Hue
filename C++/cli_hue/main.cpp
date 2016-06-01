#include "HueBridgeLocator.h"
#include "HueBridge.h"
#include "curl/curl.h"
#include <iostream>
#include "HueRules.h"

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

    HueBridge* bridge = HueBridgeLocator::Locate();
    if(!bridge)
    {
        return -1;
    }

    if (argc > 1 && std::string(argv[1]) == std::string("-flash"))
    {
        bridge->FlashLights();
    }
    else if (argc > 1 && std::string(argv[1]) == std::string("-switch_bathroom"))
    {
        SwitchSceneForLight(bridge);
    }
    return 0;
};
