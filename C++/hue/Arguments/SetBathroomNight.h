#pragma once

#include "Command.h"
#include "HueHelpers.h"

class SetBathroomNightCommand : public Command
{
	typedef Command super;
public:
	SetBathroomNightCommand();
	void Execute() override;
};