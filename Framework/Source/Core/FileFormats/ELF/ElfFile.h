#pragma once
#include <variant>
#include <unordered_map>

#include <Core/File.h>
#include "Elf.h"

namespace VS
{
    template<typename E, typename P, typename S>
    concept ElfFileC = (std::is_base_of<ElfHeader32, E>::value && std::is_base_of<ElfProgramHeader32, P>::value && std::is_base_of<ElfSectionHeader32, S>::value) 
        || (std::is_base_of<ElfHeader64, E>::value && std::is_base_of<ElfProgramHeader64, P>::value && std::is_base_of<ElfSectionHeader64, S>::value);

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

    template<typename ElfHeaderT, typename ProgramHeaderT, typename SectionHeaderT>
        requires ElfFileC<ElfHeaderT, ProgramHeaderT, SectionHeaderT>
    class ElfFile : public ElfFilePrototype
    {
    public:
        ElfFile(const std::string& Filepath);
        const ElfHeaderT& GetElfHeader() const { return ElfHeader; }
    private:
        bool CheckElf(); // Returns true if we really have an ELF binary.
        Address64 FindMainFunction() { return 0; }
        void LoadSections();

    private:
        ElfHeaderT ElfHeader;

        std::vector<ProgramHeaderT> ProgramHeaders;
        std::unordered_map<std::string, SectionHeaderT> Sections;

        Address64 MainFunction;
    };

    using ElfFile32 = ElfFile<ElfHeader32, ElfProgramHeader32, ElfSectionHeader32>;
    using ElfFile64 = ElfFile<ElfHeader64, ElfProgramHeader64, ElfSectionHeader64>;

    std::variant<ElfFile32, ElfFile64> ParseElf(const ElfFilePrototype& FilePrototype);
}