#pragma once
#include "PCH.h"

class SoundFile
{
private:
	const std::string FilePath;
	bool OpenSuccess;
	const int LibsndfileOpenMode;

protected:
	SNDFILE* Data;
	SF_INFO Metadata;
	int BufferLength;

	SoundFile(std::string FilePath, int OpenMode, int BufferLength) : FilePath(FilePath), LibsndfileOpenMode(OpenMode)
	{
		Data = sf_open(FilePath.c_str(), LibsndfileOpenMode, &Metadata);
		OpenSuccess = Data ? true : false;
		this->BufferLength = BufferLength;
	}

	~SoundFile()
	{
		sf_close(Data);
	}

public:
	virtual void ProcessData(float* NewData, int& Samplecount) = 0;
	const SF_INFO& GetMetadata() { return Metadata; }
};

class InSoundFile : public SoundFile
{
public:
	InSoundFile(std::string FilePath) : SoundFile(FilePath, SFM_READ, 0) { }

	bool SeekFile(float ToSecond)
	{
		ToSecond *= Metadata.samplerate;
		int Success = sf_seek(Data, (int)ToSecond, SEEK_SET);
		return (Success != -1); //w przypadku b³êdu sf_seek() zwraca -1
	}

	virtual void ProcessData(float* NewData, int& Samplecount) override
	{
		Samplecount = sf_read_float(Data, NewData, Samplecount > 0 ? Samplecount : BufferLength);
		for (int i = Samplecount; i < BufferLength; ++i) NewData[i] = 0;
		Samplecount = BufferLength;
	}
};

class OutSoundFile : public SoundFile
{
public:
	OutSoundFile(std::string FilePath) : SoundFile(FilePath, SFM_WRITE, 0) { }

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
