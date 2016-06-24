#include "SwitchBathroom.h"

SwitchBathroomCommand::SwitchBathroomCommand() 
: super("switch_bathroom")
{

}

void SwitchBathroomCommand::Execute()
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
		else if (rule.actions[0].body.scene == sceneNight->id)
		{
			HueHelpers::SwitchScene(m_bridge, rule, sceneNight, sceneDay);
			break;
		}
	}
}
