#pragma once

#include <Core/Defines.h>
#include <Core/Utils/Enum.h>

namespace VS
{
	namespace ASM
	{
		enum class ERegister;
		enum class EI386Register;
		enum class EAMD64Register;

		class Register
		{
		public:
			Register(ERegister Reg, UDoubleWord Value)
				: Reg(Reg), Value(Value)
			{}

			UDoubleWord GetValue()
			{

			}

		private:
			ERegister Reg;
			UDoubleWord Value;
		};

		//! Enumeration class for i386 architecture registers
		enum class EI386Register : uint8_t
		{
			_First,
			CS, //! Code Segment
			DS, //! Data Segment
			ES, //! Extra Segment
			FS, //! F Segment
			GS, //! G Segment
			SS, //! Stack Segment
			
			IP, //! Instruction pointer 16-bit 
			EIP, //! Instruction pointer 32-bit
			
			// General-purpose registers
			AL,
			AX,
			EAX,
			
			CL,
			CX,
			ECX,
			
			DL,
			DX,
			EDX,
			
			BL,
			BX,
			EBX,

			SP,
			ESP,
			
			BP,
			EBP,

			SI,
			ESI,

			DI,
			EDI,
			EFLAGS,
			_Last
		};

		//! Enumeration class for amd64 registers
		enum class EAMD64Register : uint8_t
		{
			// Inherited from EI386Register
			CS,
			DS,
			ES,
			FS,
			GS,
			SS,

			IP, 
			EIP,

			AL,
			AX,
			EAX,

			CL,
			CX,
			ECX,

			DL,
			DX,
			EDX,

			BL,
			BX,
			EBX,

			SP,
			ESP,

			BP,
			EBP,

			SI,
			ESI,

			DI,
			EDI,

			_First = EI386Register::_Last,
			// Actual AMD64 Register entries
			RAX,
			RBX,
			RCX,
			RDX,
			RSI,
			RDI,
			RBP,
			RSP,
			RIP,
			RFLAGS,
			R9,
			R10,
			R11,
			R12,
			R13,
			R14,
			R15
			_Last
		};

		enum class ERegister : uint8_t
		{
			CS = EI386Register::_First + 1,
			DS,
			ES,
			FS,
			GS,
			SS,

			IP,
			EIP,

			AL,
			AX,
			EAX,

			CL,
			CX,
			ECX,

			DL,
			DX,
			EDX,

			BL,
			BX,
			EBX,

			SP,
			ESP,

			BP,
			EBP,

			SI,
			ESI,

			DI,
			EDI,
			// Inherited from EAMD64Register
			RAX = EAMD64Register::_First + 1,
			RBX,
			RCX,
			RDX,
			RSI,
			RDI,
			RBP,
			RSP,
			RIP,
			RFLAGS,
			R9,
			R10,
			R11,
			R12,
			R13,
			R14,
			R15
		};	
	}
}