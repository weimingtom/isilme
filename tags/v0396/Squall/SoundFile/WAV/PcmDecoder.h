//-----------------------------------------------------------------------------
//	������ ��������� ��� ��������
//	�������� ��������� ��������� �����
//	�������		: AntiTank
//	�����������	: ������������ ����� (�����)
//-----------------------------------------------------------------------------
#ifndef _PCM_DECOMPRESSOR_H_INCLUDED_
#define _PCM_DECOMPRESSOR_H_INCLUDED_

// ���������
#include <windows.h>
#include "AbstractDecoder.h"
#include "AbstractSoundFile.h"

class CAbstractSoundFile;

//-----------------------------------------------------------------------------
// ����� ��� ������������ 8 ������� ���
//-----------------------------------------------------------------------------
class CDecompressPcm8Unsigned : public CAbstractDecompressor {
public:
	// �����������/����������
	CDecompressPcm8Unsigned(WAVEFORMATEX* pcm_format, bool& flag,
		CAbstractSoundFile* a)
		: CAbstractDecompressor(pcm_format, flag, a)
	{
		memcpy(pcm_format, a->GetFmt(), sizeof(WAVEFORMATEX));
		flag = true;
	};
	~CDecompressPcm8Unsigned()
	{
	};

	// ��������� ������ �� �������� � ���� ������
	DWORD GetMonoSamples(void* buffer, DWORD start, DWORD length, bool loop);

	// ��������� ������ �� �������� � ������ ������
	DWORD GetStereoSamples(void* buffer, DWORD start, DWORD length, bool loop);

	// ��������� ������ � ���� ������
	DWORD GetMonoMute(void* buffer, DWORD length);

	// ��������� ������ � ������ ������
	DWORD GetStereoMute(void* buffer, DWORD length);

	// ��������� ���������� ������� � �����
	DWORD GetSamplesInFile(void)
	{
		return SourceData->size / SourceData->GetFmt()->nBlockAlign;
	}

	// ��������� ���������� ���� � ����� ���� �����
	DWORD GetRealMonoDataSize(void)
	{
		return GetSamplesInFile();
	}

	// ��������� ���������� ���� � ����� ������ �����
	DWORD GetRealStereoDataSize(void)
	{
		return GetSamplesInFile() << 1;
	}
};

//-----------------------------------------------------------------------------
// ����� ��� ��������� 16 ������� ���
//-----------------------------------------------------------------------------
class CDecompressPcm16Signed : public CAbstractDecompressor {
protected:
	DWORD _channels;
	DWORD _curPosition;
public:
	// �����������/����������
	CDecompressPcm16Signed(WAVEFORMATEX* pcm_format, bool& flag,
		CAbstractSoundFile* a)
		: CAbstractDecompressor(pcm_format, flag, a)
	{
		memcpy(pcm_format, a->GetFmt(), sizeof(WAVEFORMATEX));
		_channels = a->GetFmt()->nChannels;
		_curPosition = 0;
		flag = true;
	};

	~CDecompressPcm16Signed()
	{
	};

	// ��������� ������ �� �������� � ���� ������
	DWORD GetMonoSamples(void* buffer, DWORD start, DWORD length, bool loop);

	// ��������� ������ �� �������� � ������ ������
	DWORD GetStereoSamples(void* buffer, DWORD start, DWORD length, bool loop);

	// ��������� ������ � ���� ������
	DWORD GetMonoMute(void* buffer, DWORD length);

	// ��������� ������ � ������ ������
	DWORD GetStereoMute(void* buffer, DWORD length);

	// ��������� ���������� ������� � �����
	DWORD GetSamplesInFile(void)
	{
		return SourceData->size / SourceData->GetFmt()->nBlockAlign;
	}

	// ��������� ���������� ���� � ����� ���� �����
	DWORD GetRealMonoDataSize(void)
	{
		return GetSamplesInFile() << 1;
	}

	// ��������� ���������� ���� � ����� ������ �����
	DWORD GetRealStereoDataSize(void)
	{
		return GetSamplesInFile() << 2;
	}
};

#endif