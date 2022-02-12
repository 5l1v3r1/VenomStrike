#pragma once

#include <memory>

#include <Core/Result.h>
#include "Commands/Command.h"


namespace VS
{
	class Commander
	{
	public:
		static std::shared_ptr<Command> ParseCommand(const std::string& Input);
	};
}