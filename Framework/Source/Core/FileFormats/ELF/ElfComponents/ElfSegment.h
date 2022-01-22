#pragma once

#include "../ElfDefines.h"

namespace VS
{
    enum class EElfSegmentType : UWord;
    enum class EElfSegmentFlags : UWord;

    /* Program segment header.  */
    struct ElfProgramHeader32
    {
        EElfSegmentType SegmentType;      /* Segment type */
        ElfOffset32 SegmentOffset;        /* Segment file offset */
        Address32 SegmentVirtualAddress;  /* Segment virtual address */
        Address32 SegmentPhysicalAddress; /* Segment physical address */
        UWord SegmentFileSize;            /* Segment size in file */
        UWord SegmentMemorySize;          /* Segment size in memory */
        EElfSegmentFlags SegmentFlags;               /* Segment flags */
        UWord SegmentAlignment;           /* Segment alignment */
    };

    struct ElfProgramHeader64
    {
        EElfSegmentType SegmentType;      /* Segment type */
        EElfSegmentFlags SegmentFlags;               /* Segment flags */
        ElfOffset64 SegmentOffset;        /* Segment file offset */
        Address64 SegmentVirtualAddress;  /* Segment virtual address */
        Address64 SegmentPhysicalAddress; /* Segment physical address */
        UDoubleWord SegmentFileSize;      /* Segment size in file */
        UDoubleWord SegmentMemorySize;    /* Segment size in memory */
        UDoubleWord SegmentAlignment;     /* Segment alignment */
    };

    /* Legal values for the segment type.  */
    enum class EElfSegmentType : UWord
    {
        _NULL = 0,                 /* Program header table entry unused */
        LOAD = 1,                  /* Loadable program segment */
        DYNAMIC = 2,               /* Dynamic linking information */
        INTERP = 3,                /* Program interpreter */
        NOTE = 4,                  /* Auxiliary information */
        SHLIB = 5,                 /* Reserved */
        PHDR = 6,                  /* Entry for header table itself */
        TLS = 7,                   /* Thread-local storage segment */
        NUM = 8,                   /* Number of defined types */
        LOOS = 0x60000000,         /* Start of OS-specific */
        GNU_EH_FRAME = 0x6474e550, /* GCC .eh_frame_hdr segment */
        GNU_STACK = 0x6474e551,    /* Indicates stack executability */
        GNU_RELRO = 0x6474e552,    /* Read-only after relocation */
        GNU_PROPERTY = 0x6474e553, /* GNU property */
        LOSUNW = 0x6ffffffa,
        SUNWBSS = 0x6ffffffa,   /* Sun Specific segment */
        SUNWSTACK = 0x6ffffffb, /* Stack segment */
        HISUNW = 0x6fffffff,
        HIOS = 0x6fffffff,   /* End of OS-specific */
        LOPROC = 0x70000000, /* Start of processor-specific */
        HIPROC = 0x7fffffff, /* End of processor-specific */
    };

    /* Legal values for segment flags.  */
    enum class EElfSegmentFlags : UWord
    {
        X = (1 << 0),          /* Segment is executable */
        W = (1 << 1),          /* Segment is writable */
        R = (1 << 2),          /* Segment is readable */
        MASKOS = 0x0ff00000,   /* OS-specific */
        MASKPROC = 0xf0000000, /* Processor-specific */
    };

    inline EElfSegmentFlags operator|(EElfSegmentFlags a, EElfSegmentFlags b)
    {
        return static_cast<EElfSegmentFlags>(static_cast<UWord>(a) | static_cast<UWord>(b));
    }
}