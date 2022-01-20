#pragma once

#include "../ElfDefines.h"

namespace VS
{
    /* Relocation table entry without addend (in section of type SHT_REL).  */

    struct ElfRel32
    {
        Address32 Offset; /* Address */
        UWord Info;   /* Relocation type and symbol index */
    };

    /* I have seen two different definitions of the Elf64_Rel and
   Elf64_Rela structures, so we'll leave them out until Novell (or
   whoever) gets their act together.  */
    /* The following, at least, is used on Sparc v9, MIPS, and Alpha.  */

    struct ElfRel64
    {
        Address64 Offset; /* Address */
        UDoubleWord Info;  /* Relocation type and symbol index */
    };

    /* Relocation table entry with addend (in section of type SHT_RELA).  */

    struct ElfRela32
    {
        Address32 Offset;  /* Address */
        UWord Info;    /* Relocation type and symbol index */
        SWord Addend; /* Addend */
    };

    struct ElfRela64
    {
        Address64 Offset;   /* Address */
        UDoubleWord Info;    /* Relocation type and symbol index */
        SDoubleWord Addend; /* Addend */
    };

}
/* How to extract and insert information held in the Info field.  */

#define ELF32_R_SYM(val) ((val) >> 8)
#define ELF32_R_TYPE(val) ((val)&0xff)
#define ELF32_R_INFO(sym, type) (((sym) << 8) + ((type)&0xff))

#define ELF64_R_SYM(i) ((i) >> 32)
#define ELF64_R_TYPE(i) ((i)&0xffffffff)
#define ELF64_R_INFO(sym, type) ((((Elf64_Xword)(sym)) << 32) + (type))
