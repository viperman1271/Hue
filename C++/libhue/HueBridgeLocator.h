#pragma once

#include <string>

class HueBridge;

class HueBridgeLocator
{
public:
    static HueBridge* Locate();
    static HueBridge* LocateAsync();
    static HueBridge* LocateWithApi();

private:
    // http://www.nerdblog.com/2012/10/a-day-with-philips-hue.html - description.xml retrieval
    static bool IsHue(const std::string& discoveryUrl);
};
