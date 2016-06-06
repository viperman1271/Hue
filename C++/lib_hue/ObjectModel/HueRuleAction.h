#pragma once

#include "HueRuleActionBody.h"

struct HueRuleAction
{
    HueRuleAction(const Json::Value& value)
    : address(value.get("address", "").asString())
    , method(value.get("method", "").asString())
    , body(value["body"])
    {}

    Json::Value SerializeToJson()
    {
        Json::Value root;
        root["address"] = address;
        root["method"] = method;
        root["body"] = body.SerializeToJson();
        return root;
    }

    std::string address;
    std::string method;
    HueRuleActionBody body;
};