#pragma once

#include "Command.h"
#include "HueHelpers.h"

class SetBathroomNightCommand : public Command
{
	typedef Command super;
public:
	SetBathroomNightCommand()
		: super("set_bathroom_night")
	{

	}

	void Execute() override
	{
		//Find the scene
		HueSceneInformation* sceneDay = nullptr;
		HueSceneInformation* sceneNight = nullptr;
		if (!HueHelpers::FillSceneInformation(m_bridge, &sceneDay, &sceneNight))
			return;

		for (const HueRuleInformation& rule : m_bridge->info.rules)
		{
			if (rule.actions[0].body.scene == sceneDay->id)
			{
				HueHelpers::SwitchScene(m_bridge, rule, sceneDay, sceneNight);
				break;
			}
		}
	}
};