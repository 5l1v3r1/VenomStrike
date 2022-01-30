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
		File(File&&) = default;
		File& operator=(File&&) = default;
		virtual ~File();
		
		inline static bool Exists(const std::string& FilePath) { return std::filesystem::exists(FilePath); }
		static std::string ParseFilename(const std::string& FilePath);
		
		//! Read a certain amount of bytes from the beginning of the file
		std::vector<UByte> Read(size_t Bytes);
		//! Read a certain amount of bytes from a specific byte in the file
		std::vector<UByte> Read(size_t From, size_t Bytes);

		//!	Find the first occurrence of the specified pattern
		Offset64 Find(size_t From, const std::vector<UByte>& Pattern);

		size_t GetFileSize(); // returns the file size in bytes

		virtual const std::string& GetFilePath() const { return FilePath; }
	private:
		

	private:
		std::string Name;
		std::string FilePath;

		EFileType FileType;

		std::fstream FileStream;
	};
}