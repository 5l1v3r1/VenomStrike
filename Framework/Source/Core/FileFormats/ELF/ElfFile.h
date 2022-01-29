#pragma once
#include <variant>
#include <unordered_map>

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
        void LoadSections();

    private:
        ElfHeader32 ElfHeader;

        std::vector<ElfProgramHeader32> ProgramHeaders;
        std::unordered_map<std::string, ElfSectionHeader32> Sections;


        Address32 MainFunction;
    };

    class ElfFile64 : public ElfFilePrototype
    {
    public:
        ElfFile64(const std::string& Filepath);
        const ElfHeader64& GetElfHeader() const { return ElfHeader; }

    private:
        bool CheckElf(); // Returns true if we really have an ELF binary.
        Address64 FindMainFunction();
        void LoadSections();

    private:
        ElfHeader64 ElfHeader;

        std::vector<ElfProgramHeader64> ProgramHeaders;
        std::unordered_map<std::string, ElfSectionHeader64> Sections;

        Address64 MainFunction;
    };
}