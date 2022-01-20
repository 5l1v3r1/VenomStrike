#pragma once

#include <Core/FileFormats/ELF/ElfDefines.h>

namespace VS
{
    enum class EElfSectionType : UWord;
    enum class EElfSectionFlags : UWord;

    // Section Headers
    struct ElfSectionHeader32
    {
        UWord SectionName;             /* Section name (string tbl index) */
        EElfSectionType SectionType;   /* Section type */
        EElfSectionFlags SectionFlags; /* Section flags */
        Address32 SectionAddress;      /* Section virtual addr at execution */
        ElfOffset32 SectionOffset;     /* Section file offset */
        UWord SectionSize;             /* Section size in bytes */
        UWord SectionLink;             /* Link to another section */
        UWord SectionInfo;             /* Additional section information */
        UWord SectionAlignment;        /* Section alignment */
        UWord EntrySize;               /* Entry size if section holds table */
    };

    struct ElfSectionHeader64
    {
        UWord SectionName;             /* Section name (string tbl index) */
        EElfSectionType SectionType;   /* Section type */
        EElfSectionFlags SectionFlags; /* Section flags */
        Address64 SectionAddress;      /* Section virtual addr at execution */
        ElfOffset64 SectionOffset;     /* Section file offset */
        UWord SectionSize;             /* Section size in bytes */
        UWord SectionLink;             /* Link to another section */
        UWord SectionInfo;             /* Additional section information */
        UWord SectionAlignment;        /* Section alignment */
        UWord EntrySize;               /* Entry size if section holds table */
    };

    /* Legal values for Section Type (section type).  */
    enum class EElfSectionType : UWord
    {
        _NULL = 0,                   /* Section header table entry unused */
        PROGBITS = 1,                /* Program data */
        SYMTAB = 2,                  /* Symbol table */
        STRTAB = 3,                  /* String table */
        RELA = 4,                    /* Relocation entries with addends */
        HASH = 5,                    /* Symbol hash table */
        DYNAMIC = 6,                 /* Dynamic linking information */
        NOTE = 7,                    /* Notes */
        NOBITS = 8,                  /* Program space with no data (bss) */
        REL = 9,                     /* Relocation entries, no addends */
        SHLIB = 10,                  /* Reserved */
        DYNSYM = 11,                 /* Dynamic linker symbol table */
        INIT_ARRAY = 14,             /* Array of constructors */
        FINI_ARRAY = 15,             /* Array of destructors */
        PREINIT_ARRAY = 16,          /* Array of pre-constructors */
        GROUP = 17,                  /* Section group */
        SYMTAB_SHNDX = 18,           /* Extended section indices */
        NUM = 19,                    /* Number of defined types.  */
        LOOS = 0x60000000,           /* Start OS-specific.  */
        GNU_ATTRIBUTES = 0x6ffffff5, /* Object attributes.  */
        GNU_HASH = 0x6ffffff6,       /* GNU-style hash table.  */
        GNU_LIBLIST = 0x6ffffff7,    /* Prelink library list */
        CHECKSUM = 0x6ffffff8,       /* Checksum for DSO content.  */
        LOSUNW = 0x6ffffffa,         /* Sun-specific low bound.  */
        SUNW_move = 0x6ffffffa,
        SUNW_COMDAT = 0x6ffffffb,
        SUNW_syminfo = 0x6ffffffc,
        GNU_verdef = 0x6ffffffd,  /* Version definition section.  */
        GNU_verneed = 0x6ffffffe, /* Version needs section.  */
        GNU_versym = 0x6fffffff,  /* Version symbol table.  */
        HISUNW = 0x6fffffff,      /* Sun-specific high bound.  */
        HIOS = 0x6fffffff,        /* End OS-specific type */
        LOPROC = 0x70000000,      /* Start of processor-specific */
        HIPROC = 0x7fffffff,      /* End of processor-specific */
        LOUSER = 0x80000000,      /* Start of application-specific */
        HIUSER = 0x8fffffff       /* End of application-specific */
    };

    // Section flags
    enum class EElfSectionFlags : UWord
    {
        WRITE = (1 << 0),            /* Writable */
        ALLOC = (1 << 1),            /* Occupies memory during execution */
        EXECINSTR = (1 << 2),        /* Executable */
        MERGE = (1 << 4),            /* Might be merged */
        STRINGS = (1 << 5),          /* Contains nul-terminated strings */
        INFO_LINK = (1 << 6),        /* `sh_info' contains SHT index */
        LINK_ORDER = (1 << 7),       /* Preserve order after combining */
        OS_NONCONFORMING = (1 << 8), /* Non-standard OS specific handling required */
        GROUP = (1 << 9),            /* Section is member of a group.  */
        TLS = (1 << 10),             /* Section hold thread-local data.  */
        COMPRESSED = (1 << 11),      /* Section with compressed data. */
        MASKOS = 0x0ff00000,         /* OS-specific.  */
        MASKPROC = 0xf0000000,       /* Processor-specific */
        GNU_RETAIN = (1 << 21),      /* Not to be GCed by linker.  */
        ORDERED = (1 << 30),         /* Special ordering requirement (Solaris).  */
        EXCLUDE = (1U << 31)         /* Section is excluded unless referenced or allocated (Solaris).*/
    };

    inline EElfSectionFlags operator|(EElfSectionFlags a, EElfSectionFlags b)
    {
        return static_cast<EElfSectionFlags>(static_cast<UWord>(a) | static_cast<UWord>(b));
    }

}