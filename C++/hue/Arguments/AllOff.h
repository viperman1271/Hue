#pragma once

#include "Command.h"
#include "HueHelpers.h"

class AllOffCommand : public Command
{
	typedef Command super;
public:
	AllOffCommand()
		: super("all_off")
	{

	}

	void Execute() override
	{
		m_bridge->TurnOffLights();
	}
};