#pragma once

#include <Core/Log.h>

#include "Command.h"



namespace VS
{
	//! Syntax:
	//! help <command> <subcommand> <subcommand> ...
	class HelpCommand : public Command
	{
	public:
		HelpCommand(const std::vector<std::string>& Parameters)
			: Command(Parameters)
		{

		}

		virtual Result Execute() override
		{
			VS_LOG(Output, BasicHelp + "\n" + HelpMessage);
			return Result{ EResult::Ok };
		}

		//! No real validation is needed for the help command
		virtual Result Validate() override
		{
			return Result{ EResult::Ok };
		}

	protected:
		inline static constexpr std::string Mnemonic = "help";
		inline static constexpr std::string BasicHelp = "Provides basic help information.";
	};
}