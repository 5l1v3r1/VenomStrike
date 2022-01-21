#pragma once

#include <Core/FileFormats/ELF/ElfDefines.h>
#include <concepts>

namespace VS
{
    enum class EElfSectionType : UWord;
    enum class EElfSectionFlags : UWord;

    //! 32-bit section header
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

    //! 64-bit section header
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

    // #define VERSIONTAGIDX(tag) (DT_VERNEEDNUM - (tag)) /* Reverse order! */ erudite shit which i am not even going to pretend i understand
    // #define ADDRTAGIDX(tag) (DT_ADDRRNGHI - (tag))     /* Reverse order! */
    //! Legal values for dynamic entry type (Type).  
    template <std::integral Arch> //! Arch must be SWord for 32-bit and SDoubleWord for 64-bit
    struct EElfDynEntryTypeProxy
    {
        enum class EElfDynEntryType : Arch
        {
            _NULL = 0,            /* Marks end of dynamic section */
            NEEDED = 1,           /* Name of needed library */
            PLTRELSZ = 2,         /* Size in bytes of PLT relocs */
            PLTGOT = 3,           /* Processor defined value */
            HASH = 4,             /* Address of symbol hash table */
            STRTAB = 5,           /* Address of string table */
            SYMTAB = 6,           /* Address of symbol table */
            RELA = 7,             /* Address of Rela relocs */
            RELASZ = 8,           /* Total size of Rela relocs */
            RELAENT = 9,          /* Size of one Rela reloc */
            STRSZ = 10,           /* Size of string table */
            SYMENT = 11,          /* Size of one symbol table entry */
            INIT = 12,            /* Address of init function */
            FINI = 13,            /* Address of termination function */
            SONAME = 14,          /* Name of shared object */
            RPATH = 15,           /* Library search path (deprecated) */
            SYMBOLIC = 16,        /* Start symbol search here */
            REL = 17,             /* Address of Rel relocs */
            RELSZ = 18,           /* Total size of Rel relocs */
            RELENT = 19,          /* Size of one Rel reloc */
            PLTREL = 20,          /* Type of reloc in PLT */
            DEBUG = 21,           /* For debugging; unspecified */
            TEXTREL = 22,         /* Reloc might modify .text */
            JMPREL = 23,          /* Address of PLT relocs */
            BIND_NOW = 24,        /* Process relocations of object */
            INIT_ARRAY = 25,      /* Array with addresses of init fct */
            FINI_ARRAY = 26,      /* Array with addresses of fini fct */
            NIT_ARRAYSZ = 27,     /* Size in bytes of DT_INIT_ARRAY */
            FINI_ARRAYSZ = 28,    /* Size in bytes of DT_FINI_ARRAY */
            RUNPATH = 29,         /* Library search path */
            FLAGS = 30,           /* Flags for the object being loaded */
            ENCODING = 32,        /* Start of encoded range */
            PREINIT_ARRAY = 32,   /* Array with addresses of preinit fct*/
            PREINIT_ARRAYSZ = 33, /* size in bytes of DT_PREINIT_ARRAY */
            SYMTAB_SHNDX = 34,    /* Address of SYMTAB_SHNDX section */
            NUM = 35,             /* Number used */
            LOOS = 0x6000000d,    /* Start of OS-specific */
            HIOS = 0x6ffff000,    /* End of OS-specific */
            LOPROC = 0x70000000,  /* Start of processor-specific */
            HIPROC = 0x7fffffff,  /* End of processor-specific */
            PROCNUM = 0x37,       /* Most used by any processor */

            /* Entries which fall between VALRNGHI & VALRNGLO use the
        Union.Value field of the ElfDynEntry structure.  This follows Sun's
        approach.  */
            VALRNGLO = 0x6ffffd00,
            GNU_PRELINKED = 0x6ffffdf5,  /* Prelinking timestamp */
            GNU_CONFLICTSZ = 0x6ffffdf6, /* Size of conflict section */
            GNU_LIBLISTSZ = 0x6ffffdf7,  /* Size of library list */
            CHECKSUM = 0x6ffffdf8,
            PLTPADSZ = 0x6ffffdf9,
            MOVEENT = 0x6ffffdfa,
            MOVESZ = 0x6ffffdfb,
            FEATURE_1 = 0x6ffffdfc, /* Feature selection (DTF_*).  */
            POSFLAG_1 = 0x6ffffdfd, /* Flags for DT_* entries, effecting
					   the following DT_* entry.  */
            SYMINSZ = 0x6ffffdfe,   /* Size of syminfo table (in bytes) */
            SYMINENT = 0x6ffffdff,  /* Entry size of syminfo */
            VALRNGHI = 0x6ffffdff,
            VALNUM = 12,

            /* Entries which fall between ADDRRNGHI & ADDRRNGLO use the
        Union.Pointer field of the ElfDynEntry structure.
        If any adjustment is made to the ELF object after it has been
        built these entries will need to be adjusted.  */
            ADDRRNGLO = 0x6ffffe00,
            GNU_HASH = 0x6ffffef5, /* GNU-style hash table.  */
            TLSDESC_PLT = 0x6ffffef6,
            TLSDESC_GOT = 0x6ffffef7,
            GNU_CONFLICT = 0x6ffffef8, /* Start of conflict section */
            GNU_LIBLIST = 0x6ffffef9,  /* Library list */
            CONFIG = 0x6ffffefa,       /* Configuration information.  */
            DEPAUDIT = 0x6ffffefb,     /* Dependency auditing.  */
            AUDIT = 0x6ffffefc,        /* Object auditing.  */
            PLTPAD = 0x6ffffefd,       /* PLT padding.  */
            MOVETAB = 0x6ffffefe,      /* Move table.  */
            SYMINFO = 0x6ffffeff,      /* Syminfo table.  */
            ADDRRNGHI = 0x6ffffeff,
            ADDRNUM = 11,

            /* The versioning entry types.  The next are defined as part of the
        GNU extension.  */
            VERSYM = 0x6ffffff0,

            RELACOUNT = 0x6ffffff9,
            RELCOUNT = 0x6ffffffa,

            /* These were chosen by Sun.  */
            FLAGS_1 = 0x6ffffffb,    /* State flags, see DF_1_* below.  */
            VERDEF = 0x6ffffffc,     /* Address of version definition
					   table */
            VERDEFNUM = 0x6ffffffd,  /* Number of version definitions */
            VERNEED = 0x6ffffffe,    /* Address of table with needed
					   versions */
            VERNEEDNUM = 0x6fffffff, /* Number of needed versions */
            VERSIONTAGNUM = 16
        };
    };
    template<std::integral Arch>
    using EElfDynEntryType = typename EElfDynEntryTypeProxy<Arch>::EElfDynEntryType;

    //! 32-bit dynamic section entry
    struct ElfDynEntry32
    {
        EElfDynEntryType<SWord> Type; // Dynamic entry type 
        union
        {
            UWord Value;       // Integer value 
            Address32 Pointer; // Address value
        } Union;
    };

    //! 64-bit dynamic section entry
    struct ElfDynEntry64
    {
        EElfDynEntryType<SDoubleWord> Type; // Dynamic entry type
        union
        {
            UDoubleWord Value; // Integer value 
            Address64 Pointer; // Address value 
        } Union;
    };

    //! Legal values for Section Type
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

    //! Section flags
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