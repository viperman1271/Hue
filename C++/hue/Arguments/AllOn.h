#pragma once

#include "Command.h"
#include "HueHelpers.h"

class AllOnCommand : public Command
{
	typedef Command super;
public:
	AllOnCommand()
		: super("all_on")
	{

	}

	void Execute() override
	{
		m_bridge->TurnOnLights();
	}
};