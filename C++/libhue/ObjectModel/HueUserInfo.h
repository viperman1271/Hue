#pragma once

#include <string>

struct HueUserInfo
{
    std::string username;

    HueUserInfo(const Json::Value& root)
        : username(root.isObject() ? root.get("username", "").asString() : "")
    {}

    HueUserInfo()
    {}
};
