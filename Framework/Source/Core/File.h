#pragma once

#include <string>
#include <fstream>
#include <filesystem>
#include <vector>

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
		
		std::vector<uint8_t> Read();
		size_t GetFileSize(); // returns the file size in bytes

		virtual const std::string& GetFilePath() const { return FilePath; }
	private:
		std::vector<uint8_t> ReadBinary();
		std::vector<uint8_t> ReadText();

	private:
		std::string Name;
		std::string FilePath;

		EFileType FileType;

		std::fstream FileStream;
	};
}