//-----------------------------------------------------------------------------
//	����� ������������ ��������
//	�������� ��������� ��������� �����
//	�������		: AntiTank
//	�����������	: ������������ ����� (�����)
//-----------------------------------------------------------------------------
#ifndef _ABSTRACT_DECOMPRESSOR_H_INCLUDED_
#define _ABSTRACT_DECOMPRESSOR_H_INCLUDED_

// ���������
#include <windows.h>
#include "AbstractSoundFile.h"

class CAbstractSoundFile;

//-----------------------------------------------------------------------------
// ����� ������������ ��������
//-----------------------------------------------------------------------------
class CAbstractDecompressor {
protected:
	// ��������� �� ������ �����
	CAbstractSoundFile* SourceData;

public:
	// �����������/����������
	CAbstractDecompressor(WAVEFORMATEX* pcm_format, bool& flag,
		CAbstractSoundFile* a)
	{
		SourceData = a;
	};

	virtual ~CAbstractDecompressor()
	{
	};

	// ��������� ������
	virtual DWORD GetMonoSamples(void* buffer, DWORD start, DWORD length,
		bool loop) = 0;
	virtual DWORD GetStereoSamples(void* buffer, DWORD start, DWORD length,
		bool loop) = 0;

	// ��������� ������
	virtual DWORD GetMonoMute(void* buffer, DWORD length) = 0;
	virtual DWORD GetStereoMute(void* buffer, DWORD length) = 0;

	// ��������� ������ ����� � �������
	virtual DWORD GetSamplesInFile(void) = 0;

	// ��������� ������ ����� � ������
	virtual DWORD GetRealMonoDataSize(void) = 0;
	virtual DWORD GetRealStereoDataSize(void) = 0;
};

#endif
