#pragma once
#include <Zydis/Decoder.h>

#include <vector>

namespace VS
{
	class VDisassembler
	{
	public:
		VDisassembler();
		std::vector<size_t> FindInstruction(const std::vector<uint8_t>& MachineCode, ZydisMnemonic Instruction);

	private:
		ZydisDecoder Decoder;
	};
}