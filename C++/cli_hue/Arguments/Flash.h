#pragma once

#include "Command.h"

class FlashCommand : public Command
{
	typedef Command super;
public:
	FlashCommand()
		: super("flash")
	{

	}

	void Execute() override
	{
		m_bridge->FlashLights();
	}
};
