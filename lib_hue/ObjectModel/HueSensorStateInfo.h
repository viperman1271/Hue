#include <string>

struct HueSensorStateInfo
{
    HueSensorStateInfo(const Json::Value& value)
    : daylight(value.get("daylight", true).asBool())
    , lastupdated(value.get("lastupdated", "").asString())
    , buttonevent(value.get("buttonevent", 0).asInt())
    {}
    bool daylight;
    std::string lastupdated;
    int buttonevent;
};
