#pragma once
#include "PCH.h"

enum SoundFileFormat
{
	SFF_None = 0,
	SFF_WAV  = SF_FORMAT_WAV | SF_FORMAT_PCM_16,
	SFF_OGG  = SF_FORMAT_OGG,
	SFF_RAW  = SF_FORMAT_RAW | SF_FORMAT_FLOAT
};

struct AudioFileInfo
{
	std::wstring Filename = L"-";
	std::wstring Filepath = L"-";
	std::wstring Fileformat = L"-";

	bool FileOk = false;

	bool IsStereo = false;
	int SampleRate = 0;
	int Length = 0;
};

class SoundFile
{
private:
	const std::string FilePath;
	bool OpenSuccess;
	const int LibsndfileOpenMode;
	AudioFileInfo FileInfo;

protected:
	SNDFILE* Data;
	SF_INFO Metadata;
	int BufferLength;

	SoundFile(std::wstring FilePath, int OpenMode, int BufferLength, int FormatInit = 0)
		: FilePath(Utilities::MultibyteCharFromWide(FilePath)),
		LibsndfileOpenMode(OpenMode)
	{
		if (FormatInit)
		{
			Metadata.format = FormatInit;
			Metadata.channels = AUDIO_CHANNELCOUNT;
			Metadata.samplerate = AUDIO_SAMPLERATE;
		}
		Data = sf_open(this->FilePath.c_str(), LibsndfileOpenMode, &Metadata);
		OpenSuccess = Data ? true : false;
		this->BufferLength = BufferLength;
		ConstructFileInfo();

		if (!sf_format_check(&Metadata)) System::Windows::Forms::MessageBox::Show(L"Invalid encoding" + FormatInit.ToString());
	}

	~SoundFile()
	{
		sf_close(Data);
	}

	void ConstructFileInfo()
	{
		FileInfo.FileOk = OpenSuccess;
		if (OpenSuccess)
		{
			int Split = FilePath.find_last_of('\\');
			std::wstring WideFilePath = Utilities::WideFromMultibyteCharArray(FilePath.c_str());

			FileInfo.Filename = std::wstring(FilePath.begin() + Split, FilePath.end());
			FileInfo.Filepath = std::wstring(FilePath.begin(), FilePath.begin() + Split);

			FileInfo.IsStereo = Metadata.channels > 1 ? true : false;
			FileInfo.SampleRate = Metadata.samplerate;
			FileInfo.Length = Metadata.frames;
		}
	}

public:
	virtual void ProcessData(float* NewData, int& Samplecount) = 0;
	const AudioFileInfo& GetFileInfo() { return FileInfo; }
};

class InSoundFile : public SoundFile
{
private:
	int CurrentPosition = 0;
public:
	InSoundFile(std::wstring FilePath) : SoundFile(FilePath, SFM_READ, 0) { }

	bool SeekFile(float ToSecond)
	{
		int TempPosition = ToSecond * Metadata.samplerate;
		int Success = sf_seek(Data, TempPosition, SEEK_SET);
		CurrentPosition = TempPosition * Metadata.channels;
		return (Success != -1); //w przypadku b³êdu sf_seek() zwraca -1
	}

	int GetFilePosition()
	{
		return CurrentPosition / Metadata.channels;
	}

	virtual void ProcessData(float* NewData, int& Samplecount) override
	{
		Samplecount = sf_read_float(Data, NewData, Samplecount > 0 ? Samplecount : BufferLength);
		CurrentPosition += Samplecount;
		for (int i = Samplecount; i < BufferLength; ++i) NewData[i] = 0;
		Samplecount = BufferLength;

		if (!GetFileInfo().IsStereo)
			for (int i = Samplecount - 1; i >= 0; --i) NewData[i] = NewData[i / 2];
	}
};

class OutSoundFile : public SoundFile
{
public:
	OutSoundFile(std::wstring FilePath, SoundFileFormat FileFormat) : SoundFile(FilePath, SFM_WRITE, 0, (int)FileFormat) { }

	virtual void ProcessData(float* NewData, int& Samplecount) override
	{
		Samplecount = sf_write_float(Data, NewData, Samplecount);
	}
};

class FileIoManager
{
private:
	FileIoManager* Instance = nullptr;
	FileIoManager() { }
	~FileIoManager() { }

public:
	FileIoManager* GetInstance()
	{
		if (!Instance) Instance = new FileIoManager();
		return Instance;
	}

	bool OpenFileForRead(std::wstring InPath)
	{

	}
};
