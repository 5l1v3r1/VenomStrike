#pragma once
#include <variant>
#include <unordered_map>

#include <Core/File.h>
#include "Elf.h"

namespace VS
{
    template<typename E, typename P, typename S, typename Sm>
    concept ElfFile32C = (std::is_base_of<ElfHeader32, E>::value && std::is_base_of<ElfProgramHeader32, P>::value && std::is_base_of<ElfSectionHeader32, S>::value && std::is_base_of<ElfSymbol32, Sm>::value);
    template<typename E, typename P, typename S, typename Sm>
    concept ElfFile64C = (std::is_base_of<ElfHeader64, E>::value && std::is_base_of<ElfProgramHeader64, P>::value && std::is_base_of<ElfSectionHeader64, S>::value && std::is_base_of<ElfSymbol64, Sm>::value);

    template<typename E, typename P, typename S, typename Sm>
    concept ElfFileC = ElfFile32C<E, P, S, Sm> || ElfFile64C<E, P, S, Sm>;

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

    template<typename ElfHeaderT, typename ProgramHeaderT, typename SectionHeaderT, typename SymbolT>
    requires ElfFileC<ElfHeaderT, ProgramHeaderT, SectionHeaderT, SymbolT>
    class ElfFile : public ElfFilePrototype
    {
    public:
        ElfFile(const std::string& Filepath);
        
        const ElfHeaderT& GetElfHeader() const { return ElfHeader; }
        Address64 GetMainFunction() const { return MainFunction; }
        

    private:
        bool CheckElf(); // Returns true if we really have an ELF binary.
        
        Address64 FindMainFunction();
        
        void LoadSections();
        void LoadSymbols();
    private:
        ElfHeaderT ElfHeader;

        std::vector<ProgramHeaderT> ProgramHeaders;
        std::unordered_map<std::string, SectionHeaderT> Sections;
        std::unordered_map<std::string, SymbolT> Symbols;

        Address64 MainFunction;
    };

    using ElfFile32 = ElfFile<ElfHeader32, ElfProgramHeader32, ElfSectionHeader32, ElfSymbol32>;
    using ElfFile64 = ElfFile<ElfHeader64, ElfProgramHeader64, ElfSectionHeader64, ElfSymbol64>;

    auto ParseElf(const ElfFilePrototype& FilePrototype) -> std::variant<ElfFile32, ElfFile64>;
}