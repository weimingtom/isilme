//-----------------------------------------------------------------------------
//	�������� ������� ������� ��� ������ � ������� � �������
//	�������� ��������� ��������� �����
//	�������		: AntiTank
//	�����������	: ������������ ����� (�����)
//-----------------------------------------------------------------------------

#ifndef _EXTERN_FUNCRION_H_INCLUDED_
#define _EXTERN_FUNCRION_H_INCLUDED_

// ��������� ������� ������� ������ ������
typedef unsigned int (__cdecl* extern_open_t)   (const char* filename);
typedef int 		 (__cdecl* extern_read_t)   (unsigned int handle,
	void* buffer, int size);
typedef int 		 (__cdecl* extern_seek_t)   (unsigned int handle,
	int position, int mode);
typedef void		 (__cdecl* extern_close_t)  (unsigned int handle);

// ��������� ������� ������� ��� ������ � �������
typedef void*(__cdecl* extern_malloc_t) (unsigned int size);
typedef void		 (__cdecl* extern_free_t)   (void* memory);

#endif
