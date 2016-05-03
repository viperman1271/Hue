#include <string>
#include "json/writer.h"

struct HueRegistration
{
    std::string devicetype;

    HueRegistration(const std::string& appname, const std::string& client)
        : devicetype(appname + "#" + client)
    {
    }

    Json::Value SerializeJson()
    {
        Json::Value serializeRoot;
        serializeRoot["devicetype"] = devicetype;
        return serializeRoot;
    }

    std::string SerializeText()
    {
        Json::Value serializedValue = SerializeJson();
        Json::FastWriter writer;
        std::string str = writer.write(serializedValue);
        return str;
    }
};