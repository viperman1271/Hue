#pragma once

#include <string>
#include <json/reader.h>

struct HueBridgeInfo
{
    HueBridgeInfo(const Json::Value& value)
    : id(value[0].get("id", "").asString())
    , internalipaddress(value[0].get("internalipaddress", "").asString())
    {
    }
    const std::string id;
    const std::string internalipaddress;
};
