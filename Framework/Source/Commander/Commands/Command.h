#pragma once

#include <string>
#include <vector>

#include <Core/Result.h>

#define HELP_MNEMONIC "help"

namespace VS
{
	class Command
	{
	public:
		Command(const std::vector<std::string>& Parameters);
		static const std::string& GetMnemonic() { return Mnemonic; }
		static constexpr uint8_t GetMinimumRequiredParams() { return MinNumberOfParameters; }
		static const std::string& GetBasicHelp() { return BasicHelp; }
		//! void should be some type of error handling
		virtual Result Execute() { return Result{ EResult::Ok }; }
	protected:
		static const std::string Mnemonic;
		// The minimum number of required parameters excluding the command name
		static constexpr uint8_t MinNumberOfParameters = 0;
		// The command's mnemonic is always the first parameter (located at index 0)
		std::vector<std::string> Parameters;

		static const std::string BasicHelp;
	};
}
