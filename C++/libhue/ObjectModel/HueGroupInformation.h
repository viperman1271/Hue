#pragma once

#include <string>
#include <vector>
#include "HueGroupActionInfo.h"

struct HueGroupInformation
{
    HueGroupInformation(const Json::Value& value)
    : name(value.get("name", "").asString())
    , type(value.get("type", "").asString())
    , action(value["action"])
    , recycle(value.get("recycle", false).asBool())
    {
        for (auto obj : value["lights"])
        {
            lights.push_back(obj.asString());
        }
    }

    std::string name;
    std::string type;
    std::vector<std::string> lights;
    HueGroupActionInfo action;
    bool recycle;
};
