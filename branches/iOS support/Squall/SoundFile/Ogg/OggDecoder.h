//-----------------------------------------------------------------------------
//	����� �������� Ogg
//	�������� ��������� ��������� �����
//	�������		: AntiTank
//	�����������	: ������������ ����� (�����)
//-----------------------------------------------------------------------------
#ifndef _OGG_DECOMPRESSOR_H_INCLUDED_
#define _OGG_DECOMPRESSOR_H_INCLUDED_

// ���������
#include "AbstractDecoder.h"
#include "AbstractSoundFile.h"
#include "vorbisfile.h"

class CAbstractSoundFile;

#define SAMPLES_IN_TEMP_BUFFER 1024

//-----------------------------------------------------------------------------
//	����� �������� Ogg
//-----------------------------------------------------------------------------
class CDecompressOgg : public CAbstractDecompressor {
protected:
	OggVorbis_File* _vf;
	void* _tempBuffer;
	int _tempBufferSize;

	int GetSamples(void* buffer, int remaining, int out_channels);

public:
	// �����������/����������
	CDecompressOgg(WAVEFORMATEX* pcm_format, bool& flag, CAbstractSoundFile* a);
	~CDecompressOgg();

	// ��������� ������ �� �������� � ���� ������
	DWORD GetMonoSamples(void* buffer, DWORD start, DWORD length, bool loop);

	// ��������� ������ �� �������� � ������ ������
	DWORD GetStereoSamples(void* buffer, DWORD start, DWORD length, bool loop);

	// ��������� ������ � ���� ������
	DWORD GetMonoMute(void* buffer, DWORD length);

	// ��������� ������ � ������ ������
	DWORD GetStereoMute(void* buffer, DWORD length);

	// ��������� ���������� ������� � �����
	DWORD GetSamplesInFile(void);

	// ��������� ���������� ���� � ����� ���� �����
	DWORD GetRealMonoDataSize(void);

	// ��������� ���������� ���� � ����� ������ �����
	DWORD GetRealStereoDataSize(void);
};

#endif