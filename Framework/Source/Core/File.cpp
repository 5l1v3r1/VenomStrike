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

	std::vector<UByte> File::Read()
	{
		switch (FileType)
		{
		case EFileType::Binary:
			return ReadBinary();
		case EFileType::Text:
			return ReadText();
		}
	}

	std::vector<UByte> File::Read(size_t Bytes)
	{
		switch (FileType)
		{
		case EFileType::Binary:
			return ReadBinary(Bytes);
		case EFileType::Text:
			return ReadText(Bytes);
		}
	}

	std::vector<UByte> File::Read(size_t From, size_t Bytes)
	{
		switch (FileType)
		{
		case EFileType::Binary:
			return ReadBinary(From, Bytes);
		case EFileType::Text:
			return ReadText(From, Bytes);
		}
	}

	Offset64 File::Find(size_t From, const std::vector<UByte>& Pattern)
	{
		switch (FileType)
		{
		case EFileType::Binary:
			return FindBinary(From, Pattern);
		case EFileType::Text:
			return FindText(From, Pattern);
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

	std::vector<UByte> File::ReadBinary(size_t From, size_t Bytes)
	{
		FileStream.open(FilePath, std::ios::in | std::ios::binary);

		FileStream.clear();
		FileStream.seekg(From, std::ios::beg);

		if (!FileStream.is_open())
		{
			throw std::runtime_error("Failed to open file for reading: " + FilePath);
		}

		std::vector<UByte> Buffer(Bytes);

		FileStream.read(reinterpret_cast<char*>(Buffer.data()), Bytes);
		FileStream.close();

		Buffer.resize(Bytes);
		return Buffer;
	}

	std::vector<UByte> File::ReadText(size_t From, size_t Bytes)
	{
		FileStream.open(FilePath, std::ios::in);
		FileStream.clear();
		FileStream.seekg(From);

		if (!FileStream.is_open())
		{
			throw std::runtime_error("Failed to open file for reading: " + FilePath);
		}

		size_t FileSize = GetFileSize();

		std::vector<UByte> Buffer;

		FileStream.read(reinterpret_cast<char*>(Buffer.data()), Bytes);
		FileStream.close();
		Buffer.resize(Bytes);

		return Buffer;
	}

	Offset64 File::FindBinary(size_t From, const std::vector<UByte>& Pattern)
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

	Offset64 File::FindText(size_t From, const std::vector<UByte>& Pattern)
	{
		for (size_t i = 0; true; ++i)
		{
			if (Read(From + i, Pattern.size()) == Pattern)
			{
				return From + i;
			}
		}

		FileStream.close();
		return 0;
	}
}