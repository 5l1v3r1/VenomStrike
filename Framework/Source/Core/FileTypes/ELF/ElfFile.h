#pragma once
#include "Core/File.h"

namespace VS
{
    class ElfFile : File
    {
    public:
        ElfFile(const std::string& Filepath);
    };
}