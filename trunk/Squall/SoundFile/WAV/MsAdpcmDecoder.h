//-----------------------------------------------------------------------------
//	����� �������� IMA ADPCM ������� �� MS
//	�������� ��������� ��������� �����
//	�������		: AntiTank
//	�����������	: ������������ ����� (�����)
//-----------------------------------------------------------------------------
#ifndef _MS_ADPCM_DECOMPRESSOR_H_INCLUDED_
#define _MS_ADPCM_DECOMPRESSOR_H_INCLUDED_

// ���������
#include <windows.h>
#include "AbstractDecoder.h"
#include "AbstractSoundFile.h"

class CAbstractSoundFile;

//-----------------------------------------------------------------------------
// ����� ��� IMA ADPCM ������� �� MicroSoft
//-----------------------------------------------------------------------------
class CDecompressMsAdpcm : public CAbstractDecompressor {
protected:
	struct SCoef {
		short Coef1;
		short Coef2;
	};

	// ��������� ������� ��� IMA ADPCM
	struct SMS_ADPCM_Format {
		WAVEFORMATEX fmt;					// ����������� ������
		WORD SamplesPerPacket;		// ������ ������
		WORD NumCoef;				//
	};

	DWORD _channels;							// ���������� ������� � �����
	DWORD _samplesPerPacket;					// ���������� ������� � ������
	DWORD _bytesPerPacket;					// ���������� ���� � ������
	DWORD _packetof;							// ���������� ������� � �����
	char* _packetBuffer;						// ������������� ����� ��� ������ ���������������� ������
	short* _left;								// ��������� �� ������ ������ ������
	short* _rigth;								// ��������� �� ������ ������� ������
	DWORD _curPacket;							// �������� � ����� �� ������� �����
	WORD _numCoef;
	SCoef* _coefTable;

	// ���������� ������
	DWORD DecodeMONOPacket(void);
	DWORD DecodeSTEREOPacket(void);

public:
	// �����������/����������
	CDecompressMsAdpcm(WAVEFORMATEX* pcm_format, bool& flag,
		CAbstractSoundFile* a);
	~CDecompressMsAdpcm();

	// ��������� ���� ������ �� ��������
	DWORD GetMonoSamples(void* buffer, DWORD start, DWORD length, bool loop);

	// ��������� ������ ������ �� ��������
	DWORD GetStereoSamples(void* buffer, DWORD start, DWORD length, bool loop);

	// ��������� ������ � ���� ������
	DWORD GetMonoMute(void* buffer, DWORD length);

	// ��������� ������ � ������ ������
	DWORD GetStereoMute(void* buffer, DWORD length);

	// ��������� ���������� ������� � �����
	DWORD GetSamplesInFile(void)
	{
		return _packetof * _samplesPerPacket;
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