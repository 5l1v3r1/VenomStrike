#pragma once

#include <string>
#include <vector>

#include <Core/Result.h>

namespace VS
{
	class Command
	{
	public:
		static const std::string& GetMnemonic() { return Mnemonic; }
		//! void should be some type of error handling
		virtual Result Execute() { return Result{ EResult::Ok }; }
	protected:
		static const std::string Mnemonic;
		static constexpr uint8_t MinNumberOfParameters = 0;
		std::vector<std::string> Parameters;
	};
}