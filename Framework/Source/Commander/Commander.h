#pragma once

#include <Core/Result.h>
#include "Command.h"

namespace VS
{
	class Commander
	{
	public:
		static RResult<Command> ParseCommand(const std::string& Input);
	};
}