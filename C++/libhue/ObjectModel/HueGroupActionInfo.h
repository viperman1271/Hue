#pragma once

struct HueGroupActionInfo
{
    HueGroupActionInfo(const Json::Value& value)
    : on(value.get("on", false).asBool())
    , bri(value.get("bri", 0).asInt())
    , hue(value.get("hue", 0).asInt())
    , sat(value.get("sat", 0).asInt())
    , ct(value.get("ct", 0).asInt())
    , effect(value.get("effect", "").asString())
    , alert(value.get("alert", "").asString())
    , colormode(value.get("colormode", "").asString())
    {

    }

    bool on;
    int bri;
    int hue;
    int sat;
    int ct;
    std::string effect;
    std::string alert;
    std::string colormode;
};