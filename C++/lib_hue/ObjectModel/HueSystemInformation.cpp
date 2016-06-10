#include "HueSystemInformation.h"
#include <iostream>

void HueSystemInformation::DeserializeJson(const Json::Value& root)
{
    try
    {
        UpdateLights(root);
        UpdateGroups(root);
        UpdateConfig(root);
        UpdateScenes(root);
        UpdateSensors(root);
        UpdateRules(root);
    }
    catch (std::exception& ex)
    {
        std::cout << ex.what();
        //Console.WriteLine(ex.Message);
    }
}

void HueSystemInformation::UpdateLights(const Json::Value& root)
{
    lights.clear();
    
    //for (const Json::Value& obj : root["lights"])
    for (auto iter = root["lights"].begin(); iter != root["lights"].end(); ++iter)
    {
        HueLightInformation lightInfo(*iter, iter.key().asString());
        lights.push_back(lightInfo);
    }
}

void HueSystemInformation::UpdateGroups(const Json::Value& root)
{
    groups.clear();
    for (const Json::Value& obj : root["groups"])
    {
        HueGroupInformation groupInfo(obj);
        groups.push_back(groupInfo);
    }
}

void HueSystemInformation::UpdateConfig(const Json::Value& root)
{
    config = HueConfigInformation(root["groups"]);
}

void HueSystemInformation::UpdateScenes(const Json::Value& root)
{
    scenes.clear();
    for (auto iter = root["scenes"].begin(); iter != root["scenes"].end(); ++iter)
    {
        HueSceneInformation sceneInfo(*iter, iter.key().asString());
        scenes.push_back(sceneInfo);
    }
}

void HueSystemInformation::UpdateRules(const Json::Value& root)
{
    rules.clear();
    for (auto iter = root["rules"].begin(); iter != root["rules"].end(); ++iter)
    {
        HueRuleInformation ruleInfo(*iter, iter.key().asString());
        rules.push_back(ruleInfo);
    }
}

void HueSystemInformation::UpdateSensors(const Json::Value& root)
{
    sensors.clear();
    for (const Json::Value& obj : root["sensors"])
    {
        HueSensorInformation sensorInfo(obj);
        sensors.push_back(sensorInfo);
    }
}

void HueSystemInformation::RemoveQuotationMarks(std::string& str)
{
    int index = str.find('\"');
    while (index >= 0)
    {
        str = str.erase(index, 1);
        index = str.find('\"');
    }
}
