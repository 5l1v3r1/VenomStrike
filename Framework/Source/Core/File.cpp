#include "File.h"

#include <stdexcept>

namespace VS
{
	File::File(const std::string& FilePath, EFileType FileType, bool CreateIfMissing)
		: FilePath(FilePath), FileType(FileType)
	{
		// Create the file if it doesn't exist
		if (CreateIfMissing && !Exists(FilePath))
		{
			FileStream.open(FilePath);
			if (!FileStream.is_open())
			{
				throw std::runtime_error("Failed to create file: " + FilePath);
			}
			FileStream.close();
		}

		Name = ParseFilename(FilePath);
	}

	std::string File::ParseFilename(const std::string& FilePath)
	{
		size_t LastDirectory = FilePath.find_last_of("/");

		if (LastDirectory != std::string::npos)
		{
			return FilePath.substr(LastDirectory + 1, FilePath.length() - LastDirectory);
		}

		return FilePath; // The file path contains  only the filename
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
			FileStream.open(FilePath, std::ios::ate | std::ios::in);
			if (!FileStream.is_open())
			{
				throw std::runtime_error("Failed to open file: " + FilePath);
			}

			size_t FileSize = FileStream.tellg();
			FileStream.close();

			return FileSize;
		}
		case EFileType::Binary:
		{
			FileStream.open(FilePath, std::ios::ate | std::ios::in | std::ios::binary);
			if (!FileStream.is_open())
			{
				throw std::runtime_error("Failed to open file: " + FilePath);
			}

			size_t FileSize = FileStream.tellg();
			FileStream.close();

			return FileSize;
		}
		}
	}
	std::vector<uint8_t> File::ReadBinary()
	{
		FileStream.open(FilePath, std::ios::in | std::ios::binary);

		if (!FileStream.is_open())
		{
			throw std::runtime_error("Failed to open file for reading: " + FilePath);
		}

		size_t FileSize = GetFileSize();

		std::vector<uint8_t> Buffer(FileSize);

		FileStream.read(reinterpret_cast<char*>(Buffer.data()), FileSize);
		FileStream.close();

		return Buffer;
	}
	std::vector<uint8_t> File::ReadText()
	{
		FileStream.open(FilePath, std::ios::in);

		if (!FileStream.is_open())
		{
			throw std::runtime_error("Failed to open file for reading: " + FilePath);
		}

		size_t FileSize = GetFileSize();

		std::vector<uint8_t> Buffer(FileSize);

		FileStream.read(reinterpret_cast<char*>(Buffer.data()), FileSize);
		FileStream.close();

		return Buffer;
	}
}