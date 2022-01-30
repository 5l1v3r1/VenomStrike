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

		std::vector<UByte> ExtractShellcode(const ElfFile32& File);
		std::vector<UByte> ExtractShellcode(const ElfFile64& File);
	private:
		ZydisDecoder Decoder;
	};
}