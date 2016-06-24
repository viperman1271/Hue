#pragma once

#include "Command.h"

class DumpJsonCommand : public Command
{
	typedef Command super;
public:
	DumpJsonCommand();

	void Execute() override;
};
