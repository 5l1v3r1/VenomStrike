#pragma once

#include <memory>
#include <unordered_map>
#include <functional>

#include <Core/Result.h>
#include "Commands/Command.h"

//! A list of indices into the AvailableCommands array
#define HELP_MNEMONIC 0

namespace VS
{
	class Commander
	{
	public:
		static RResult<std::shared_ptr<Command>> ParseCommand(const std::string& Input);
		static bool CommandExists(const std::string& CommandMnemonic);

	private:
		template<class Ret>
		requires std::is_base_of<Command, Ret>::value
		static std::shared_ptr<Command> MakeCommand(const std::vector<std::string>& Parameters)
		{
			return std::make_shared<Ret>(Parameters);
		}

	private:
		static const std::unordered_map<std::string, std::function<std::shared_ptr<Command>(const std::vector<std::string>&)>> AvailableCommands;
	};
}