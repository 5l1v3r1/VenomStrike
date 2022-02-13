#pragma once

#include <string>

namespace VS
{
	enum class EResult
	{
		Ok = 0,
		GenericError = 1,
		CommandExecutionError = 2,
		CommandValidationError = 3,
		CommandNotFound = 4
	};

	
	struct Result
	{
		Result(EResult Res)
			: Res(Res)
		{ }
		Result(EResult Res, const std::string& Info)
			: Res(Res), Info(Info)
		{ }

		bool Ok() const { return Res == EResult::Ok; }
		const std::string& GetMessage() const { return Info; }

	protected:
		const EResult Res = EResult::Ok;
		const std::string Info = "";
	};

	//! Result structure for functions with non-void return values
	template<typename T>
	struct RResult : public Result
	{
		RResult(EResult Res) = delete;
		RResult(EResult Res, const std::string& Info) = delete;

		RResult(EResult Res, T Val)
			: Result(Res), Val(Val)
		{ }

		RResult(EResult Res, const std::string& Info, T Val)
			: Result(Res, Info), Val(Val)
		{ }
		
		T Val;
	};
}