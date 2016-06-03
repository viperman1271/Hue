#include <string>
#ifdef LINUX_VS
#	include "../../lib_json_linux/include/json/writer.h"
#elif LINUX_VS_UNIFIED
#	include "../../JsonCpp/include/json/writer.h"
#else
#	include "json/writer.h"
#endif

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