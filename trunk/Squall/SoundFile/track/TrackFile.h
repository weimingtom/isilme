//-----------------------------------------------------------------------------
//	����� ��� ������ � Ogg �������
//	�������� ��������� ��������� �����
//	�������		: AntiTank
//	�����������	: ������������ ����� (�����)
//-----------------------------------------------------------------------------
#ifndef _TRACK_FILE_H_INCLUDED_
#define _TRACK_FILE_H_INCLUDED_

// ���������
#include <windows.h>
#include <mmreg.h>
#include <mmsystem.h>

#include "Reader.h"
#include "AbstractSoundFile.h"

class CAbstractSoundFile;

//-----------------------------------------------------------------------------
// ����� ��� ������ � ������� Ogg �����
//-----------------------------------------------------------------------------
class CTrackFile : public CAbstractSoundFile {
protected:

	char fmt[256];					// ����� ��� ��������� � �������� �����

public:
	// ����������� ����������
	CTrackFile(CReader* reader);
	~CTrackFile();

	// ��������� ��������� �� ������ ������
	WAVEFORMATEX* GetFmt(void)
	{
		return (WAVEFORMATEX *) &fmt;
	}
};
#endif