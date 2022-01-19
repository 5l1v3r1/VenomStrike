#pragma once

#include <elf.h>
#include <Defines.h>

/* Type of file offsets.  */
using ElfOffset32 = UWord;
using ElfOffset64 = UDoubleWord;

/* Type for section indices, which are 16-bit quantities.  */
using ElfSection32 = UHalfWord;
using ElfSection64 = UHalfWord;

/* Type for version symbol information.  */
using ElfVersym32 = UHalfWord;
using ElfVersym64 = UHalfWord;

#ifdef __linux__
#include <elf.h> // include proper macros
#else
#include "ElfMacros.h" // include macro definitions from elf.h when elf.h is not present
#endif

enum class EElfType : UHalfWord;
enum class EElfArch : UHalfWord;
enum class EElfSectionType : UWord;

// Elf Headers
struct ElfHeader32
{
    UByte	    ElfIdentifier[EI_NIDENT];	/* Magic number and other info */
    EElfType	Type;			            /* Object file type */
    EElfArch	Arch;		                /* Architecture */
    EElfVersion	Version;		            /* Object file version */
    Address32	EntryPoint;		            /* Entry point virtual address */
    ElfOffset32	ProgramHeaderTableOffset;	/* Program header table file offset */
    ElfOffset32	SectionHeaderTableOffset;	/* Section header table file offset */
    UWord	    Flags;		                /* Processor-specific flags */
    UHalfWord	Size;		                /* ELF header size in bytes */
    UHalfWord	ProgramHeaderSize;		    /* Program header table entry size */
    UHalfWord	ProgramHeaderCount;		    /* Program header table entry count */
    UHalfWord	SectionHeaderSize;		    /* Section header table entry size */
    UHalfWord	SectionHeaderCount;		    /* Section header table entry count */
    UHalfWord	StringTableIndex;		    /* Section header string table index */
};

struct ElfHeader64
{
    UByte	    ElfIdentifier[EI_NIDENT];	/* Magic number and other info */
    EElfType	Type;			            /* Object file type */
    EElfArch	Arch;		                /* Architecture */
    EElfVersion	Version;		            /* Object file version */
    Address64	EntryPoint;		            /* Entry point virtual address */
    ElfOffset64	ProgramHeaderTableOffset;	/* Program header table file offset */
    ElfOffset64	SectionHeaderTableOffset;	/* Section header table file offset */
    UWord	    Flags;		                /* Processor-specific flags */
    UHalfWord	Size;		                /* ELF header size in bytes */
    UHalfWord	ProgramHeaderSize;		    /* Program header table entry size */
    UHalfWord	ProgramHeaderCount;		    /* Program header table entry count */
    UHalfWord	SectionHeaderSize;		    /* Section header table entry size */
    UHalfWord	SectionHeaderCount;		    /* Section header table entry count */
    UHalfWord	StringTableIndex;		    /* Section header string table index */
};

struct ElfSectionHeader32
{
    UWord	            SectionName;		/* Section name (string tbl index) */
    EElfSectionType	    SectionType;		/* Section type */
    UWord	            SectionFlags;		/* Section flags */
    Address32	        SectionAddress;		/* Section virtual addr at execution */
    ElfOffset32	        SectionOffset;		/* Section file offset */
    UWord	            SectionSize;		/* Section size in bytes */
    UWord	            SectionLink;		    /* Link to another section */
    UWord	            SectionInfo;		/* Additional section information */
    UWord	            SectionAlignment;	/* Section alignment */
    UWord	            EntrySize;		    /* Entry size if section holds table */
};

struct ElfSectionHeader64
{
    UWord	            SectionName;		/* Section name (string tbl index) */
    EElfSectionType	    SectionType;		/* Section type */
    UWord	            SectionFlags;		/* Section flags */
    Address64	        SectionAddress;		/* Section virtual addr at execution */
    ElfOffset64	        SectionOffset;		/* Section file offset */
    UWord	            SectionSize;		/* Section size in bytes */
    UWord	            SectionLink;		/* Link to another section */
    UWord	            SectionInfo;		/* Additional section information */
    UWord	            SectionAlignment;	/* Section alignment */
    UWord	            EntrySize;		    /* Entry size if section holds table */
};


/* Legal values for ELF Type (object file type).  */
enum class EElfType : UHalfWord
{
    NONE = 0,           // No file type
    REL = 1,            // Relocatable file
    EXEC = 2,           // Executable file
    DYN = 3,            // Shared object file
    CORE = 4,           // Core file
    NUM = 5,            // Number of defined types
    LOOS = 0xfe00,      // OS-specific range start
    HIOS = 0xfeff,      // OS-specific range end
    LOPROC = 0xff00,    // Processor-specific range start
    HIPROC = 0xffff     // Processor-specific range end
};

/* Legal values for ELF Arch (architecture).  */
enum class EElfArch : UHalfWord
{
    NONE	      = 0,	    /* No machine */
    M32		      = 1,	    /* AT&T WE 32100 */
    SPARC	      = 2,	    /* SUN SPARC */
    I386		  = 3,	    /* Intel 80386 */
    M68K		  = 4,	    /* Motorola m68k family */
    M88K	      = 5,	    /* Motorola m88k family */
    IAMCU	      = 6,	    /* Intel MCU */
    I860		  = 7,	    /* Intel 80860 */
    MIPS		  = 8,	    /* MIPS R3000 big-endian */
    S370		  = 9,	    /* IBM System/370 */
    MIPS_RS3_LE	  = 10,	    /* MIPS R3000 little-endian */
				    /* reserved 11-14 */
    PARISC	      = 15,	    /* HPPA */
				    /* reserved 16 */
    VPP500	      = 17,	/* Fujitsu VPP500 */
    SPARC32PLUS	  = 18,	    /* Sun's "v8plus" */
    I960		  = 19,	    /* Intel 80960 */
    PPC		      = 20,	    /* PowerPC */
    PPC64	      = 21,	    /* PowerPC 64-bit */
    S390		  = 22,	    /* IBM S390 */
    SPU		      = 23,	    /* IBM SPU/SPC */
				     /* reserved 24-35 */
    V800		  = 36,	    /* NEC V800 series */
    FR20		  = 37,	    /* Fujitsu FR20 */
    RH32		  = 38,	    /* TRW RH-32 */
    RCE		      = 39,	    /* Motorola RCE */
    ARM		      = 40,	    /* ARM */
    FAKE_ALPHA	  = 41,	    /* Digital Alpha */
    SH		      = 42,	    /* Hitachi SH */
    SPARCV9	      = 43,	    /* SPARC v9 64-bit */
    TRICORE	      = 44,	    /* Siemens Tricore */
    ARC		      = 45,	    /* Argonaut RISC Core */
    H8_300	      = 46,	    /* Hitachi H8/300 */
    H8_300H	      = 47,	    /* Hitachi H8/300H */
    H8S		      = 48,	    /* Hitachi H8S */
    H8_500	      = 49,	    /* Hitachi H8/500 */
    IA_64	      = 50,	    /* Intel Merced */
    MIPS_X	      = 51,	    /* Stanford MIPS-X */
    COLDFIRE	  = 52,	    /* Motorola Coldfire */
    M68HC12	      = 53,	    /* Motorola M68HC12 */
    MMA		      = 54,	    /* Fujitsu MMA Multimedia Accelerator */
    PCP		      = 55,	    /* Siemens PCP */
    NCPU		  = 56,	    /* Sony nCPU embeeded RISC */
    NDR1		  = 57,	    /* Denso NDR1 microprocessor */
    STARCORE	  = 58,	    /* Motorola Start*Core processor */
    ME16		  = 59,	    /* Toyota ME16 processor */
    ST100	      = 60,	    /* STMicroelectronic ST100 processor */
    TINYJ	      = 61,	    /* Advanced Logic Corp. Tinyj emb.fam */
    X86_64	      = 62,	    /* AMD x86-64 architecture */
    PDSP		  = 63,	    /* Sony DSP Processor */
    PDP10	      = 64,	    /* Digital PDP-10 */
    PDP11	      = 65,	    /* Digital PDP-11 */
    FX66		  = 66,	    /* Siemens FX66 microcontroller */
    ST9PLUS	      = 67,	    /* STMicroelectronics ST9+ 8/16 mc */
    ST7		      = 68,	    /* STmicroelectronics ST7 8 bit mc */
    M68HC16	      = 69,	    /* Motorola MC68HC16 microcontroller */
    M68HC11	      = 70,	    /* Motorola MC68HC11 microcontroller */
    M68HC08	      = 71,	    /* Motorola MC68HC08 microcontroller */
    M68HC05	      = 72,	    /* Motorola MC68HC05 microcontroller */
    SVX		      = 73,	    /* Silicon Graphics SVx */
    ST19		  = 74,	    /* STMicroelectronics ST19 8 bit mc */
    VAX		      = 75,	    /* Digital VAX */
    CRIS		  = 76,	    /* Axis Communications 32-bit emb.proc */
    JAVELIN	      = 77,	    /* Infineon Technologies 32-bit emb.proc */
    FIREPATH	  = 78,	    /* Element 14 64-bit DSP Processor */
    ZSP		      = 79,	    /* LSI Logic 16-bit DSP Processor */
    MMIX		  = 80,	    /* Donald Knuth's educational 64-bit proc */
    HUANY	      = 81,	    /* Harvard University machine-independent object files */
    PRISM	      = 82,	    /* SiTera Prism */
    AVR		      = 83,	    /* Atmel AVR 8-bit microcontroller */
    FR30		  = 84,	    /* Fujitsu FR30 */
    D10V		  = 85,	    /* Mitsubishi D10V */
    D30V		  = 86,	    /* Mitsubishi D30V */
    V850		  = 87,	    /* NEC v850 */
    M32R		  = 88,	    /* Mitsubishi M32R */
    MN10300	      = 89,	    /* Matsushita MN10300 */
    MN10200	      = 90,	    /* Matsushita MN10200 */
    PJ		      = 91,	    /* picoJava */
    OPENRISC	  = 92,	    /* OpenRISC 32-bit embedded processor */
    ARC_COMPACT	  = 93,	    /* ARC International ARCompact */
    XTENSA	      = 94,	    /* Tensilica Xtensa Architecture */
    VIDEOCORE	  = 95,	    /* Alphamosaic VideoCore */
    TMM_GPP	      = 96,	    /* Thompson Multimedia General Purpose Proc */
    NS32K	      = 97,	    /* National Semi. 32000 */
    TPC		      = 98,	    /* Tenor Network TPC */
    SNP1K	      = 99,	    /* Trebia SNP 1000 */
    ST200	      = 100,    /* STMicroelectronics ST200 */
    IP2K		  = 101,    /* Ubicom IP2xxx */
    MAX		      = 102,    /* MAX processor */
    CR		      = 103,    /* National Semi. CompactRISC */
    F2MC16	      = 104,    /* Fujitsu F2MC16 */
    MSP430	      = 105,    /* Texas Instruments msp430 */
    BLACKFIN	  = 106,    /* Analog Devices Blackfin DSP */
    SE_C33	      = 107,    /* Seiko Epson S1C33 family */
    SEP		      = 108,    /* Sharp embedded microprocessor */
    ARCA		  = 109,    /* Arca RISC */
    UNICORE	      = 110,    /* PKU-Unity & MPRC Peking Uni. mc series */
    EXCESS	      = 111,	/* eXcess configurable cpu */
    DXP		      = 112,	/* Icera Semi. Deep Execution Processor */
    ALTERA_NIOS2  = 113,	/* Altera Nios II */
    CRX		      = 114,	/* National Semi. CompactRISC CRX */
    XGATE	      = 115,	/* Motorola XGATE */
    C166		  = 116,	/* Infineon C16x/XC16x */
    M16C		  = 117,	/* Renesas M16C */
    DSPIC30F	  = 118,	/* Microchip Technology dsPIC30F */
    CE		      = 119,	/* Freescale Communication Engine RISC */
    M32C		  = 120,	/* Renesas M32C */
				    /* reserved 121-130 */
    TSK3000	      = 131,	/* Altium TSK3000 */
    RS08		  = 132,	/* Freescale RS08 */
    SHARC	      = 133,	/* Analog Devices SHARC family */
    ECOG2	      = 134,	/* Cyan Technology eCOG2 */
    SCORE7	      = 135,	/* Sunplus S+core7 RISC */
    DSP24	      = 136,	/* New Japan Radio (NJR) 24-bit DSP */
    VIDEOCORE3	  = 137,	/* Broadcom VideoCore III */
    LATTICEMICO32 = 138,	/* RISC for Lattice FPGA */
    SE_C17	      = 139,	/* Seiko Epson C17 */
    TI_C6000	  = 140,	/* Texas Instruments TMS320C6000 DSP */
    TI_C2000	  = 141,	/* Texas Instruments TMS320C2000 DSP */
    TI_C5500	  = 142,	/* Texas Instruments TMS320C55x DSP */
    TI_ARP32	  = 143,	/* Texas Instruments App. Specific RISC */
    TI_PRU	      = 144,	/* Texas Instruments Prog. Realtime Unit */
				    /* reserved 145-159 */
    MMDSP_PLUS	  = 160,	/* STMicroelectronics 64bit VLIW DSP */
    CYPRESS_M8C	  = 161,	/* Cypress M8C */
    R32C		  = 162,	/* Renesas R32C */
    TRIMEDIA	  = 163,	/* NXP Semi. TriMedia */
    QDSP6	      = 164,	/* QUALCOMM DSP6 */
    I8051		  = 165,	/* Intel 8051 and variants */
    STXP7X	      = 166,	/* STMicroelectronics STxP7x */
    NDS32	      = 167,	/* Andes Tech. compact code emb. RISC */
    ECOG1X	      = 168,	/* Cyan Technology eCOG1X */
    MAXQ30	      = 169,	/* Dallas Semi. MAXQ30 mc */
    XIMO16	      = 170,	/* New Japan Radio (NJR) 16-bit DSP */
    MANIK	      = 171,	/* M2000 Reconfigurable RISC */
    CRAYNV2	      = 172,	/* Cray NV2 vector architecture */
    RX		      = 173,	/* Renesas RX */
    METAG	      = 174,	/* Imagination Tech. META */
    MCST_ELBRUS	  = 175,	/* MCST Elbrus */
    ECOG16	      = 176,	/* Cyan Technology eCOG16 */
    CR16		  = 177,	/* National Semi. CompactRISC CR16 */
    ETPU		  = 178,	/* Freescale Extended Time Processing Unit */
    SLE9X	      = 179,	/* Infineon Tech. SLE9X */
    L10M		  = 180,	/* Intel L10M */
    K10M		  = 181,	/* Intel K10M */
				    /* reserved 182 */
    AARCH64	      = 183,	/* ARM AARCH64 */
				    /* reserved 184 */
    AVR32	      = 185,	/* Amtel 32-bit microprocessor */
    STM8		  = 186,	/* STMicroelectronics STM8 */
    TILE64	      = 187,	/* Tilera TILE64 */
    TILEPRO	      = 188,	/* Tilera TILEPro */
    MICROBLAZE	  = 189,	/* Xilinx MicroBlaze */
    CUDA		  = 190,	/* NVIDIA CUDA */
    TILEGX	      = 191,	/* Tilera TILE-Gx */
    CLOUDSHIELD	  = 192,	/* CloudShield */
    COREA_1ST	  = 193,	/* KIPO-KAIST Core-A 1st gen. */
    COREA_2ND	  = 194,	/* KIPO-KAIST Core-A 2nd gen. */
    ARCV2	      = 195,	/* Synopsys ARCv2 ISA.  */
    OPEN8	      = 196,	/* Open8 RISC */
    RL78		  = 197,	/* Renesas RL78 */
    VIDEOCORE5	  = 198,	/* Broadcom VideoCore V */
    R78KOR	      = 199,	/* Renesas 78KOR */
    F56800EX	  = 200,	/* Freescale 56800EX DSC */
    BA1		      = 201,	/* Beyond BA1 */
    BA2		      = 202,	/* Beyond BA2 */
    XCORE	      = 203,	/* XMOS xCORE */
    MCHP_PIC	  = 204,	/* Microchip 8-bit PIC(r) */
				    /* reserved 205-209 */
    KM32		  = 210,	/* KM211 KM32 */
    KMX32	      = 211,	/* KM211 KMX32 */
    EMX16	      = 212,	/* KM211 KMX16 */
    EMX8		  = 213,	/* KM211 KMX8 */
    KVARC	      = 214,	/* KM211 KVARC */
    CDP		      = 215,	/* Paneve CDP */
    COGE		  = 216,	/* Cognitive Smart Memory Processor */
    COOL		  = 217,	/* Bluechip CoolEngine */
    NORC		  = 218,	/* Nanoradio Optimized RISC */
    CSR_KALIMBA	  = 219,	/* CSR Kalimba */
    Z80		      = 220,	/* Zilog Z80 */
    VISIUM	      = 221,	/* Controls and Data Services VISIUMcore */
    FT32		  = 222,	/* FTDI Chip FT32 */
    MOXIE	      = 223,	/* Moxie processor */
    AMDGPU	      = 224,	/* AMD GPU */
				    /* reserved 225-242 */
    RISCV	      = 243,	/* RISC-V */

    BPF		      = 247,	/* Linux BPF -- in-kernel virtual machine */
    CSKY		  = 252,     /* C-SKY */

    NUM		      = 253

};

/* Legal values for e_version (version).  */
enum class EElfVersion : UWord
{
    NONE	  = 0,		/* Invalid ELF version */
    CURRENT	  = 1,		/* Current version */
    NUM		  = 2
};

/* Legal values for Section Type (section type).  */
enum class EElfSectionType : UWord
{
    NULL	          = 0,		    /* Section header table entry unused */
    PROGBITS	      = 1,		    /* Program data */
    SYMTAB	          = 2,		    /* Symbol table */
    STRTAB	          = 3,		    /* String table */
    RELA	          = 4,		    /* Relocation entries with addends */
    HASH	          = 5,		    /* Symbol hash table */
    DYNAMIC	          = 6,		    /* Dynamic linking information */
    NOTE	          = 7,		    /* Notes */
    NOBITS	          = 8,		    /* Program space with no data (bss) */
    REL		          = 9,		    /* Relocation entries, no addends */
    SHLIB	          = 10,		    /* Reserved */
    DYNSYM	          = 11,		    /* Dynamic linker symbol table */
    INIT_ARRAY	      = 14,		    /* Array of constructors */
    FINI_ARRAY	      = 15,		    /* Array of destructors */
    PREINIT_ARRAY     = 16,		    /* Array of pre-constructors */
    GROUP	          = 17,		    /* Section group */
    SYMTAB_SHNDX      = 18,		    /* Extended section indices */
    NUM		          = 19,		    /* Number of defined types.  */
    LOOS	          = 0x60000000,	/* Start OS-specific.  */
    GNU_ATTRIBUTES    = 0x6ffffff5,	/* Object attributes.  */
    GNU_HASH	      = 0x6ffffff6,	/* GNU-style hash table.  */
    GNU_LIBLIST	      = 0x6ffffff7,	/* Prelink library list */
    CHECKSUM	      = 0x6ffffff8,	/* Checksum for DSO content.  */
    LOSUNW	          = 0x6ffffffa,	/* Sun-specific low bound.  */
    SUNW_move	      = 0x6ffffffa,
    SUNW_COMDAT       = 0x6ffffffb,
    SUNW_syminfo      = 0x6ffffffc,
    GNU_verdef	      = 0x6ffffffd,	/* Version definition section.  */
    GNU_verneed	      = 0x6ffffffe,	/* Version needs section.  */
    GNU_versym	      = 0x6fffffff,	/* Version symbol table.  */
    HISUNW	          = 0x6fffffff,	/* Sun-specific high bound.  */
    HIOS	          = 0x6fffffff,	/* End OS-specific type */
    LOPROC	          = 0x70000000,	/* Start of processor-specific */
    HIPROC	          = 0x7fffffff,	/* End of processor-specific */
    LOUSER	          = 0x80000000,	/* Start of application-specific */
    HIUSER	          = 0x8fffffff	/* End of application-specific */
};

// Section flags
enum class EElfSectionFlags : UWord
{
    WRITE	          = (1 << 0),	/* Writable */
    ALLOC	          = (1 << 1),	/* Occupies memory during execution */
    EXECINSTR	      = (1 << 2),	/* Executable */
    MERGE	          = (1 << 4),	/* Might be merged */
    STRINGS	          = (1 << 5),	/* Contains nul-terminated strings */
    INFO_LINK	      = (1 << 6),	/* `sh_info' contains SHT index */
    LINK_ORDER	      = (1 << 7),	/* Preserve order after combining */
    OS_NONCONFORMING  = (1 << 8),	/* Non-standard OS specific handling required */
    GROUP	          = (1 << 9),	/* Section is member of a group.  */
    TLS		          = (1 << 10),	/* Section hold thread-local data.  */
    COMPRESSED	      = (1 << 11),	/* Section with compressed data. */
    MASKOS	          = 0x0ff00000,	/* OS-specific.  */
    MASKPROC	      = 0xf0000000,	/* Processor-specific */
    GNU_RETAIN	      = (1 << 21),  /* Not to be GCed by linker.  */
    ORDERED	          = (1 << 30),	/* Special ordering requirement (Solaris).  */
    EXCLUDE	          = (1U << 31)	/* Section is excluded unless referenced or allocated (Solaris).*/
};

inline EElfSectionFlags operator|(EElfSectionFlags a, EElfSectionFlags b)
{
    return static_cast<EElfSectionFlags>(static_cast<UWord>(a) | static_cast<UWord>(b));
}