#include "ElfFile.h"

#include "Elf.h"

namespace VS
{
    ElfFilePrototype::ElfFilePrototype(const std::string& Filepath)
        : File(Filepath, EFileType::Binary, false)
    {
        
    }

    // 32-bit
    ElfFile32::ElfFile32(const std::string& FilePath)
        : ElfFilePrototype(FilePath)
    {

    }

    // 64-bit 
    ElfFile64::ElfFile64(const std::string& FilePath)
        : ElfFilePrototype(FilePath)
    {

    }
}