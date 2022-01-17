#pragma once

#include <vector>
#include <array>
#include <cstdint>

namespace VS
{
	class VShellcodeParser
	{
	public:
		static std::vector<uint8_t> Parse(std::vector<uint8_t> RawShellcode);

	public:
		static constexpr std::array<uint8_t, 2> CallBytes = { 0xff, 0xd0 }; // call rax
	};
}