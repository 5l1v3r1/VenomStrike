#include "Application.h"

#include <vector>
#include "Injectors/ShellcodeParser.h"

#include <Zydis/Decoder.h>
#include <Zydis/Zydis.h>

namespace VS
{
	VApplication::VApplication()
	{
	}
	void VApplication::Run()
	{
		//std::vector<unsigned char> CharShellcode = { 0x48, 0x83, 0xec, 0x08, 0x48, 0x8d, 0x3d, 0xa9, 0x0f, 0x00, 0x00, 0x31, 0xc0, 0xff, 0xd0, 0x31, 0xc0, 0x48, 0x83, 0xc4, 0x08, 0xc3, 0x0f, 0x1f, 0x80, 0x00, 0x00, 0x00, 0x00 };
		//std::vector<std::byte> Shellcode;
		
		//VShellcodeParser::ConvertShellcodeToRawBytes(CharShellcode, Shellcode);

	}
}

// \x48\x83\xec\x08\x48\x8d\x3d\xa9\x0f\x00\x00\x31\xc0\xff\xd0\x31\xc0\x48\x83\xc4\x08\xc3\x0f\x1f\x80\x00\x00\x00\x00