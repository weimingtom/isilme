//-----------------------------------------------------------------------------
//	����� ��� ������ � Ogg �������
//	�������� ��������� ��������� �����
//	�������		: AntiTank
//	�����������	: ������������ ����� (�����)
//-----------------------------------------------------------------------------
#ifndef _OGG_FILE_H_INCLUDED_
#define _OGG_FILE_H_INCLUDED_

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
class COggFile : public CAbstractSoundFile {
protected:

	char fmt[256];					// ����� ��� ��������� � �������� �����

public:
	// ����������� ����������
	COggFile(CReader* reader);
	~COggFile();

	// ��������� ��������� �� ������ ������
	WAVEFORMATEX* GetFmt(void)
	{
		return (WAVEFORMATEX *) &fmt;
	}
};
#endif