#include <vector>
#include "HueLightInformation.h"
#include "HueGroupInformation.h"
#include "HueSceneInformation.h"
#include "HueRuleInformation.h"
#include "HueSensorInformation.h"
#include "HueConfigInformation.h"

#ifdef LINUX_VS
#	include "../../lib_json_linux/include/json/reader.h"
#else
#	include "json/reader.h"
#endif

class HueSystemInformation
{
public:
    void DeserializeJson(const Json::Value& json);

    void UpdateLights(const Json::Value& root);
    void UpdateGroups(const Json::Value& root);
    void UpdateConfig(const Json::Value& root);
    void UpdateScenes(const Json::Value& root);
    void UpdateRules(const Json::Value& root);
    void UpdateSensors(const Json::Value& root);

    static void RemoveQuotationMarks(std::string& str);

public:
    std::vector<HueLightInformation> lights;
    std::vector<HueGroupInformation> groups;
    std::vector<HueSceneInformation> scenes;
    std::vector<HueRuleInformation> rules;
    std::vector<HueSensorInformation> sensors;
    HueConfigInformation config;
};
