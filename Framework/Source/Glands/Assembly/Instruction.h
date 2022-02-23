#pragma once

#include <string>
#include <vector>

#include <Core/Defines.h>
#include <Core/Utils/Enum.h>

#include <Glands/Endianness.h>
#include "Architecture.h"

namespace VS
{
	namespace ASM
	{
		VS_ENUM(EMnemonic, Enum, NOP = 1);
		VS_ENUM(EX86Mnemonic, EMnemonic, MOV = 2);
		VS_ENUM(EAMD64Mnemonic, EX86Mnemonic, RIP = 3);

		/// Platform agnostic wrapper for assembly instructions.
		class Instruction
		{
		public:
			Instruction(EEndian Endianness)
				: Endianness(Endianness)
			{}

			EEndian GetEndianness() const { return Endianness; }
			EArchitecture GetArchitecture() const { return Architecture; }
		private:
			static constexpr std::vector<UByte> Opcode = {};
			//! The instruction mnemonic.
			static constexpr EMnemonic<UWord> Mnemonic = static_cast<EMnemonic<UWord>>(EX86Mnemonic<UWord>::MOV);

			//! The raw byte representation of the entire instruction.
			std::vector<UByte> Raw;

			EEndian Endianness;
			EArchitecture Architecture;
		};
	}
}