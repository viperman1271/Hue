#pragma once

#include "Command.h"
#include "HueHelpers.h"

class SwitchBathroomCommand : public Command
{
	typedef Command super;
public:
	SwitchBathroomCommand();

	void Execute() override;
};
