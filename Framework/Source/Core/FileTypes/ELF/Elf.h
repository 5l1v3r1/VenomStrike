#pragma once

#include <elf.h>
#include <Defines.h>

/* Type of file offsets.  */
using ElfOffset32 = UWord;
using ElfOffset64 = UDoubleWord;

/* Type for section indices, which are 16-bit quantities.  */
using ElfSection32 = uint16_t;
using ElfSection64 = uint16_t;

/* Type for version symbol information.  */
using ElfVersym32 = UHalfWord;
using ElfVersym64 = UHalfWord;