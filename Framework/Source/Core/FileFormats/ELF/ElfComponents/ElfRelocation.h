#pragma once

#include <Core/FileFormats/ELF/ElfDefines.h>

namespace VS
{
    /* Relocation table entry without addend (in section of type SHT_REL).  */
    struct ElfRel32
    {
        Address32 Offset; /* Address */
        UWord Info;       /* Relocation type and symbol index */
    };

    /* I have seen two different definitions of the Elf64_Rel and
   Elf64_Rela structures, so we'll leave them out until Novell (or
   whoever) gets their act together.  */
    /* The following, at least, is used on Sparc v9, MIPS, and Alpha.  */

    struct ElfRel64
    {
        Address64 Offset; /* Address */
        UDoubleWord Info; /* Relocation type and symbol index */
    };

    /* Relocation table entry with addend (in section of type SHT_RELA).  */

    struct ElfRela32
    {
        Address32 Offset; /* Address */
        UWord Info;       /* Relocation type and symbol index */
        SWord Addend;     /* Addend */
    };

    struct ElfRela64
    {
        Address64 Offset;   /* Address */
        UDoubleWord Info;   /* Relocation type and symbol index */
        SDoubleWord Addend; /* Addend */
    };

    enum class EElfI386RelocationType : UWord
    {
        I386_NONE = 0,     /* No reloc */
        I386_32 = 1,       /* Direct 32 bit  */
        I386_PC32 = 2,     /* PC relative 32 bit */
        I386_GOT32 = 3,    /* 32 bit GOT entry */
        I386_PLT32 = 4,    /* 32 bit PLT address */
        I386_COPY = 5,     /* Copy symbol at runtime */
        I386_GLOB_DAT = 6, /* Create GOT entry */
        I386_JMP_SLOT = 7, /* Create PLT entry */
        I386_RELATIVE = 8, /* Adjust by program base */
        I386_GOTOFF = 9,   /* 32 bit offset to GOT */
        I386_GOTPC = 10,   /* 32 bit PC relative offset to GOT */
        I386_32PLT = 11,
        I386_TLS_TPOFF = 14, /* Offset in static TLS block */
        I386_TLS_IE = 15,    /* Address of GOT entry for static TLS block offset */
        I386_TLS_GOTIE = 16, /* GOT entry for static TLS block offset */
        I386_TLS_LE = 17,    /* Offset relative to static TLS block */
        I386_TLS_GD = 18,    /* Direct 32 bit for GNU version of general dynamic thread local data */
        I386_TLS_LDM = 19,   /* Direct 32 bit for GNU version of local dynamic thread local data in LE code */
        I386_16 = 20,
        I386_PC16 = 21,
        I386_8 = 22,
        I386_PC8 = 23,
        I386_TLS_GD_32 = 24,     /* Direct 32 bit for general dynamic thread local data */
        I386_TLS_GD_PUSH = 25,   /* Tag for pushl in GD TLS code */
        I386_TLS_GD_CALL = 26,   /* Relocation for call to __tls_get_addr() */
        I386_TLS_GD_POP = 27,    /* Tag for popl in GD TLS code */
        I386_TLS_LDM_32 = 28,    /* Direct 32 bit for local dynamic thread local data in LE code */
        I386_TLS_LDM_PUSH = 29,  /* Tag for pushl in LDM TLS code */
        I386_TLS_LDM_CALL = 30,  /* Relocation for call to __tls_get_addr() in LDM code */
        I386_TLS_LDM_POP = 31,   /* Tag for popl in LDM TLS code */
        I386_TLS_LDO_32 = 32,    /* Offset relative to TLS block */
        I386_TLS_IE_32 = 33,     /* GOT entry for negated static TLS block offset */
        I386_TLS_LE_32 = 34,     /* Negated offset relative to static TLS block */
        I386_TLS_DTPMOD32 = 35,  /* ID of module containing symbol */
        I386_TLS_DTPOFF32 = 36,  /* Offset in TLS block */
        I386_TLS_TPOFF32 = 37,   /* Negated offset in static TLS block */
        I386_SIZE32 = 38,        /* 32-bit symbol size */
        I386_TLS_GOTDESC = 39,   /* GOT offset for TLS descriptor.  */
        I386_TLS_DESC_CALL = 40, /* Marker of call through TLS descriptor for relaxation.  */
        I386_TLS_DESC = 41,      /* TLS descriptor containing pointer to code and to argument, returning the TLS offset for the symbol.  */
        I386_IRELATIVE = 42,     /* Adjust indirectly by program base */
        I386_GOT32X = 43,        // Load from 32 bit GOT entry, relaxable. 
                                 /* Keep this the last entry.  */
        I386_NUM = 44,
    };

    
}
/* How to extract and insert information held in the Info field.  */

#define ELF32_R_SYM(val) ((val) >> 8)
#define ELF32_R_TYPE(val) ((val)&0xff)
#define ELF32_R_INFO(sym, type) (((sym) << 8) + ((type)&0xff))

#define ELF64_R_SYM(i) ((i) >> 32)
#define ELF64_R_TYPE(i) ((i)&0xffffffff)
#define ELF64_R_INFO(sym, type) ((((Elf64_Xword)(sym)) << 32) + (type))
