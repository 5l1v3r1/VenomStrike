#pragma once

#include <string>
#include <vector>

#include <Core/Result.h>

namespace VS
{
	/// Parent class for commands.
	/// The Execute() method must be implemented in all child classes. 
	/// It has not been marked as pure virtual in order to allow general command handling through this parent class.
	class Command
	{
	public:
		Command(const std::vector<std::string>& Parameters);
		static const std::string& GetMnemonic() { return Mnemonic; }
		static constexpr uint8_t GetMinimumRequiredParams() { return MinNumberOfParameters; }
		static const std::string& GetBasicHelp() { return BasicHelp; }
		
		/// Executes the command, must be implemented in all child classes.
		/// Commands should return an error message in the Result object if their execution was unsuccessful.
		virtual Result Execute() { return Result{ EResult::CommandExecutionError, "You must use a specific instance of the Command class."}; }
		virtual Result Validate() { return Result{ EResult::CommandValidationError, "YYou must use a specific instance of the Command class." }; }
	protected:
		static const std::string Mnemonic;
		//! The minimum number of required parameters excluding the command name.
		static constexpr uint8_t MinNumberOfParameters = 0;
		//! The command's mnemonic is always the first parameter (located at index 0).
		std::vector<std::string> Parameters;
		//! A basic message that is used by the "help" command when listing all available commands.
		static const std::string BasicHelp;
	};
}
