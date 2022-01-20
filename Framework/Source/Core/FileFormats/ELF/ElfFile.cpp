#include "ElfFile.h"

#include "Elf.h"

namespace VS
{
    ElfFile::ElfFile(const std::string& Filepath)
        : File(Filepath, EFileType::Binary, false)
    {
        
    }
}