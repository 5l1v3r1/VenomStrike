#pragma once

#include <vector>
#include <array>
namespace VS
{
	class VShellcodeParser
	{
	public:
		static std::vector<std::byte> Parse(std::vector<std::byte> RawShellcode);
		static void ConvertShellcodeToRawBytes(const std::vector<unsigned char>& Input, std::vector<std::byte>& Output);

	public:
		static constexpr std::array<std::byte, 2> CallBytes = { static_cast<std::byte>(0xff), static_cast<std::byte>(0xd0) }; // call rax
	};
}