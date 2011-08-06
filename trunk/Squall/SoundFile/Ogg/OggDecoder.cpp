//-----------------------------------------------------------------------------
//	����� �������� Ogg �������
//	�������� ��������� ��������� �����
//	�������		: AntiTank
//	�����������	: ������������ ����� (�����)
//-----------------------------------------------------------------------------
#include "OggDecoder.h"
// ������ ������
size_t OggRead(void* ptr, size_t size, size_t nmemb, void* datasource)
{
	CAbstractSoundFile* SourceData = (CAbstractSoundFile*) datasource;

	// �������� �� ����� �����
	if (SourceData->eof())
		return 0;

	// ������ ������
	return SourceData->read(ptr, size * nmemb);
}

// ���������������� � �����
int OggSeek(void* datasource, ogg_int64_t offset, int whence)
{
	CAbstractSoundFile* SourceData = (CAbstractSoundFile*) datasource;
	// ������ ������
	return SourceData->seek((int) offset, whence);
}

// �������� �����
int OggClose(void* datasource)
{
	return 0;
}

// ��������� ������ �����
long OggTell(void* datasource)
{
	CAbstractSoundFile* SourceData = (CAbstractSoundFile*) datasource;
	return SourceData->tell();
}

#define TEMP_BUFFER_SIZE 1024

int CDecompressOgg::GetSamples(void* buffer, int remaining, int out_channels)
{
	int j, in_channels, val, read_bytes;

	int need_read = 0;
	int temp;

	int buffer_offset = 0;
	int read_samples = 0;

	// ��������� �� �����
	short* out = (short*) buffer;
	short* in = 0;

	// ������� �������� ���������� �������
	in_channels = ov_info(_vf, -1)->channels;

	// ��������� ������ ���������� ������ � ������
	int remaining_bytes = remaining* in_channels * 2;

	while (remaining_bytes) {
		// ����������� ������ �� ������� ������
		need_read = (remaining_bytes > _tempBufferSize) ?
			_tempBufferSize :
			remaining_bytes;

		read_bytes = ov_read(_vf,
					 	(char *) _tempBuffer,
					 	need_read,
					 	0,
					 	2,
					 	1,
					 	& temp);

		if (in_channels == out_channels) {
			// ���������� ������� ��������� � ��������� ���������
			// ����������� ������
			memcpy(out, _tempBuffer, read_bytes);
			out = (short *) ((char *) out + read_bytes);
		} else {
			// ���������� ������� ��������� � ��������� �� ���������

			// ��������� ��������� �� �����
			in = (short *) _tempBuffer;
			// �������� ���������� ���������� �������
			read_samples = read_bytes / (ov_info(_vf, -1)->channels * 2);

			// �����������
			if (in_channels == 1) {
				// ���� � ������
				for (j = 0; j < read_samples; j++) {
					val = (int) * in;

					if (val > 32767)
						val = 32767;
					else if (val < -32768)
						val = -32768;
					*out++ = val;
					*out++ = val;
					in++;
				}
			} else {
				// ������ � ����
				for (j = 0; j < read_samples; j++) {
					val = ((int) in[0] + (int) in[1]) >> 1;

					if (val > 32767)
						val = 32767;
					else if (val < -32768)
						val = -32768;
					*out++ = val;
					in += 2;
				}
			}
		}

		remaining_bytes -= read_bytes;
	}
	return (int) out - (int) buffer;
}

//-----------------------------------------------------------------------------
//	����������� ��������
//	�� �����	:	pcm_format	- ��������� �� ������ ���� ��������� ���������
//								  �����
//					flag		- ��������� �� ���������� � ������� ���������
//								  ���� ���������� �������������
//					a			- ��������� �� ����������� �������� ����
//								  ��������
//	�� ������	:	*
//-----------------------------------------------------------------------------
CDecompressOgg::CDecompressOgg(WAVEFORMATEX* pcm_format, bool& flag,
	CAbstractSoundFile* a)
	: CAbstractDecompressor(pcm_format, flag, a)
{
	ov_callbacks Callback;

	flag = false;

	// ������� ������ ������ ������
	Callback.read_func = OggRead;
	Callback.seek_func = OggSeek;
	Callback.close_func = OggClose;
	Callback.tell_func = OggTell;

	// ��������� ������ ��� ��������� Ogg
#if AGSS_USE_MALLOC
	_vf = (OggVorbis_File *) malloc(sizeof(OggVorbis_File));
#else
	_vf = (OggVorbis_File *) GlobalAlloc(GPTR, sizeof(OggVorbis_File));
#endif

	// ������ �������� ?
	if (_vf) {
		// ������� ����
		if (!ov_open_callbacks(SourceData, _vf, NULL, 0, Callback)) {
			// ������� ���������� � �����
			vorbis_info* vi = ov_info(_vf, -1);

			// ����������� ������ ��� Direct X (����� Direct X �� ������ ������� �����)
			pcm_format->wFormatTag = 1;
			pcm_format->wBitsPerSample = 16;
			pcm_format->nSamplesPerSec = vi->rate;
			pcm_format->nChannels = vi->channels;
			pcm_format->nBlockAlign = (pcm_format->nChannels * pcm_format->wBitsPerSample) >>
				3;
			pcm_format->nAvgBytesPerSec = pcm_format->nBlockAlign * pcm_format->nSamplesPerSec;

			// ��������� ������ ��� ������������� �����
#if AGSS_USE_MALLOC
			_tempBuffer = malloc(SAMPLES_IN_TEMP_BUFFER * 4);
#else
			_tempBuffer = GlobalAlloc(GPTR, SAMPLES_IN_TEMP_BUFFER * 4);
#endif
			// �������� ������� ������
			if (_tempBuffer == 0)
				return;

			// ������ �������������� ������
			_tempBufferSize = SAMPLES_IN_TEMP_BUFFER * 4;

			// ��� ������ 
			flag = true;
		}
		// �������� �������������
		if (!flag) {
#if AGSS_USE_MALLOC
			free(_vf);
#else
			GlobalFree(_vf);
#endif
			_vf = 0;
		}
	}
}

//-----------------------------------------------------------------------------
//	���������� ��������
//	�� �����	:	*
//	�� ������	:	*
//-----------------------------------------------------------------------------
CDecompressOgg::~CDecompressOgg()
{
	if (_vf) {
		// ��������� ������ ��������
		ov_clear(_vf);
		// ��������� ���������
#if AGSS_USE_MALLOC
		free(_vf);
#else
		GlobalFree(_vf);
#endif
		_vf = 0;
	}

	// ��������� ������������� �����
	if (_tempBuffer) {
#if AGSS_USE_MALLOC
		free(_tempBuffer);
#else
		GlobalFree(_tempBuffer);
#endif
	}
}

//-----------------------------------------------------------------------------
//	������������ OGG ������� � ������ ������
//	�� �����	:	buffer	- ��������� �� �����
//					start	- �������� � ������ �����, � �������
//					length	- ���������� ������� ��� �������������
//	�� ������	:	�� ������� ���� ��������� ����� � �������
//					������ ������
//-----------------------------------------------------------------------------
DWORD CDecompressOgg::GetStereoSamples(void* buffer, DWORD start,
	DWORD length, bool loop)
{
	if (start != 0xFFFFFFFF)
		ov_pcm_seek(_vf, start);
	return GetSamples(buffer, length, 2);
}

//-----------------------------------------------------------------------------
//	������������ OGG ������� � ���� ������
//	�� �����	:	buffer	- ��������� �� �����
//					start	- �������� � ������ �����, � �������
//					length	- ���������� ������� ��� �������������
//	�� ������	:	�� ������� ���� ��������� ����� � �������
//					������ ������
//-----------------------------------------------------------------------------
DWORD CDecompressOgg::GetMonoSamples(void* buffer, DWORD start, DWORD length,
	bool loop)
{
	if (start != 0xFFFFFFFF)
		ov_pcm_seek(_vf, start);
	return GetSamples(buffer, length, 1);
}

//-----------------------------------------------------------------------------
//	�������� ������ �� ������� ������� ������ ������ �����
//	�� �����	:	buffer	- ��������� �� �����
//					length	- ���������� �������
//	�� ������	:	�� ������� ���� ��������� �����
//-----------------------------------------------------------------------------
DWORD CDecompressOgg::GetStereoMute(void* buffer, DWORD length)
{
	length <<= 2;
	memset(buffer, 0, length);
	return length;
}

//-----------------------------------------------------------------------------
//	�������� ������ �� ������� ������� ������ ���� �����
//	�� �����	:	buffer	- ��������� �� �����
//					length	- ���������� �������
//	�� ������	:	�� ������� ���� ��������� �����
//-----------------------------------------------------------------------------
DWORD CDecompressOgg::GetMonoMute(void* buffer, DWORD length)
{
	length <<= 1;
	memset(buffer, 0, length);
	return length;
}

//-----------------------------------------------------------------------------
//	��������� ���������� ������� � �����
//	�� �����	:	*
//	�� ������	:	���������� ������� � �����
//-----------------------------------------------------------------------------
DWORD CDecompressOgg::GetSamplesInFile(void)
{
	return (DWORD) ov_pcm_total(_vf, -1);
}

//-----------------------------------------------------------------------------
//	��������� ���������� ���� � ����� ���� �����
//	�� �����	:	*
//	�� ������	:	���������� ���� � �����
//-----------------------------------------------------------------------------
DWORD CDecompressOgg::GetRealMonoDataSize(void)
{
	return GetSamplesInFile() * 2;
}

//-----------------------------------------------------------------------------
//	��������� ���������� ���� � ����� ������ �����
//	�� �����	:	*
//	�� ������	:	���������� ���� � �����
//-----------------------------------------------------------------------------
DWORD CDecompressOgg::GetRealStereoDataSize(void)
{
	return GetSamplesInFile() * 4;
}
