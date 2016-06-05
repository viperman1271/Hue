#pragma once

#include <vector>

class CommandLineArguments
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

	void Parse(int argc, char** argv);
	const std::vector<ACTIONS>& GetActions() const { return m_actions; }
private:
	std::vector<ACTIONS> m_actions;
};