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
		//! Read a certain amount of bytes from a specific byte in the file
		std::vector<UByte> Read(size_t From, size_t Bytes);

		//!	Find the first occurrence of the specified pattern
		Offset64 Find(size_t From, const std::vector<UByte>& Pattern);

		size_t GetFileSize(); // returns the file size in bytes

		virtual const std::string& GetFilePath() const { return FilePath; }
	private:
		
		std::vector<UByte> ReadBinary(size_t From, size_t Bytes);
		std::vector<UByte> ReadText(size_t From, size_t Bytes);
		Offset64 FindBinary(size_t From, const std::vector<UByte>& Pattern);
		Offset64 FindText(size_t From, const std::vector<UByte>& Pattern);

		inline std::vector<UByte> ReadBinary(size_t Bytes)
		{
			return ReadBinary(0, Bytes);
		}
		inline std::vector<UByte> ReadText(size_t Bytes)
		{
			return ReadText(0, Bytes);
		}

		inline std::vector<UByte> ReadBinary() 
		{
			size_t FileSize = GetFileSize();
			return ReadBinary(FileSize);
		}
		inline std::vector<UByte> ReadText()
		{
			size_t FileSize = GetFileSize();
			return ReadText(FileSize);
		}
		

	private:
		std::string Name;
		std::string FilePath;

		EFileType FileType;

		std::fstream FileStream;
	};
}