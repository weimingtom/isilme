//-----------------------------------------------------------------------------
//	����� ��� ������ � ������� Mp3 ������
//	�������� ��������� ��������� Argentum
//	����������� : ������������ �����
//-----------------------------------------------------------------------------
#include "WmaFile.h"

//-----------------------------------------------------------------------------
//	����������� ������
//	�� ����� :	reader_ptr	- ��������� �� �������������� ������ �����
//	�� ������ :	*
//-----------------------------------------------------------------------------
CWmaFile::CWmaFile(CReader* reader_ptr)
	: CAbstractSoundFile()
{
	reader = reader_ptr;			// ��������� �� ������ �����
	start_position = 0;					// �������� � ����� �� ������ ������ �����
	end_position = reader->get_size();	// �������� � ����� �� ����� �����
	cur_position = 0;					// ������� ������� � �����
	size = reader->get_size();	// ��������� ������� �����
}

//-----------------------------------------------------------------------------
//	���������� ������
//	�� ����� :	*
//	�� ������ :	*
//-----------------------------------------------------------------------------
CWmaFile::~CWmaFile()
{
}