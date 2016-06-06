#pragma once

#include <vector>
#include "HueBridge.h"
#include "Arguments/Command.h"

class CommandLineCommands
{
public:
	enum ACTIONS
	{
		FLASH,
		SWITCH_BATHROOM,
		SET_BATHROOM_DAY,
		SET_BATHROOM_NIGHT,

		COUNT
	};

	CommandLineCommands();

	void Parse(int argc, char** argv);
	void Execute();

	void SetBridge(HueBridge* bridge);
	const std::vector<ACTIONS>& GetActions() const { return m_actions; }
private:
	std::vector<ACTIONS> m_actions;
	std::vector<Command*> m_commands;
};