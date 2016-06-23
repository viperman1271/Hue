#pragma once

#include "Command.h"
#include "HueHelpers.h"

class SwitchBathroomCommand : public Command
{
	typedef Command super;
public:
	SwitchBathroomCommand()
		: super("trigger_scene")
	{

	}

	void Execute() override
	{
	}
}
