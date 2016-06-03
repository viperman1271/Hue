#include <string>
#ifdef LINUX_VS
#	include "../../lib_json_linux/include/json/reader.h"
#elif LINUX_VS_UNIFIED
#	include "../../JsonCpp/include/json/reader.h"
#else
#	include "json/reader.h"
#endif

struct HueBridgeInfo
{
    HueBridgeInfo(const Json::Value& value)
    : id(value[0].get("id", "").asString())
    , internalipaddress(value[0].get("internalipaddress", "").asString())
    {
    }
    const std::string id;
    const std::string internalipaddress;
};
