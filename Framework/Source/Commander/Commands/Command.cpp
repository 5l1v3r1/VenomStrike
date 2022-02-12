#include "Command.h"

namespace VS
{
	const std::string Command::Mnemonic = "";
	const std::string Command::BasicHelp = "";
	Command::Command(const std::vector<std::string>& Parameters)
		: Parameters(Parameters)
	{

	}
}