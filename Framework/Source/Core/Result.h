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

	// Result structure for functions that return something
	template<typename T>
	struct RResult : public Result
	{
		T Val;
	};
}