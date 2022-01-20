#pragma once

#include <Core/FileFormats/ELF/ElfDefines.h>

/* How to extract and insert information held in the symbol Info field.  */

#define ELF32_ST_BIND(val) (((unsigned char)(val)) >> 4)
#define ELF32_ST_TYPE(val) ((val)&0xf)
#define ELF32_ST_INFO(bind, type) (((bind) << 4) + ((type)&0xf))

/* Both ElfSymbol32 and ElfSymbol64 use the same one-byte symbol Info field.  */
#define ELF64_ST_BIND(val) ELF32_ST_BIND(val)
#define ELF64_ST_TYPE(val) ELF32_ST_TYPE(val)
#define ELF64_ST_INFO(bind, type) ELF32_ST_INFO((bind), (type))

/* How to extract and insert information held in the symbol Other field.  */
#define ELF32_ST_VISIBILITY(o) ((o)&0x03)

/* For ELF64 the definitions are the same.  */
#define ELF64_ST_VISIBILITY(o) ELF32_ST_VISIBILITY(o)

namespace VS
{

    enum class EElfSymbolBindingInfo : UByte;
    enum class EElfSymbolTypeInfo : UByte;
    enum class EElfSymbolVisibility : UByte;

    // Symbols
    struct ElfSymbol32
    {
        UWord Name;                 /* Symbol name (string tbl index) */
        Address32 Value;            /* Symbol value */
        UWord Size;                 /* Symbol size */
        UByte Info;                 /* Symbol type and binding */
        EElfSymbolVisibility Other; /* Symbol visibility */
        ElfSection32 SectionIndex;  /* Section index */
    };

    struct ElfSymbol64
    {
        UWord Name;                 /* Symbol name (string tbl index) */
        UByte Info;                 /* Symbol type and binding */
        EElfSymbolVisibility Other; /* Symbol visibility */
        ElfSection64 SectionIndex;  /* Section index */
        Address64 Value;            /* Symbol value */
        UDoubleWord Size;           /* Symbol size */
    };

    /* Legal values for ST_BIND subfield of st_info (symbol binding).  */
    enum class EElfSymbolBindingInfo : UByte
    {
        LOCAL = 0,       /* Local symbol */
        GLOBAL = 1,      /* Global symbol */
        WEAK = 2,        /* Weak symbol */
        NUM = 3,         /* Number of defined types.  */
        LOOS = 10,       /* Start of OS-specific */
        GNU_UNIQUE = 10, /* Unique symbol.  */
        HIOS = 12,       /* End of OS-specific */
        LOPROC = 13,     /* Start of processor-specific */
        HIPROC = 15      /* End of processor-specific */
    };

    enum class EElfSymbolTypeInfo : UByte
    {
        NOTYPE = 0,     /* Symbol type is unspecified */
        OBJECT = 1,     /* Symbol is a data object */
        FUNC = 2,       /* Symbol is a code object */
        SECTION = 3,    /* Symbol associated with a section */
        FILE = 4,       /* Symbol's name is file name */
        COMMON = 5,     /* Symbol is a common data object */
        TLS = 6,        /* Symbol is thread-local data object*/
        NUM = 7,        /* Number of defined types.  */
        LOOS = 10,      /* Start of OS-specific */
        GNU_IFUNC = 10, /* Symbol is indirect code object */
        HIOS = 12,      /* End of OS-specific */
        LOPROC = 13,    /* Start of processor-specific */
        HIPROC = 15,    /* End of processor-specific */
    };

    /* Symbol visibility specification encoded in the symbol Other field.  */
    enum class EElfSymbolVisibility : UByte
    {
        DEFAULT = 0,  /* Default symbol visibility rules */
        INTERNAL = 1, /* Processor specific hidden class */
        HIDDEN = 2,   /* Sym unavailable in other modules */
        PROTECTED = 3 /* Not preemptible, not exported */
    };

}