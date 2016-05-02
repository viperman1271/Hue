#include <string>

struct HueSensorConfigInfo
{
    HueSensorConfigInfo(const Json::Value& value)
    : battery(value.get("battery", 0).asInt())
    , on(value.get("on", false).asBool())
    , reachable(value.get("reachable", false).asBool())
    , m_long(value.get("long", "").asString())
    , lat(value.get("lat", "").asString())
    , sunriseoffset(value.get("sunriseoffset", "").asString())
    , sunsetoffset(value.get("sunsetoffset", "").asString())
    {}
    int battery;
    bool on;
    bool reachable;
    std::string m_long;
    std::string lat;
    std::string sunriseoffset;
    std::string sunsetoffset;
};
