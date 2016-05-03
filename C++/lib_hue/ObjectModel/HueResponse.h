#include "ObjectModel/HueError.h"
#include "ObjectModel/HueUserInfo.h"

struct HueResponse
{
    HueError error;
    HueUserInfo success;

    HueResponse(const Json::Value& root)
    {
        if (root.isArray())
        {
            error = HueError(root[0].get("error", ""));
            success = HueUserInfo(root[0].get("success", ""));
        }
        else
        {
            error = HueError(root.get("error", ""));
            success = HueUserInfo(root.get("success", ""));
        }
    }
};