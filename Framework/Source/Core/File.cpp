#include "File.h"

#include <stdexcept>

namespace VS
{
	File::File(const std::string& Filepath, EFileType FileType, bool CreateIfMissing)
		: Filepath(Filepath), FileType(FileType)
	{
		// Create the file if it doesn't exist
		if (CreateIfMissing && !Exists(Filepath))
		{
			FileStream.open(Filepath);
			if (!FileStream.is_open())
			{
				throw std::runtime_error("Failed to create file: " + Filepath);
			}
			FileStream.close();
		}

		Name = ParseFilename(Filepath);
	}

	std::string File::ParseFilename(const std::string& Filepath)
	{
		size_t LastDirectory = Filepath.find_last_of("/");

		if (LastDirectory != std::string::npos)
		{
			return Filepath.substr(LastDirectory + 1, Filepath.length() - LastDirectory);
		}

		return Filepath; // The file path contains  only the filename
	}

	std::vector<uint8_t> File::Read()
	{
		switch (FileType)
		{
		case EFileType::Binary:
			return ReadBinary();
		case EFileType::Text:
			return ReadText();
		}
	}

	size_t File::GetFileSize()
	{
		switch (FileType)
		{
		case EFileType::Text:
		{
			FileStream.open(Filepath, std::ios::ate | std::ios::in);
			if (!FileStream.is_open())
			{
				throw std::runtime_error("Failed to open file: " + Filepath);
			}

			size_t FileSize = FileStream.tellg();
			FileStream.close();

			return FileSize;
		}
		case EFileType::Binary:
		{
			FileStream.open(Filepath, std::ios::ate | std::ios::in | std::ios::binary);
			if (!FileStream.is_open())
			{
				throw std::runtime_error("Failed to open file: " + Filepath);
			}

			size_t FileSize = FileStream.tellg();
			FileStream.close();

			return FileSize;
		}
		}
	}
	std::vector<uint8_t> File::ReadBinary()
	{
		FileStream.open(Filepath, std::ios::in | std::ios::binary);

		if (!FileStream.is_open())
		{
			throw std::runtime_error("Failed to open file for reading: " + Filepath);
		}

		size_t FileSize = GetFileSize();

		std::vector<uint8_t> Buffer(FileSize);

		FileStream.read(reinterpret_cast<char*>(Buffer.data()), FileSize);
		FileStream.close();

		return Buffer;
	}
	std::vector<uint8_t> File::ReadText()
	{
		FileStream.open(Filepath, std::ios::in);

		if (!FileStream.is_open())
		{
			throw std::runtime_error("Failed to open file for reading: " + Filepath);
		}

		size_t FileSize = GetFileSize();

		std::vector<uint8_t> Buffer(FileSize);

		FileStream.read(reinterpret_cast<char*>(Buffer.data()), FileSize);
		FileStream.close();

		return Buffer;
	}
}