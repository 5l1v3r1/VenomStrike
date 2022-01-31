#include "File.h"

#include <stdexcept>

#include <Core/Log.h>

namespace VS
{
	File::File(const std::string& FilePath, EFileType FileType, bool CreateIfMissing)
		: FilePath(FilePath), FileType(FileType)
	{
		// Create the file if it doesn't exist
		if (CreateIfMissing && !Exists(FilePath))
		{
			FileStream.open(FilePath, std::ios::in | std::ios::out | std::ios::binary);
			if (!FileStream.good())
			{
				VS_LOG(error, "Failed to create file {0}!", FilePath);
			}
		}
		else
		{
			FileStream.open(FilePath, std::ios::in | std::ios::out | std::ios::binary);
			if (!FileStream.good())
			{
				VS_LOG(error, "Failed to create file {0}!", FilePath);
			}
		}

		Name = ParseFilename(FilePath);
	}

	File::~File()
	{
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

		if (!FileStream.good())
		{
			if (FileStream.eof())
			{
				VS_LOG(error, "Reached end of file while attempting to read {0} bytes from position {1} in file {2}!", Bytes, From, FilePath);
				return std::vector<UByte>();
			}
			else
			{
				VS_LOG(error, "Unknown error when trying to read {0} bytes from position {1} in file {2}!", Bytes, From, FilePath);
				return std::vector<UByte>();
			}
		}

		std::vector<UByte> Buffer(Bytes);

		FileStream.read(reinterpret_cast<char*>(Buffer.data()), Bytes);
		if (!FileStream.good())
		{
			if (FileStream.eof())
			{
				VS_LOG(error, "Reached end of file while attempting to read {0} bytes from position {1} in file {2}!", Bytes, From, FilePath);
				return std::vector<UByte>();
			}
			else
			{
				VS_LOG(error, "Unknown error when trying to read {0} bytes from position {1} in file {2}!", Bytes, From, FilePath);
				return std::vector<UByte>();
			}
		}

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