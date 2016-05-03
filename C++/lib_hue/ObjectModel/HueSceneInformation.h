#include <string>
#include <vector>

struct HueSceneInformation
{
    HueSceneInformation()
    {}

    HueSceneInformation(const Json::Value& value, const std::string& sceneId)
        : id(sceneId)
        , name(value.get("name", "").asString())
        , owner(value.get("owner", "").asString())
        , picture(value.get("picture", "").asString())
        , lastupdated(value.get("lastupdated", "").asString())
        , version(value.get("version", 0).asInt())
        , recycle(value.get("recycle", false).asBool())
        , locked(value.get("locked", false).asBool())
    {
        for (auto obj : value["lights"])
        {
            lights.push_back(obj.asString());
        }
    }

    std::string id;
    std::string name;
    std::vector<std::string> lights;
    std::string owner;
    std::string picture;
    std::string lastupdated;
    int version;
    bool recycle;
    bool locked;
};
