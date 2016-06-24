#pragma once

#include "HttpClient.h"
#include "HueBridge.h"

#include <string>

namespace HueHelpers
{
	bool FillSceneInformation(HueBridge* bridge, HueSceneInformation** sceneDay, HueSceneInformation** sceneNight);
	std::string replace(std::string &s, const std::string &toReplace, const std::string &replaceWith);
	void SwitchScene(HueBridge* bridge, HueRuleInformation rule, HueSceneInformation* originalScene, HueSceneInformation* newScene);
}