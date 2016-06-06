#pragma once

#include <string>

#include <json/reader.h>

struct HueLightState
{
    HueLightState(const Json::Value& value)
    : on(value.get("on", false).asBool())
    , reachable(value.get("reachable", false).asBool())
    , bri(value.get("bri", 0).asInt())
    , hue(value.get("hue", 0).asInt())
    , sat(value.get("sat", 0).asInt())
    , cy(value.get("cy", 0).asInt())
    , effect(value.get("effect", "").asString())
    , alert(value.get("alert", "").asString())
    , colormode(value.get("colormode", "").asString())
    {

    }

    bool on;
    bool reachable;
    int bri;
    int hue;
    int sat;
    int cy;
    std::string effect;
    std::string alert;
    std::string colormode;
};
