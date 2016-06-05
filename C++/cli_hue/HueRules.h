#pragma once

#include <string>

#ifdef LINUX_VS
#	include "../lib_hue_linux/HttpClient.h"
#else
#	include "HttpClient.h"
#endif

std::string replace(std::string &s, const std::string &toReplace, const std::string &replaceWith)
{
    return(s.replace(s.find(toReplace), toReplace.length(), replaceWith));
}

void SwitchScene(HueBridge* bridge, HueRuleInformation rule, HueSceneInformation* originalScene, HueSceneInformation* newScene)
{
    std::string currentRuleName = originalScene->name.substr(0, originalScene->name.find(' '));
    std::string newRuleName = newScene->name.substr(0, newScene->name.find(' '));
    replace(rule.name, currentRuleName, newRuleName);
    rule.actions[0].body.scene = newScene->id;
    HueBasicRuleInformation basicRule(rule);
    std::string serializedData = basicRule.SerializeToText();// "{\"name\":\"Dimmer 2.1 Bathroom - Daytime\",\"actions\":[{\"address\":\"/groups/" + rule.id + "/action\",\"method\":\"PUT\",\"body\":{\"scene\":\"" + newScene->id + "\"}}]}";// basicRule.Serialize();

    std::string url = bridge->Urls.GetRuleUrl(rule.id);
    std::string statusResponse = HttpClient::GetInstance()->Put(url, serializedData);
}

bool FillSceneInformation(HueBridge* bridge, HueSceneInformation** sceneDay, HueSceneInformation** sceneNight)
{
	if (sceneDay == nullptr || sceneNight == nullptr)
		return false;

	//Find the scenes
	for (HueSceneInformation& scene : bridge->info.scenes)
	{
		if (scene.id == "324e97cf0-on-0") //Bathroom - Daytime
		{
			*sceneDay = &scene;
		}
		else if (scene.id == "b7fe67faf-on-0") //Bathroom - Night
		{
			*sceneNight = &scene;
		}

		if (*sceneDay && *sceneNight)
			break;
	}

	if (*sceneDay == nullptr || *sceneNight == nullptr)
		return false;

	return true;
}

void SwitchSceneForLight(HueBridge* bridge)
{
    //Find the scene
    HueSceneInformation* sceneDay = nullptr;
    HueSceneInformation* sceneNight = nullptr;
	if (!FillSceneInformation(bridge, &sceneDay, &sceneNight))
		return;

    for(const HueRuleInformation& rule : bridge->info.rules)
    {
        if (rule.actions[0].body.scene == sceneDay->id)
        {
            SwitchScene(bridge, rule, sceneDay, sceneNight);
            break;
        }
        else if (rule.actions[0].body.scene == sceneNight->id)
        {
            SwitchScene(bridge, rule, sceneNight, sceneDay);
            break;
        }
    }
}

void SetBathroomSceneForNight(HueBridge* bridge)
{
	//Find the scene
	HueSceneInformation* sceneDay = nullptr;
	HueSceneInformation* sceneNight = nullptr;
	if (!FillSceneInformation(bridge, &sceneDay, &sceneNight))
		return;

	for (const HueRuleInformation& rule : bridge->info.rules)
	{
		if (rule.actions[0].body.scene == sceneDay->id)
		{
			SwitchScene(bridge, rule, sceneDay, sceneNight);
			break;
		}
	}
}

void SetBathroomSceneForDay(HueBridge* bridge)
{
	//Find the scene
	HueSceneInformation* sceneDay = nullptr;
	HueSceneInformation* sceneNight = nullptr;
	if (!FillSceneInformation(bridge, &sceneDay, &sceneNight))
		return;

	for (const HueRuleInformation& rule : bridge->info.rules)
	{
		if (rule.actions[0].body.scene == sceneNight->id)
		{
			SwitchScene(bridge, rule, sceneNight, sceneDay);
			break;
		}
	}
}
