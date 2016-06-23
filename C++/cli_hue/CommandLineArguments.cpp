#include "CommandLineArguments.h"
#include <string.h>

#include "Arguments/AllOff.h"
#include "Arguments/AllOn.h"
#include "Arguments/Flash.h"
#include "Arguments/SetBathroomDay.h"
#include "Arguments/SetBathroomNight.h"
#include "Arguments/SwitchBathroom.h"

CommandLineCommands::CommandLineCommands()
{
	m_commands.push_back(new AllOffCommand());
	m_commands.push_back(new AllOnCommand());
	m_commands.push_back(new FlashCommand());
	m_commands.push_back(new SetBathroomDayCommand());
	m_commands.push_back(new SetBathroomNightCommand());
	m_commands.push_back(new SwitchBathroomCommand());
	m_commands.push_back(new TriggerSceneCommand());
}

void CommandLineCommands::Parse(int argc, char ** argv)
{
	for (int i = 0; i < argc; ++i)
	{
		for (Command* arg : m_commands)
		{
			if(strcmp(argv[i], arg->GetString().c_str()) == 0)
			{ 
				arg->FlagForExecution();
				break;
			}
		}

// 		if (strcmp(argv[i], "-flash") == 0)
// 		{
// 			m_actions.push_back(FLASH);
// 		}
// 		else if (strcmp(argv[i], "-switch_bathroom") == 0)
// 		{
// 			m_actions.push_back(SWITCH_BATHROOM);
// 		}
// 		else if (strcmp(argv[i], "-set_bathroom_day") == 0)
// 		{
// 			m_actions.push_back(SET_BATHROOM_DAY);
// 		}
// 		else if (strcmp(argv[i], "-set_bathroom_night") == 0)
// 		{
// 			m_actions.push_back(SET_BATHROOM_NIGHT);
// 		}
	}
}

void CommandLineCommands::Execute()
{
	for (Command* arg : m_commands)
	{
		if (arg->ShouldExecute())
		{
			arg->Execute();
		}
	}
}

void CommandLineCommands::SetBridge(HueBridge* bridge)
{
	for (Command* arg : m_commands)
	{
		arg->SetBridge(bridge);
	}
}