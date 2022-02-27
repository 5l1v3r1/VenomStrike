#pragma once

#include <string>
#include <vector>

#include <Core/Defines.h>
#include <Core/Utils/Enum.h>

#include <Glands/Endianness.h>
#include "Architecture.h"

#include <SuperEnum/super_enum.h>

namespace VS
{
	namespace ASM
	{
		enum class EX86Mnemonic : uint16_t
		{
			_First = 0,
			NOP,

			_Last
		};

		enum class EMnemonic : uint16_t
		{
			NOP = EX86Mnemonic::NOP
		};

		/// Platform agnostic wrapper for assembly instructions.
		class Instruction
		{
		public:
			Instruction(EEndian Endianness)
				: Endianness(Endianness)
			{}

			EEndian GetEndianness() const { return Endianness; }
			EArch GetArchitecture() const { return Architecture; }
		private:
			static constexpr std::vector<UByte> Opcode = {};
			//! The instruction mnemonic.
			static const EMnemonic Mnemonic = EMnemonic::NOP;

			//! The raw byte representation of the entire instruction.
			std::vector<UByte> Raw;

			EEndian Endianness;
			EArch Architecture;
		};
	}
}