#pragma once
#include "PCH.h"

enum SoundFileFormat
{
	SFF_None = 0,
	SFF_WAV  = SF_FORMAT_WAV | SF_FORMAT_PCM_16,
};

struct AudioFileInfo
{
	std::wstring Filename = L"-";
	std::wstring Filepath = L"-";
	std::wstring Fileformat = L"-";

	bool FileOk = false;

	bool IsStereo = false;
	int SampleRate = 0;
	sf_count_t Length = 0;
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
			Metadata.channels = (int)AUDIO_CHANNELCOUNT;
			Metadata.samplerate = (int)AUDIO_SAMPLERATE;
		}
		Data = sf_open(this->FilePath.c_str(), LibsndfileOpenMode, &Metadata);
		OpenSuccess = Data ? true : false;
		this->BufferLength = BufferLength;
		ConstructFileInfo();

		if (!sf_format_check(&Metadata)) Utilities::ShowMessagebox(L"Invalid encoding" + FormatInit.ToString());
	}

	~SoundFile()
	{
		if(OpenSuccess) sf_close(Data);
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
	bool IsFileValid() { return OpenSuccess; }
};

class InSoundFile : public SoundFile
{
private:
	int CurrentPosition = 0;
public:
	InSoundFile(std::wstring FilePath) : SoundFile(FilePath, SFM_READ, 0) { }

	bool SeekFile(float ToSecond)
	{
		sf_count_t TempPosition = (sf_count_t)(ToSecond * (float)Metadata.samplerate);
		sf_count_t Success = sf_seek(Data, TempPosition, SEEK_SET);
		CurrentPosition = (int)TempPosition * Metadata.channels;
		return (Success != -1); //w przypadku b³êdu sf_seek() zwraca -1
	}

	int GetFilePosition()
	{
		return CurrentPosition / Metadata.channels;
	}

	virtual void ProcessData(float* NewData, int& Samplecount) override
	{
		bool UseDefaultCount = Samplecount <= 0;
		bool Mono = !GetFileInfo().IsStereo;
		if (Mono) Samplecount /= 2;

		Samplecount = (int)sf_read_float(Data, NewData, (!UseDefaultCount ? Samplecount : BufferLength));
		CurrentPosition += Samplecount;
		for (int i = Samplecount; i < BufferLength; ++i) NewData[i] = 0;

		if (Mono)
		{
			Samplecount *= 2;
			for (int i = Samplecount - 1; i >= 0; --i) NewData[i] = NewData[i / 2];
		}

		if (UseDefaultCount) Samplecount = BufferLength;
	}
};

class OutSoundFile : public SoundFile
{
public:
	OutSoundFile(std::wstring FilePath, SoundFileFormat FileFormat) : SoundFile(FilePath, SFM_WRITE, 0, (int)FileFormat) { }

	virtual void ProcessData(float* NewData, int& Samplecount) override
	{
		Samplecount = (int)sf_write_float(Data, NewData, Samplecount);
	}
};
