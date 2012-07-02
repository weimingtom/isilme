//-----------------------------------------------------------------------------
//	����� ��� �������������� ������ � �������
//	�������� ��������� ��������� �����
//	�������		: AntiTank
//	�����������	: ������������ ����� (�����)
//-----------------------------------------------------------------------------
#include "reader.h"
#include "string.h"

//-----------------------------------------------------------------------------
//	����������� ������
//	������� �������� ������ �� ���������� �����
//	�� �����	:	file		- ��������� �� ��� ��������� �����
//					stream_flag	- ���� ���������� ��� �������� �����
//								  true	- ������� � ������
//								  false	- ���� � ��������
//					init		- ��������� �� ���������� � ������� ���������
//								  ���������� ������������� �����
//					open		- ��������� �� ������� ������� �������� �����
//					read		- ��������� �� ������� ������� ������ �� �����
//					seek		- ��������� �� ������� ������� ���������������� � �����
//					close		- ��������� �� ������� ������� �������� �����
//	�� ������	:	*
//-----------------------------------------------------------------------------
CReader::CReader(const char* file, int stream_flag, bool& init,
	extern_open_t ext_open, extern_read_t ext_read, extern_seek_t ext_seek,
	extern_close_t ext_close, extern_malloc_t ext_malloc,
	extern_free_t ext_free)
{
	unsigned int r;

	init = false;		// ������ ���
	file_handler = 0xffffffff;	// ������� �����
	file_size = 0;			// ������ �����
	file_ptr = 0;			// ��������� �� ����������� ������ �����
	file_type = 0;			// ��� �����
	file_mem = 0;			// ���� ������������ ����� � ������
	file_position = 0;			// ������� �������� � �����
	file_name = 0;			// ��������� �� ��� �����
	file_ext = 0;			// ��������� �� ���������� �����

	// ���������� ���������� �� ������� ������ ������ �����
	_open = ext_open;
	_read = ext_read;
	_seek = ext_seek;
	_close = ext_close;

	_malloc = ext_malloc;
	_free = ext_free;

	if (file == 0)
		return;

	// ��������� ������ �������
	unsigned int len = strlen(file);

	// ������� ������ ��� ��� �����
	file_name = (char *) _malloc(len + 1);

	// ������ ��� ���� �������� ?
	if (!file_name)
		return;

	// �������� ��� �����
	memcpy(file_name, file, len + 1);

	// ��������� ����������
	for (int i = strlen(file_name); i > 0; --i) {
		if (file_name[i] == 0x2e) {
			file_ext = file_name + i + 1;
			break;
		}
	}

	// �������� �����
	file_handler = _open(file);
	if (file_handler != 0xffffffff) {
		// ��������� ������ �����
		file_size = _seek(file_handler, 0, 2);
		if (file_size != 0xffffffff) {
			_seek(file_handler, 0, 0);

			// ��������� ��� �����
			if (stream_flag) {
				// ���� � ������

				// ������� ������ ��� ����
				file_ptr = (void *) _malloc(file_size);
				if (file_ptr) {
					// �������� ����� � ������
					r = _read(file_handler, file_ptr, file_size);
					if (r == file_size) {
						_close(file_handler);
						file_handler = 0xffffffff;
						init = true;
						file_type = 1;
						file_mem = true;
						return;
					}
				}
			} else {
				// ���� � �������� � �����
				init = true;
				file_type = 2;
				file_mem = false;
				return;
			}
		}
	}

	// ���� ������� ?
	if (file_handler != 0xffffffff) {
		_close(file_handler);
		file_handler = 0xffffffff;
	}

	// ������ ��� ���� �������� ?
	if (file_ptr) {
		_free(file_ptr);
		file_ptr = 0;
	}

	file_size = 0;
	file_type = 0;
}

//-----------------------------------------------------------------------------
//	����������� ������
//	������� �������� ���� �� ��������� ������
//	�� �����	:	memory		- ��������� ������ �� ��������� �������
//					memory_size	- ������ �������� ������
//					new_memory	- ���� ��������� ����� ������ ��� �������� ������
//								  true	- �������� � ����������� �������� ������
//								  false	- ������������ ��� ���������� ������
//					init		- ��������� �� ���������� � ������� ���������
//								  ���������� ������������� �����
//	�� ������	:	*
//-----------------------------------------------------------------------------
CReader::CReader(void* memory, unsigned int memory_size, int new_memory,
	bool& init, extern_malloc_t ext_malloc, extern_free_t ext_free)
{
	init = false;		// ������ ���
	file_handler = 0xffffffff;	// ������� �����
	file_size = memory_size;	// ������ �����
	file_ptr = 0;			// ��������� �� ����������� ������ �����
	file_type = 1;			// ��� �����
	file_mem = 0;			// ���� ������������ ����� � ������
	file_position = 0;			// ������� �������� � �����
	file_name = 0;			// ��������� �� ��� �����
	file_ext = 0;			// ��������� �� ���������� �����

	// ������� ������
	_malloc = ext_malloc;
	_free = ext_free;

	// �������� ���� �������� ������
	if (new_memory) {
		// � ���������� ������
		// ������� ������ ��� ����
		file_ptr = (void *) _malloc(memory_size);
		if (file_ptr) {
			// ��������� ������
			memcpy(file_ptr, memory, memory_size);
			file_mem = true;
			init = true;
			return;
		}
	} else {
		// ��� ��������� ������
		file_ptr = memory;
		file_mem = false;
		init = true;
		return;
	}

	// ������ ��� ���� �������� ?
	if (file_ptr) {
		_free(file_ptr);
		file_ptr = 0;
		file_mem = 0;
	}

	file_size = 0;
	file_type = 0;
}

//-----------------------------------------------------------------------------
//	���������� ������
//	�� �����	:	*
//	�� ������	:	*
//-----------------------------------------------------------------------------
CReader::~CReader()
{
	// ���� ������� ?
	if (file_handler != 0xffffffff) {
		_close(file_handler);
		file_handler = 0xffffffff;
	}

	// ������ ��� ���� �������� ?
	if (file_mem) {
		if (file_ptr) {
			_free(file_ptr);
			file_ptr = 0;
		}
	}

	if (file_name) {
		_free(file_name);
		file_name = 0;
	}

	file_size = 0;	// ������ �����
	file_type = 0;	// ��� �����
	file_position = 0;	// ������� �������� � �����
}

//-----------------------------------------------------------------------------
//	������������ ����������� ������ (���������� ����� AgSS)
//	�� �����	:	*
//	�� ������	:	*
//-----------------------------------------------------------------------------
void CReader::free_file_resource(void)
{
	// ���� ������� ?
	if (file_handler != 0xffffffff) {
		_close(file_handler);
		file_handler = 0xffffffff;
	}

	// ������ ��� ���� �������� ?
	if (file_mem) {
		if (file_ptr) {
			_free(file_ptr);
			file_ptr = 0;
		}
	}

	file_size = 0;	// ������ �����
	file_type = 0;	// ��� �����
	file_position = 0;	// ������� �������� � �����
}

//-----------------------------------------------------------------------------
//	�������������� ������ ������ �� ����� �� ������� ������� � �����
//	�� �����	:	buffer	- ��������� �� ����� � ������� ��������� ������
//					length	- ������ �������� ������
//	�� ������	:	���������� ����������� ������, � ������
//-----------------------------------------------------------------------------
unsigned int CReader::read(void* buffer, unsigned int length)
{
	unsigned int read_size;
	// �������� �� ����� �� ������� �����
	if (file_position > file_size)
		file_position = file_size;

	// �������� ��� ������ ������ �� ������� �� ������� �����
	if ((file_position + length) > file_size)
		length = file_size - file_position;

	// �������� ��� ���� ��� ������
	if (length) {
		// �������� ���� �����
		switch (file_type) {
			// ��������� ����� ������������ � ������
		case 1:
			// ������ �� ������
			if ((file_ptr) && (file_size)) {
				// ��������� ������ � �����
				memcpy(buffer, (char *) file_ptr + file_position, length);
				file_position += length;
				return length;
			}
			break;

			// ��������� ����� � ��������
		case 2:
			// ������ �� ������
			if ((file_handler != 0xffffffff) && (file_size)) {
				// ��������� ������ �� �����
				read_size = _read(file_handler, buffer, length);
				if (read_size == length) {
					file_position += length;
					return length;
				}
			}
			break;
		};
	}
	return 0;
}

//-----------------------------------------------------------------------------
//	�������������� ������ ������ �� ����� ��� ������ ������� � �����
//	�� �����	:	buffer	- ��������� �� ����� � ������� ��������� ������
//					length	- ������ �������� ������
//	�� ������	:	���������� ����������� ������, � ������
//-----------------------------------------------------------------------------
unsigned int CReader::peek(void* buffer, unsigned int length)
{
	unsigned int read_size;
	// �������� �� ����� �� ������� �����
	if (file_position > file_size)
		file_position = file_size;

	// �������� ��� ������ ������ �� ������� �� ������� �����
	if ((file_position + length) > file_size)
		length = file_size - file_position;

	// �������� ��� ���� ��� ������
	if (length) {
		// �������� ���� �����
		switch (file_type) {
			// ��������� ����� ������������ � ������
		case 1:
			// ������ �� ������
			if ((file_ptr) && (file_size)) {
				// ��������� ������ � �����
				memcpy(buffer, (char *) file_ptr + file_position, length);
				return length;
			}
			break;

			// ��������� ����� � ��������
		case 2:
			// ������ �� ������
			if ((file_handler != 0xffffffff) && (file_size)) {
				// ��������� ������ �� �����
				read_size = _read(file_handler, buffer, length);
				if (read_size == length) {
					if (_seek(file_handler, file_position, 0) != 0xFFFFFFFF)
						return length;
					else
						return 0;
				}
			}
			break;
		};
	}
	return 0;
}

//-----------------------------------------------------------------------------
//	��������� ������� ������ �� ����� ������������ ������ �����
//	�� �����	:	new_position	- ����� ������� ������ �� �����
//					type			- ��� ���������������� (������������ ����)
//	�� ������	:	����� �������� ������� ������ �� �����
//-----------------------------------------------------------------------------
unsigned int CReader::seek(unsigned int new_position)
{
	file_position = new_position;
	// �������� �� ����� �� ������� �����
	if (file_position > file_size)
		file_position = file_size;

	switch (file_type) {
		// ���� � ������
	case 1:
		return file_position;

		// ���� � ��������
	case 2:
		if (_seek(file_handler, file_position, 0) != 0xFFFFFFFF) {
			return file_position;
		} else {
			return -1;
		}
	}
	return -1;
}

//-----------------------------------------------------------------------------
//	��������� ������� ������� � �����
//	�� �����	:	*
//	�� ������	:	������� � �����
//-----------------------------------------------------------------------------
unsigned int CReader::tell(void)
{
	return file_position;
}