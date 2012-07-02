//-----------------------------------------------------------------------------
//	����� ��� ������ � Wav �������
//	�������� ��������� ��������� �����
//	�������		: AntiTank
//	�����������	: ������������ ����� (�����)
//-----------------------------------------------------------------------------

// ���������� �����
#include "WavFile.h"

//-----------------------------------------------------------------------------
//	����������� ������
//	�� �����	:	reader	- ��������� �������������� ���������� �����
//	�� ������	:	*
//-----------------------------------------------------------------------------
CWavFile::CWavFile(CReader* reader_ptr)
	: CAbstractSoundFile()
{
	memset(fmt, 0, sizeof(WAVEFORMATEX));
	wav_header head;
	wav_block block;
	DWORD cur_pos;

	// ������� ��������� �� �������������� ������ �����
	reader = reader_ptr;

	// ��������� ��������� �����
	reader->read(&head, sizeof(head));

	// �������� �������������� �����
	if ((head.Id1 == RIFF_ID) && (head.Id2 == WAVE_ID)) {
		// ���� ��������� � �������� � �������
		do {
			// ��������� ������ ���������
			cur_pos = reader->tell();
			reader->read(&block, sizeof(wav_block));

			// ��������� �������
			if (block.Id == FORMAT_ID) {
				if (block.Size > 256)
					return;
				reader->read(&fmt, block.Size);
			}

			// ��������� ������
			if (block.Id == DATA_ID) {
				start_position = cur_pos + sizeof(wav_block);
				end_position = start_position + block.Size;
				size = block.Size;
			}
			// ������� ��������� �� ��������� ����
			reader->seek(cur_pos + block.Size + sizeof(wav_block));
		} while (!reader->eof());

		// ������� � ������ �����
		reader->seek(start_position);
		cur_position = 0;
		return;
	}
}

//-----------------------------------------------------------------------------
//	���������� ������
//	�� �����	:	*
//	�� ������	:	*
//-----------------------------------------------------------------------------
CWavFile::~CWavFile()
{
}