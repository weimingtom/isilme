//-----------------------------------------------------------------------------
//	����� �������� WMA �������
//	�������� ��������� ��������� Argentum
//	����������� : ������������ �����
//-----------------------------------------------------------------------------
#ifndef _WMA_DECOMPRESSOR_H_INCLUDED_
#define _WMA_DECOMPRESSOR_H_INCLUDED_

// ���������
#include <windows.h>
#include <mmsystem.h>
#include <amstream.h>

#include "AbstractDecoder.h"
#include "AbstractSoundFile.h"

class CAbstractSoundFile;

//-----------------------------------------------------------------------------
//	����� �������� WMA �������
//-----------------------------------------------------------------------------
class CDecompressWma : public CAbstractDecompressor {
protected:
	IMultiMediaStream* MMStream_ptr;
	IMediaStream* MStream_ptr;
	IAudioMediaStream* AudioStream_ptr;
	IAudioData* AudioData_ptr;		// ��������� �� ������
	WORD* temp_wma_buffer;	// ������������� ��������� �����
	WAVEFORMATEX WmaFormat;			// ������ �����

public:
	// �����������/����������
	CDecompressWma(WAVEFORMATEX* pcm_format, bool& flag, CAbstractSoundFile* a);
	~CDecompressWma();

	// ��������� ���� ������ �� ��������
	DWORD GetMonoSamples(void* buffer, DWORD start, DWORD length, bool loop);

	// ��������� ������ ������ �� ��������
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