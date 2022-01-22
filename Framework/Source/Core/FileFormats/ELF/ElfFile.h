#pragma once
#include <variant>

#include <Core/File.h>
#include "Elf.h"

namespace VS
{
    enum class EArchitecture : UByte
    {
        x86,
        x64
    };

    class ElfFilePrototype : public File
    {
    public:
        ElfFilePrototype(const std::string& Filepath);
        EArchitecture GetArch() const { return Arch; }

    protected:
        EArchitecture Arch;
    };

    class ElfFile32 : public ElfFilePrototype
    {
    public:
        ElfFile32(const std::string& Filepath);
    };

    class ElfFile64 : public ElfFilePrototype
    {
    public:
        ElfFile64(const std::string& Filepath);
    };

    std::variant<ElfFile32, ElfFile64> ParseElf(const ElfFilePrototype& FilePrototype)
    {
        switch(FilePrototype.GetArch())
        {
        case EArchitecture::x86:
            return ElfFile32(FilePrototype.GetFilePath());
        case EArchitecture::x64:
            return ElfFile64(FilePrototype.GetFilePath());
        };
    }
}