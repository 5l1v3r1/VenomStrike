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
			FileStream.open(FilePath, std::ios::in | std::ios::out | std::ios::binary);
			if (!FileStream.is_open())
			{
				throw std::runtime_error("Failed to create file: " + FilePath);
			}
		}
		else
		{
			FileStream.open(FilePath, std::ios::in | std::ios::out | std::ios::binary);
		}

		Name = ParseFilename(FilePath);
	}

	File::~File()
	{
		FileStream.close();
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

	std::vector<UByte> File::Read(size_t Bytes)
	{
		return Read(0, Bytes);
	}

	std::vector<UByte> File::Read(size_t From, size_t Bytes)
	{
		FileStream.clear();
		FileStream.seekg(From, std::ios::beg);

		if (!FileStream.is_open())
		{
			throw std::runtime_error("Failed to open file for reading: " + FilePath);
		}

		std::vector<UByte> Buffer(Bytes);

		FileStream.read(reinterpret_cast<char*>(Buffer.data()), Bytes);

		Buffer.resize(Bytes);
		return Buffer;
	}

	Offset64 File::Find(size_t From, const std::vector<UByte>& Pattern)
	{
		for (size_t i = 0; true; ++i)
		{
			std::vector<UByte> Data = Read(From + i, Pattern.size());
			if (Data == Pattern)
			{
				return From + i;
			}
		}

		return 0;
	}

	size_t File::GetFileSize()
	{
		FileStream.seekg(std::ios::end);

		size_t FileSize = FileStream.tellg();

		return FileSize;

	}

}