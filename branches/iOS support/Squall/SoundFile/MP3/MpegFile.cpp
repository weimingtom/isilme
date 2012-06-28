//-----------------------------------------------------------------------------
//	����� ��� ������ � ������� Mp3 ������
//	�������� ��������� ��������� �����
//	�������		: AntiTank
//	�����������	: ������������ ����� (�����)
//-----------------------------------------------------------------------------
#include "MpegFile.h"

//-----------------------------------------------------------------------------
//	����������� ������
//	�� ����� :	reader_ptr	- ��������� �� �������������� ������ �����
//	�� ������ :	*
//-----------------------------------------------------------------------------
CMpegFile::CMpegFile(CReader* reader_ptr)
	: CAbstractSoundFile()
{
	// ��������� ��� ������������� ���� ������ ������
	struct ID3Header {
		char Tag[3];		// ��������� "ID3"
		BYTE VerHi;		// ����� ������ ������� �����
		BYTE VerLow;		// ����� ������ ������� �����
		BYTE Flags;		// �����
		BYTE Size[4];	// �������������� ������ ���������
	};

	BYTE temp[256];
	DWORD start_pos;
	DWORD end_pos;

	reader = reader_ptr;			// ��������� �� ������ �����

	start_pos = 0;
	end_pos = reader->get_size();

	// �������� ������� ���� ������ ������
	reader->seek(start_pos);
	if (reader->read(&temp, sizeof(temp)) != sizeof(temp))
		return;

	// �������� ������� ���� ������ ������
	if (!memcmp(((ID3Header *) temp)->Tag, "ID3", 3)) {
		start_pos += (((ID3Header *) temp)->Size[3] & 0x7F) |
			((((ID3Header *) temp)->Size[2] & 0x7F) << 7) |
			((((ID3Header *) temp)->Size[1] & 0x7F) << 14) |
			((((ID3Header *) temp)->Size[0] & 0x7F) << 21);
		start_pos += 10;
	}

	// ������� � ������ �����
	reader->seek(start_pos);
	if (reader->read(&temp, sizeof(temp)) != sizeof(temp))
		return;

	// ������ ������ ���� ������� �������
	while (1) {
		DWORD i = 0;
		// ����� ����� ?
		if (reader->eof())
			break;

		// ����� �������
		for (i = 0; i < sizeof(temp); i ++) {
			if ((temp[i] == 0xFF) && ((temp[i + 1] & 0xF0) == 0xF0)) {
				break;
			} else {
				if ((temp[i] == 0xFF) && ((temp[i + 1] & 0xF0) == 0xE0))
					break;
			}
		}
		if (i == sizeof(temp)) {
			start_pos += sizeof(temp) - 1;
			reader->seek(start_pos);
			reader->read(temp, sizeof(temp));
		} else {
			start_pos += i;
			break;
		}
	}

	// �������� ������� ���� ������ ������
	reader->seek(end_pos - 128);
	reader->read(temp, 3);
	if (!memcmp(temp, "TAG", 3))
		end_pos -= 128;

	// ������� � ������ �����
	reader->seek(start_pos);

	start_position = start_pos;						// ��������� ������� � �����
	end_position = end_pos;							// �������� ������� � �����

	cur_position = 0;								// ���������� ������� �������
	size = end_position - start_position;	// ������ ���������� ������
}

//-----------------------------------------------------------------------------
//	���������� ������
//	�� ����� :	*
//	�� ������ :	*
//-----------------------------------------------------------------------------
CMpegFile::~CMpegFile()
{
}
