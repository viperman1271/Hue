#include <string>

#include "HueRuleAction.h"
#include "json/writer.h"

struct HueRuleInformation
{
    HueRuleInformation()
    {}

    HueRuleInformation(const Json::Value& value, const std::string& ruleId)
        : id(ruleId)
        , name(value.get("name", "").asString())
        , owner(value.get("owner", "").asString())
        , created(value.get("created", "").asString())
        , lasttriggered(value.get("lasttriggered", "").asString())
        , status(value.get("status", "").asString())
        , timestriggered(value.get("timestriggered", 0).asInt())
        , recycle(value.get("recycle", false).asBool())
    {
        for (auto obj : value["actions"])
        {
            actions.push_back(HueRuleAction(obj));
        }
    }
    std::string id;
    std::string name;
    std::string owner;
    std::string created;
    std::string lasttriggered;
    std::string status;
    int timestriggered;
    bool recycle;
    std::vector<HueRuleAction> actions;
};

struct HueBasicRuleInformation
{
    std::string name;
    std::vector<HueRuleAction> actions;

    HueBasicRuleInformation(const HueRuleInformation& ruleInfo)
        : name(ruleInfo.name)
        , actions(ruleInfo.actions)
    {
    }

    std::string SerializeToText()
    {
        Json::Value root;
        root["name"] = name;
        for (HueRuleAction& action : actions)
        {
            root["actions"].append(action.SerializeToJson());
        }

        Json::FastWriter writer;
        return writer.write(root);
    }
};