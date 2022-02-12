#pragma once

#include <string>

namespace VS
{
	enum class EResult
	{
		Ok = 0,
		GenericError = 1,
	};

	
	struct Result
	{
		const EResult Res = EResult::Ok;
		const std::string Info = "";
	};

	//! Result structure for functions with non-void return values
	template<typename T>
	struct RResult : public Result
	{
		T Val;
	};
}