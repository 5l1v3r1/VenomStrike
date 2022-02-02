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
		Disassembler() = delete;

		static void Init();
		static std::vector<Offset64> FindInstruction(const std::vector<UByte>& MachineCode, ZydisMnemonic Instruction);
		static bool CompareInstruction(const std::vector<UByte>& Instruction, ZydisMnemonic InstructionMnemonic);

		static std::vector<UByte> ExtractShellcode(ElfFile32& File);
		static std::vector<UByte> ExtractShellcode(ElfFile64& File);

	private:
		static ZydisDecoder Decoder;
	};
}