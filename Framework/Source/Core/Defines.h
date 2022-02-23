#pragma once

#include <cstdint>

// Memory
/* Type for an 8-bit quantity */
using UByte = uint8_t;
using SByte = int8_t;

/* Type for a 16-bit quantity.  */
using UHalfWord = uint16_t;
using SHalfWord = int16_t;

/* Types for signed and unsigned 32-bit quantities.  */
using UWord = uint32_t;
using SWord = int32_t;

/* Types for signed and unsigned 64-bit quantities.  */
using UDoubleWord = uint64_t;
using SDoubleWord = int64_t;

/* Types of addresses.  */
using Address32 = UWord;
using Address64 = UDoubleWord;

// Types of offsets;
using Offset32 = UWord;
using Offset64 = UDoubleWord;

// Functions for type information
namespace VS
{
    template <class T>
    std::underlying_type<T> ToUnderlyingType(T v)
    {
        return static_cast<std::underlying_type<T>>(v);
    }
}