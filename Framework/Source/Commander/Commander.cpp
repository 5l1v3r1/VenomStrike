#include "Commander.h"

namespace VS
{
	RResult<Command> Commander::ParseCommand(const std::string& Input)
	{
		// Trim leading and following spaces and tabs
		size_t CommandStart = Input.find_first_not_of(" \t");
		size_t CommandEnd = Input.find_last_not_of(" \t");

		std::string Cmd = Input.substr(CommandStart, CommandEnd - CommandStart + 1);



		return RResult<Command>();
	}
}