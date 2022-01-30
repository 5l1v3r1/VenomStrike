#pragma once
#include <vector>

#include <Zydis/Decoder.h>

#include <Core/Defines.h>
#include <Core/FileFormats/ELF/ElfFile.h>

namespace VS
{
	class Disassembler
	{
	public:
		Disassembler();
		std::vector<Offset64> FindInstruction(const std::vector<UByte>& MachineCode, ZydisMnemonic Instruction);
		bool CompareInstruction(const std::vector<UByte>& Instruction, ZydisMnemonic InstructionMnemonic);

		std::vector<UByte> ExtractShellcode(ElfFile32& File);
		std::vector<UByte> ExtractShellcode(ElfFile64& File);
	private:
		ZydisDecoder Decoder;
	};
}