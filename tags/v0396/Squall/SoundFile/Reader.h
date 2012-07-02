//-----------------------------------------------------------------------------
//	����� ��� ������ � ������� ��������� ����� �� ������ ������
//	�������� ��������� ��������� �����
//	�������		: AntiTank
//	�����������	: ������������ ����� (�����)
//-----------------------------------------------------------------------------
#ifndef _CREADER_H_INCLUDED_
#define _CREADER_H_INCLUDED_

// ���������
#include "ExternFunction.h"

//-----------------------------------------------------------------------------
//	����� ��� ������ � ������� ��������� ����� �� ������ ������
//-----------------------------------------------------------------------------
class CReader {
protected:
	// �������� ������ ��� ������ � �������
	extern_open_t _open;						// ��������� �� ������� ������� �������� �����
	extern_read_t _read;						// ��������� �� ������� ������� ������ �����
	extern_seek_t _seek;						// ��������� �� ������� ������� ������ ������� � �����
	extern_close_t _close;  					 // ��������� �� ������� ������� �������� �����
	extern_malloc_t _malloc;					  // ��������� �� ������� ������� ��������� ������
	extern_free_t _free;						// ��������� �� ������� ������� ������������ ������

	void* file_ptr; 					// ��������� �� ������ �����
	char* file_name;					// ��������� �� ��� �����
	char* file_ext; 					// ��������� �� ���������� �����
	unsigned int file_size; 				   // ������ �����
	unsigned int file_type; 				   // ��� �����
	bool file_mem;  				   // ���� ��������� ������
	unsigned int file_position; 			   // ������� ������� � �����
	unsigned int file_handler;  			   // ������� �����

public:

	CReader(						 // ����������� ��� ������ � �����
	const char* file, int stream_flag, bool& init, extern_open_t ext_open,
		extern_read_t ext_read, extern_seek_t ext_seek,
		extern_close_t ext_close, extern_malloc_t ext_malloc,
		extern_free_t ext_free);

	CReader(						 // ����������� ��� ����� �� ������
	void* memory, unsigned int memory_size, int new_memory, bool& init,
		extern_malloc_t ext_malloc, extern_free_t ext_free);

	~CReader(); 					 // ����������

	void free_file_resource(			  // ���������� ���������� ������ ������
	void);

	unsigned int read(  						  // ������ ����� �� ����� �� ������� ������� ������
	void* buffer, unsigned int size);


	unsigned int peek(  						  // ������ ������ �� ����� ��� ������ ������� ������
	void* buffer, unsigned int size);

	unsigned int seek(  						  // ��������� ����� ������� � ����� ���������� ������ �����
	unsigned int new_position);

	unsigned int tell(  						  // �������� ������� � �����
	void);


	unsigned int get_size(  					  // ��������� ������� �����
	void)
	{
		return file_size;
	}


	bool eof(   						  // �������� �� ����� �����
	void)
	{
		return file_size == file_position;
	}

	char* get_file_name(				   // �������� ��������� �� ��� ������������� �����
	void)
	{
		return file_name;
	}

	char* get_file_ext( 				   // �������� ��������� �� ���������� ������������� �����
	void)
	{
		return file_ext;
	}
};

#endif