#include "Disassembler.h"

#include <Zydis/Zydis.h>

namespace VS
{
	Disassembler::Disassembler()
	{
		ZydisDecoderInit(&Decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_ADDRESS_WIDTH_64);        
        uint8_t Shellcode[] = { 0x48, 0x83, 0xec, 0x08, 0x48, 0x8d, 0x3d, 0xa9, 0x0f, 0x00, 0x00, 0x31, 0xc0, 0xff, 0xd0, 0x31, 0xc0, 0x48, 0x83, 0xc4, 0x08, 0xc3, 0x0f, 0x1f, 0x80, 0x00, 0x00, 0x00, 0x00 };

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
