#pragma once

#include <string>
#include <fstream>
#include <filesystem>
#include <vector>

#include "Defines.h"

namespace VS
{
	enum class EFileType
	{
		Binary,
		Text
	};


	class File
	{
	public:
		File(const std::string& Filepath, EFileType FileType, bool CreateIfMissing = false);
		
		inline static bool Exists(const std::string& FilePath) { return std::filesystem::exists(FilePath); }
		static std::string ParseFilename(const std::string& FilePath);
		
		std::vector<UByte> Read();
		//! Read a certain amount of bytes from the beginning of the file
		std::vector<UByte> Read(size_t Bytes);
		size_t GetFileSize(); // returns the file size in bytes

		virtual const std::string& GetFilePath() const { return FilePath; }
	private:
		std::vector<UByte> ReadBinary();
		std::vector<UByte> ReadText();
		std::vector<UByte> ReadBinary(size_t Bytes);
		std::vector<UByte> ReadText(size_t Bytes);

	private:
		std::string Name;
		std::string FilePath;

		EFileType FileType;

		std::fstream FileStream;
	};
}