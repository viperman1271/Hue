#pragma once

#include "Command.h"
#include "HueHelpers.h"

class TriggerSceneCommand : public Command
{
	typedef Command super;
public:
	TriggerSceneCommand()
		: super("trigger_scene")
	{

	}

	void Execute() override
	{
	}
};