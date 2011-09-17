//-----------------------------------------------------------------------------
//	����� ����������� ������ �����
//	�������� ��������� ��������� �����
//	�������		: AntiTank
//	�����������	: ������������ ����� (�����)
//-----------------------------------------------------------------------------
#ifndef _ABSTRACT_SOUND_FILE_H_INCLUDED_
#define _ABSTRACT_SOUND_FILE_H_INCLUDED_

// ���������
#include <windows.h>
#include <mmreg.h>
#include <mmsystem.h>

#include "Reader.h"

//-----------------------------------------------------------------------------
//	����� ����������� ������ �����
//-----------------------------------------------------------------------------
class CAbstractSoundFile {
protected:
	CReader* reader;			  // ��������� �� ���������� ������ ��������� �����

	DWORD start_position;      // �������� � ����� �� ������ �������� ������
	DWORD end_position; 	   // �������� � ����� �� ����� �������� ������
	DWORD cur_position; 	   // ������� ������� ���������� ������

public:
	DWORD size; 			   // ������ �������� ������

	// ����������� ����������
	CAbstractSoundFile()
	{
	};
	virtual ~CAbstractSoundFile()
	{
	};

	// ��������� ��������� �� ������ �����
	virtual WAVEFORMATEX* GetFmt(void) = 0;

	//-----------------------------------------------------------------------------
	//	��������� ������ �� ����� �� ������� ��������� � �����
	//	�� �����	:	buffer	- ��������� �� ����� ���� ������ ������
	//					length	- ���������� �������� ������, � ������
	//	�� ������	:	���������� ����������� ����
	//-----------------------------------------------------------------------------
	DWORD read(void* buffer, DWORD length)
	{
		// �������� �� ����� �� ������� �����
		if ((cur_position + length) > size)
			length = size - cur_position;

		// ������ ������
		length = reader->read(buffer, length);
		cur_position += length;
		return length;
	};

	//-----------------------------------------------------------------------------
	//	��������� ������ �� ����� ��� ������ ��������� � �����
	//	�� �����	:	buffer	- ��������� �� ����� ���� ������ ������
	//					length	- ���������� �������� ������, � ������
	//	�� ������	:	���������� ����������� ����
	//-----------------------------------------------------------------------------
	DWORD peek(void* buffer, DWORD length)
	{
		// �������� �� ����� �� ������� �����
		if ((cur_position + length) > size)
			length = size - cur_position;

		// ������ ������
		return reader->peek(buffer, length);
	};

	//-----------------------------------------------------------------------------
	//	���������� ������� ������ �� �����
	//	�� �����	:	new_position	- ����� ������� � �����
	//					type			- ��� ����� �������
	//	�� ������	:	������� ������� � �����
	//-----------------------------------------------------------------------------
	DWORD seek(DWORD new_position, DWORD type)
	{
		switch (type) {
		case FILE_BEGIN:
			cur_position = new_position;
			break;

		case FILE_CURRENT:
			cur_position += new_position;
			break;

		case FILE_END:
			cur_position = size;
			break;
		}
		// �������� �� ����� �� ������� �����
		if (cur_position > size)
			cur_position = size;

		// ��������� ����� ������� ������
		reader->seek(start_position + cur_position);
		return cur_position;
	};

	//-----------------------------------------------------------------------------
	//	�������� ������� � �����
	//	�� �����	:	*
	//	�� ������	:	������� ������� � �����
	//-----------------------------------------------------------------------------
	DWORD tell(void)
	{
		cur_position = (reader->tell() - start_position);
		return cur_position;
	};

	//-----------------------------------------------------------------------------
	//	�������� �� ����� �����
	//	�� �����	:	*
	//	�� ������	:	true	- ���� ��������
	//					false	- ���� �� ��������
	//-----------------------------------------------------------------------------
	int eof()
	{
		return cur_position == size;
	};

	//-----------------------------------------------------------------------------
	//	��������� ������� �����
	//	�� �����	:	*
	//	�� ������	:	������ �����
	//-----------------------------------------------------------------------------
	int length()
	{
		return size;
	}

	char* get_file_name(void)
	{
		return reader->get_file_name();
	}

	void free_file_resource(void)
	{
		reader->free_file_resource();
	}
};
#endif