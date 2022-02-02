#pragma once

#include <string>
#include <algorithm>

namespace VS
{
	// Trim leading and following spaces and tabs
	std::string Trim(const std::string& Input)
	{
		size_t Start = Input.find_first_not_of(" \t");
		size_t End = Input.find_last_not_of(" \t");

		return Input.substr(Start, End - Start + 1);
	}

	std::vector<std::string> Split(const std::string& Input, const std::string& Delimeter)
	{
		std::vector<std::string> Res;
		for (size_t Pos = 0; Pos != std::string::npos; )
		{
			size_t DelimeterFound = Input.find(Delimeter, Pos);
			Res.emplace_back(Input, Pos, DelimeterFound - Pos);
			Pos = DelimeterFound == std::string::npos ? DelimeterFound : DelimeterFound + 1;
		}

		return Res;
	}

}