#include <string>
#include "HueLightState.h"
#ifdef LINUX_VS
#	include "../../lib_json_linux/include/json/reader.h"
#else
#	include "json/reader.h"
#endif

struct HueLightInformation
{
    HueLightInformation(const Json::Value& value, const std::string& objectId)
    : state(value["state"])
    , type(value.get("type", "").asString())
    , name(value.get("name", "").asString())
    , modelid(value.get("modelid", "").asString())
    , manufacturername(value.get("manufacturername", "").asString())
    , uniqueid(value.get("uniqueid", "").asString())
    , swversion(value.get("swversion", "").asString())
    , id(objectId)
    {
    }

    HueLightState state;
    std::string type;
    std::string name;
    std::string modelid;
    std::string manufacturername;
    std::string uniqueid;
    std::string swversion;
    std::string id;
};
