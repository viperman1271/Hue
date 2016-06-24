#pragma once

#include "Command.h"
#include "HueHelpers.h"

class SetBathroomDayCommand : public Command
{
	typedef Command super;
public:
	SetBathroomDayCommand();

	void Execute() override;
};

