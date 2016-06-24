#pragma once

#include <string>

struct HueRuleActionBody
{
    HueRuleActionBody(const Json::Value& value)
    : scene(value.get("scene", "").asString())
    {}

    Json::Value SerializeToJson()
    {
        Json::Value root;
        root["scene"] = scene;
        return root;
    }

    std::string scene;
};