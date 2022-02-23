#pragma once

#include <Core/Defines.h>
#include <Core/Utils/Enum.h>

namespace VS
{
	namespace ASM
	{
		class ERegister;

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

		template<typename T>
		class ERegister : public Enum<T>
		{
		public:
			enum : T
			{
				
			};
		};

		template<typename T>
		class EX86Register : public EX86Register<T>
		{
		public:
			enum : T
			{
				AX
				RAX,
				RBX,
				RCX,
				RDX,
				RSI,
				RDI,
				RBP,
				RSP,
				R8,
				R9,
				R10,
				R11,
				R12,
				R13,
				R14,
				R15,
				RFLAGS,
				RIP
			};
		};

		template<typename T>
		class EAMD64Register : public EX86Register<T>
		{
		public:
			enum : T
			{
				AX
				RAX,
				RBX,
				RCX,
				RDX,
				RSI,
				RDI,
				RBP,
				RSP,
				R8,
				R9,
				R10,
				R11,
				R12,
				R13,
				R14,
				R15,
				RFLAGS,
				RIP
			};
		};

		
	}
}