#include "Commander.h"

#include <regex>
#include <algorithm>
#include <ranges>
#include <string_view>

#include <Core/Utils/StringUtils.h>

#include "Commands/Help.h"

namespace VS
{
	const std::unordered_map<std::string, std::function<std::shared_ptr<Command>(const std::vector<std::string>&)>> Commander::AvailableCommands = 
	{ {"help", Commander::MakeCommand<HelpCommand>} };

	std::shared_ptr<Command> Commander::ParseCommand(const std::string& Input)
	{
		std::string Cmd = Trim(Input);

		// Convert any tabs inside the command to spaces
		std::replace(Cmd.begin(), Cmd.end(), '\t', ' ');
		// Convert multiple spaces inside the command to just one
		std::regex r(" +");
		Cmd = std::regex_replace(Cmd, r, " ");

		size_t NumberOfArgs = std::count(Cmd.begin(), Cmd.end(), ' ');

		std::vector<std::string> Args(NumberOfArgs + 1);
		Args = std::move(Split(Cmd, " "));

		return AvailableCommands.at("help")(Args);
	}
	bool Commander::Exists(const std::string& CommandMnemonic)
	{
		return false;
	}
}