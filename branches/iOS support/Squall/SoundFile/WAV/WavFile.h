//-----------------------------------------------------------------------------
//	����� ��� ������ � Wav �������
//	�������� ��������� ��������� �����
//	�������		: AntiTank
//	�����������	: ������������ ����� (�����)
//-----------------------------------------------------------------------------
#ifndef _WAV_FILE_H_INCLUDED_
#define _WAV_FILE_H_INCLUDED_

// ���������
#include <windows.h>
#include <mmreg.h>
#include <mmsystem.h>

#include "Reader.h"
#include "AbstractSoundFile.h"

// �������������� ������
#define RIFF_ID		0x46464952			// ������������� �����
#define WAVE_ID		0x45564157			// ������������� wav �����
#define FORMAT_ID	0x20746d66			// ������������� ����� �������
#define DATA_ID		0x61746164			// ������������� ����� ������ �����

class CAbstractSoundFile;

//-----------------------------------------------------------------------------
// ����� ��� ������ � ������� Wav �����
//-----------------------------------------------------------------------------
class CWavFile : public CAbstractSoundFile {
protected:
	// ��������� ��������� �����
	struct wav_header {
		DWORD Id1;						// ������������� (������ ���� RIFF)
		DWORD Size;						// ������ �����
		DWORD Id2;						// ������������� (������ ���� WAVE)
	};

	// ��������� ����� ��������� ������
	struct wav_block {
		DWORD Id;						// ������������� �����
		DWORD Size;						// ������ �����
	};

	char fmt[256];					// ����� ��� ��������� � �������� �����

public:
	// ����������� ����������
	CWavFile(CReader* reader);
	~CWavFile();

	// ��������� ��������� �� ������ ������
	WAVEFORMATEX* GetFmt(void)
	{
		return (WAVEFORMATEX *) &fmt;
	}
};
#endif