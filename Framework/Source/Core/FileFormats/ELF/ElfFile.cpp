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
        switch (FilePrototype.GetArch())
        {
        case EArchitecture::x86:
            return ElfFile32(FilePrototype.GetFilePath());
        case EArchitecture::x64:
            return ElfFile64(FilePrototype.GetFilePath());
        default:
            return ElfFile32(""); // Invalid, this should never be reached
        }

    }

    template<typename ElfHeaderT, typename ProgramHeaderT, typename SectionHeaderT, typename SymbolT>
    requires ElfFileC<ElfHeaderT, ProgramHeaderT, SectionHeaderT, SymbolT>
    ElfFile<ElfHeaderT, ProgramHeaderT, SectionHeaderT, SymbolT>::ElfFile(const std::string& Filepath)
        : ElfFilePrototype(Filepath)
    {
        FindMainFunction();
        std::vector<UByte> ElfHeaderBytes = Read(sizeof(ElfHeader64));
        std::memcpy(&ElfHeader, ElfHeaderBytes.data(), sizeof(ElfHeader64));

        if (!CheckElf())
        {
            // Error handling
            return;
        }

        ProgramHeaders.reserve(ElfHeader.ProgramHeaderCount);

        // Load program headers
        for (size_t i = 0; i < ElfHeader.ProgramHeaderCount; ++i)
        {
            std::vector<UByte> ProgramHeaderData = Read(ElfHeader.ProgramHeaderTableOffset + ElfHeader.ProgramHeaderSize * i, ElfHeader.ProgramHeaderSize);
            ProgramHeaders.emplace_back(*reinterpret_cast<ProgramHeaderT*>(ProgramHeaderData.data()));
        }

        LoadSections();
        LoadSymbols();
        FindMainFunction();
    }

    template<typename ElfHeaderT, typename ProgramHeaderT, typename SectionHeaderT, typename SymbolT>
    requires ElfFileC<ElfHeaderT, ProgramHeaderT, SectionHeaderT, SymbolT>
    bool ElfFile<ElfHeaderT, ProgramHeaderT, SectionHeaderT, SymbolT>::CheckElf()
    {
        for (uint8_t i = 0; i < 4; ++i)
        {
            if (ElfHeader.ElfIdentifier[i] != ElfMagic[i])
                return false;
        }
        return true;
    }

    template<typename ElfHeaderT, typename ProgramHeaderT, typename SectionHeaderT, typename SymbolT>
    requires ElfFileC<ElfHeaderT, ProgramHeaderT, SectionHeaderT, SymbolT>
    void ElfFile<ElfHeaderT, ProgramHeaderT, SectionHeaderT, SymbolT>::LoadSections()
    {
        std::vector<SectionHeaderT> SectionHeaders;
        std::vector<std::string> SectionNames;

        SectionHeaders.reserve(ElfHeader.SectionHeaderCount);
        SectionNames.reserve(ElfHeader.SectionHeaderCount);
        Sections.reserve(ElfHeader.SectionHeaderCount);

        // Load section headers
        for (size_t i = 0; i < ElfHeader.SectionHeaderCount; ++i)
        {
            std::vector<UByte> SectionHeaderData = Read(ElfHeader.SectionHeaderTableOffset + ElfHeader.SectionHeaderSize * i, ElfHeader.SectionHeaderSize);
            SectionHeaders.emplace_back(*reinterpret_cast<SectionHeaderT*>(SectionHeaderData.data()));
        }

        // Load section string table
        Offset64 StringTableStart = SectionHeaders[ElfHeader.StringTableIndex].SectionOffset;
        Offset64 StringTableEnd = Find(SectionHeaders[ElfHeader.StringTableIndex].SectionOffset + 1, { 0x0, 0x0 });
        std::unordered_map<UWord, UWord> StringTableIndices;
        StringTableIndices.reserve(ElfHeader.SectionHeaderCount);

        for (Offset64 Offset = 1; StringTableStart + Offset < StringTableEnd;)
        {
            Offset64 StringStart = SectionHeaders[ElfHeader.StringTableIndex].SectionOffset + Offset;
            Address64 StringEnd = Find(StringStart, { 0x0 });
            std::vector<UByte> SectionNameBytes = Read(StringStart, StringEnd - StringStart);

            SectionNames.emplace_back(SectionNameBytes.begin(), SectionNameBytes.end());

            StringTableIndices.insert_or_assign(Offset, SectionNames.size() - 1);
            Offset += StringEnd - StringStart + 1;
        }

        // Combine section headers with names into a map for easier access
        for (size_t i = 0; i < ElfHeader.SectionHeaderCount; ++i)
        {
            Sections.insert_or_assign(SectionNames[StringTableIndices[SectionHeaders[i].SectionName]], SectionHeaders[i]);
        }
    }

    template<typename ElfHeaderT, typename ProgramHeaderT, typename SectionHeaderT, typename SymbolT>
    requires ElfFileC<ElfHeaderT, ProgramHeaderT, SectionHeaderT, SymbolT>
    void ElfFile<ElfHeaderT, ProgramHeaderT, SectionHeaderT, SymbolT>::LoadSymbols()
    {
        // Location the symbol table
        if (Sections.find(".symtab") == Sections.end() || Sections.find(".strtab") == Sections.end())
        {
            // Logger stuff
            return;
        }

        std::vector<UByte> SymbolTableBytes = Read(Sections[".symtab"].SectionOffset, Sections[".symtab"].SectionSize);

        uint32_t SymbolCount = Sections[".symtab"].SectionSize / Sections[".symtab"].EntrySize;

        Symbols.reserve(SymbolCount);
        std::vector<std::string> SymbolNames(SymbolCount);
        std::unordered_map<UWord, UWord> StringTableIndices;
        StringTableIndices.reserve(SymbolCount);

        // Load the string section string table
        Offset64 StringTableStart = Sections[".strtab"].SectionOffset;
        Offset64 StringTableEnd = Find(Sections[".strtab"].SectionOffset + 1, { 0x0, 0x0 });

        for (Offset64 Offset = 1; StringTableStart + Offset < StringTableEnd;)
        {
            Offset64 StringStart = Sections[".strtab"].SectionOffset + Offset;
            Address64 StringEnd = Find(StringStart, { 0x0 });
            std::vector<UByte> SymbolNameBytes = Read(StringStart, StringEnd - StringStart);

            SymbolNames.emplace_back(SymbolNameBytes.begin(), SymbolNameBytes.end());

            StringTableIndices.insert_or_assign(Offset, SymbolNames.size() - 1);
            Offset += StringEnd - StringStart + 1;
        }

        for (size_t i = 0; i < SymbolCount; ++i)
        {
            Symbols.insert_or_assign(SymbolNames[StringTableIndices[reinterpret_cast<SymbolT*>(SymbolTableBytes.data() + i * Sections[".symtab"].EntrySize)->Name]], *reinterpret_cast<SymbolT*>(SymbolTableBytes.data() + i * Sections[".symtab"].EntrySize));
        }
        return;
    }

    template<typename ElfHeaderT, typename ProgramHeaderT, typename SectionHeaderT, typename SymbolT>
    requires ElfFileC<ElfHeaderT, ProgramHeaderT, SectionHeaderT, SymbolT>
    Address64 ElfFile<ElfHeaderT, ProgramHeaderT, SectionHeaderT, SymbolT>::FindMainFunction()
    {
        if (Symbols.find("main") == Symbols.end())
        {
            // Logger stuff
            return 0;
        }

        return Symbols["main"].Value;
    }
}