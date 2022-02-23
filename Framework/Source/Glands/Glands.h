#pragma once
#include <vector>

#include <Zydis/Decoder.h>

#include <Core/Defines.h>
#include <Core/FileFormats/ELF/ElfFile.h>

namespace VS
{
	/// A class for all things assembly and disassembly.
	/// @warning The disassembler must be initialised by the Init() function before any use.
	/// 
	class Glands
	{
	public:
		Glands() = delete;

		//! Initialises the Glands assembly engine
		static void Init();

		/// Locates all instances of the provided instruction.
		/// <param name="MachineCode"> The machine code to comb through. </param>
		/// <param name="Instruction"> The instruction to search for, will eventually be replaced by Glands' own assembly API. </param>
		/// <returns> Returns a vector of offsets from the beginning of the file where the instruction is at. </returns>
		static std::vector<Offset64> FindInstruction(const std::vector<UByte>& MachineCode, ZydisMnemonic Instruction);
		static bool CompareInstruction(const std::vector<UByte>& Instruction, ZydisMnemonic InstructionMnemonic);

		/// <summary>
		/// Generates machine code which emulates a function call to the specified address in a hyperstaging environment.
		/// </summary>
		/// <param name="Address"> The address of the function to call. </param>
		static std::vector<UByte> EmulateFunctionCall(Address64 Address);

		/// <summary>
		/// Locates the main function of an executable and extracts shellcode from it.
		/// </summary>
		/// <param name="File"> The 32-bit ELF file to extract shellcode from. </param>
		static std::vector<UByte> ExtractShellcode(ElfFile32& File);

		/// <summary>
		/// Locates the main function of an executable and extracts shellcode from it.
		/// </summary>
		/// <param name="File"> The 64-bit ELF file to extract shellcode from. </param>
		static std::vector<UByte> ExtractShellcode(ElfFile64& File);

	private:
		static ZydisDecoder Decoder;
	};

}