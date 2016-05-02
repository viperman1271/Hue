#include <string>
#include "HueSensorStateInfo.h"
#include "HueSensorConfigInfo.h"

struct HueSensorInformation
{
    HueSensorInformation(const Json::Value& value)
    : state(value["state"])
    , config(value["config"])
    , name(value.get("name", "").asString())
    , type(value.get("type", "").asString())
    , modelid(value.get("modelid", "").asString())
    , manufacturername(value.get("manufacturername", "").asString())
    , swversion(value.get("swversion", "").asString())
    , uniqueid(value.get("uniqueid", "").asString())
    {}
    HueSensorStateInfo state;
    HueSensorConfigInfo config;
    std::string name;
    std::string type;
    std::string modelid;
    std::string manufacturername;
    std::string swversion;
    std::string uniqueid;
};
