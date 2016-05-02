#include <string>

struct HueError
{
    int type;
    std::string address;
    std::string description;

    HueError()
        : type(0)
    {
    }

    HueError(const Json::Value& root)
        : type(root.isObject() ? root.get("type", "").asInt() : 0)
        , address(root.isObject() ? root.get("address", "").asString() : "")
        , description(root.isObject() ? root.get("description", "").asString() : "")
    {

    }
};