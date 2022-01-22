#include "Disassembler.h"

#include <Zydis/Zydis.h>

namespace VS
{
	VDisassembler::VDisassembler()
	{
		ZydisDecoderInit(&Decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_ADDRESS_WIDTH_64);
        
        uint8_t Shellcode[] = { 0x48, 0x83, 0xec, 0x08, 0x48, 0x8d, 0x3d, 0xa9, 0x0f, 0x00, 0x00, 0x31, 0xc0, 0xff, 0xd0, 0x31, 0xc0, 0x48, 0x83, 0xc4, 0x08, 0xc3, 0x0f, 0x1f, 0x80, 0x00, 0x00, 0x00, 0x00 };
        

	}

    // Returns all instances of an instruction given its mnemonic
    std::vector<size_t> VDisassembler::FindInstruction(const std::vector<UByte>& MachineCode, ZydisMnemonic Instruction)
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
}
