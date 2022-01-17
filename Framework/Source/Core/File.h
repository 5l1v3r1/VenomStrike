#pragma once

#include <string>
#include <fstream>
#include <filesystem>

namespace VS
{
	enum class EFileType
	{
		Binary,
		Text
	};


	class VFile
	{
	public:
		VFile(const std::string& Filepath, EFileType FileType, bool CreateIfMissing = false);
		
		inline static bool Exists(const std::string& Filepath) { return std::filesystem::exists(Filepath); }
		static std::string ParseFilename(const std::string& Filepath);
		
		std::vector<uint8_t> Read();
		size_t GetFileSize(); // returns the file size in bytes

	private:
		std::vector<uint8_t> ReadBinary();
		std::vector<uint8_t> ReadText();

	private:
		std::string Name;
		std::string Filepath;

		EFileType FileType;

		std::fstream FileStream;
	};
}