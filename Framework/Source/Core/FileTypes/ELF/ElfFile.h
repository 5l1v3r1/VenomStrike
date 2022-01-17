#pragma once
#include "File.h"

namespace VS
{
    class ElfFile : File
    {
    public:
        ElfFile(const std::string& Filepath);
    };
}