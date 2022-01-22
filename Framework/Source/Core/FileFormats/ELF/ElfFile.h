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

    //! Used solely for determining the architecture. At this point, the file may not even be a valid ELF binary.
    class ElfFilePrototype : public File
    {
    public:
        ElfFilePrototype(const std::string& Filepath);
        EArchitecture GetArch() const { return Arch; }

    protected:
        EArchitecture Arch;
    };

    class ElfFile32;
    class ElfFile64;
    std::variant<ElfFile32, ElfFile64> ParseElf(const ElfFilePrototype& FilePrototype);

    class ElfFile32 : public ElfFilePrototype
    {
    public:
        ElfFile32(const std::string& Filepath);
        const ElfHeader32& GetElfHeader() const { return ElfHeader; }
    private:
        bool CheckElf(); // Returns true if we really have an ELF binary.
        Address32 FindMainFunction();

    private:
        ElfHeader32 ElfHeader;

        std::vector<ElfProgramHeader32> ProgramHeaders;
        std::vector<ElfSectionHeader32> SectionHeaders;
    };

    class ElfFile64 : public ElfFilePrototype
    {
    public:
        ElfFile64(const std::string& Filepath);
        const ElfHeader64& GetElfHeader() const { return ElfHeader; }

    private:
        bool CheckElf(); // Returns true if we really have an ELF binary.
        Address64 FindMainFunction();
    private:
        ElfHeader64 ElfHeader;

        std::vector<ElfProgramHeader64> ProgramHeaders;
        std::vector<ElfSectionHeader64> SectionHeaders;
    };
}