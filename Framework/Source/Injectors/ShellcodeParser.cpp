#include "ShellcodeParser.h"

#include <algorithm>

namespace VS
{
	std::vector<std::byte> VShellcodeParser::Parse(std::vector<std::byte> RawShellcode)
	{
		auto CallInstruction = std::search(RawShellcode.begin(), RawShellcode.end(), CallBytes.begin(), CallBytes.end());
		RawShellcode.at(CallInstruction - RawShellcode.begin()) = static_cast<std::byte>(0);
		RawShellcode.at(CallInstruction - RawShellcode.begin() + 1) = static_cast<std::byte>(0);

		return RawShellcode;
	}

	void VShellcodeParser::ConvertShellcodeToRawBytes(const std::vector<unsigned char>& Input, std::vector<std::byte>& Output)
	{
		Output.reserve(Input.size());
		for (const auto& Byte : Input)
		{
			int i = 0;
			Output[i] = static_cast<std::byte>(Byte);
			++i;
		}
	}
}