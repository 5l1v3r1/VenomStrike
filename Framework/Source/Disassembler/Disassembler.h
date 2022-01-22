#pragma once
#include <vector>

#include <Zydis/Decoder.h>

#include <Core/Defines.h>

namespace VS
{
	class VDisassembler
	{
	public:
		VDisassembler();
		std::vector<Offset64> FindInstruction(const std::vector<UByte>& MachineCode, ZydisMnemonic Instruction);

	private:
		ZydisDecoder Decoder;
	};
}