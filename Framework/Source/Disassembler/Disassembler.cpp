#include "Disassembler.h"

#include <Zydis/Zydis.h>

namespace VS
{
    ZydisDecoder Disassembler::Decoder = {};
	void Disassembler::Init()
	{     
        ZydisDecoderInit(&Decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_ADDRESS_WIDTH_64);
	}

    // Returns all instances of an instruction given its mnemonic
    std::vector<size_t> Disassembler::FindInstruction(const std::vector<UByte>& MachineCode, ZydisMnemonic Instruction)
    {
        ZydisDecodedInstruction DecodedInstruction;
        std::vector<Offset64> Offsets;
        size_t MachineCodeSize = MachineCode.size();

        for (size_t i = 0; ZYAN_SUCCESS(ZydisDecoderDecodeBuffer(&Decoder, MachineCode.data() + i, MachineCodeSize - i, &DecodedInstruction)); i += DecodedInstruction.length)
        {
            if (DecodedInstruction.mnemonic == Instruction)
            {
                Offsets.emplace_back(i);
                continue;
            }
        }

        return Offsets; 
    }
    bool Disassembler::CompareInstruction(const std::vector<UByte>& Instruction, ZydisMnemonic InstructionMnemonic)
    {
        ZydisDecodedInstruction DecodedInstruction;
        return ZYAN_SUCCESS(ZydisDecoderDecodeBuffer(&Decoder, Instruction.data(), Instruction.size(), &DecodedInstruction)) && DecodedInstruction.mnemonic == InstructionMnemonic;
    }
    std::vector<UByte> Disassembler::ExtractShellcode(ElfFile32& File)
    {
        ElfSymbol32 MainSymbol = File.GetSymbol("main");
        

        return File.Read(MainSymbol.Value, MainSymbol.Size);
    }
    std::vector<UByte> Disassembler::ExtractShellcode(ElfFile64& File)
    {
        ElfSymbol64 MainSymbol = File.GetSymbol("main");

        return File.Read(MainSymbol.Value, MainSymbol.Size);
    }
}
