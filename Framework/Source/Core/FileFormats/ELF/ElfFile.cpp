#include "ElfFile.h"

#include "Elf.h"
#include <cstring>

namespace VS
{
    ElfFilePrototype::ElfFilePrototype(const std::string& Filepath)
        : File(Filepath, EFileType::Binary, false)
    {
        UByte HeaderBeginning = std::vector<UByte>(Read(4, 2))[0];

        // 32-bit
        if(HeaderBeginning == 1)
        {
            Arch = EArchitecture::x86;
        }
        else if(HeaderBeginning == 2) // 64-bit
        {
            Arch = EArchitecture::x64;
        }
    }

    std::variant<ElfFile32, ElfFile64> ParseElf(const ElfFilePrototype& FilePrototype)
    {
        switch(FilePrototype.GetArch())
        {
        case EArchitecture::x86:
            return ElfFile32(FilePrototype.GetFilePath());
        case EArchitecture::x64:
            return ElfFile64(FilePrototype.GetFilePath());
        default:
            return ElfFile32(""); // Invalid, this should never be reached
        }
    }

    // 32-bit
    ElfFile32::ElfFile32(const std::string& FilePath)
        : ElfFilePrototype(FilePath)
    {
        std::vector<UByte> ElfHeaderBytes = Read(sizeof(ElfHeader32));
        std::memcpy(&ElfHeader, ElfHeaderBytes.data(), sizeof(ElfHeader32));
        
    }

    Address32 ElfFile32::FindMainFunction()
    {
        return Address32();
    }

    // 64-bit 
    ElfFile64::ElfFile64(const std::string& FilePath)
        : ElfFilePrototype(FilePath)
    {
        std::vector<uint8_t> ElfHeaderBytes = Read(sizeof(ElfHeader64));
        std::memcpy(&ElfHeader, ElfHeaderBytes.data(), sizeof(ElfHeader64));
    }
}