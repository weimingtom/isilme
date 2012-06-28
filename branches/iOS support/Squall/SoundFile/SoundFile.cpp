//-----------------------------------------------------------------------------
//	����� ��� ������ �� ��������� �������
//	�������� ��������� ��������� �����
//	�������		: AntiTank
//	�����������	: ������������ ����� (�����)
//-----------------------------------------------------------------------------

#include "SquallApi.h"
#include "SoundFile.h"
#include "Reader.h"

// ������� ������
#include "WavFile.h"
#include "MpegFile.h"
#include "OggFile.h"
#include "WmaFile.h"
//#include "TrackFile.h"

// �������� �������� �������
#include "PcmDecoder.h"
#include "ImaAdpcmDecoder.h"
#include "MsAdpcmDecoder.h"
#include "MpegDecoder.h"
#include "OggDecoder.h"
#include "WmaDecoder.h"
//#include "TrackDecoder.h"

//-----------------------------------------------------------------------------
//	����������� ������
//	�� �����	:	*
//	�� ������	:	*
//-----------------------------------------------------------------------------
CSoundFile::CSoundFile()
{
	memset(&pcm_format, 0, sizeof(WAVEFORMATEX));
	class_id = 0x53536746;  					 // ������������� ������
	decoder = 0;								// �������� ���
	sound_data = 0;									// ����������� ������ ���
	reader = 0;									// ���������� ������ ��������� �����
	_ref = 0;   							 // ���������� ������
}

//-----------------------------------------------------------------------------
//	���������� ������
//	�� �����	:	*
//	�� ������	:	*
//-----------------------------------------------------------------------------
CSoundFile::~CSoundFile()
{
	// ������ �� ������
	if (this) {
		DeInit();
		class_id = 0;
	}
}

//-----------------------------------------------------------------------------
// ���������� ������
// �� �����    :  *
// �� ������   :  ���������� ������ � ������ �����
//-----------------------------------------------------------------------------
int CSoundFile::AddRef(void)
{
	_ref++;
	return _ref;
}

//-----------------------------------------------------------------------------
// �������� ������
// �� �����    :  *
// �� ������   :  ���������� ������ � ������ �����
//-----------------------------------------------------------------------------
int CSoundFile::DecRef(void)
{
	if (_ref <= 0)
		_ref = 0;
	else
		_ref--;

	return _ref;
}
//-----------------------------------------------------------------------------
//	���������������� ����
//	�� �����	:	*
//	�� ������	:	���������� �������������
//-----------------------------------------------------------------------------
bool CSoundFile::Init(void)
{
	bool format_init;
	// ������������� ����������� ������
	WAVEFORMATEX* format;

	// ��������� ������� ���� ��� wav
	sound_data = new CWavFile(reader);

	// �������� ������������� �����
	format = sound_data->GetFmt();
	if (format) {
		// �������� �� ������ PCM
		if (format->wFormatTag == 1) {
			if (format->wBitsPerSample == 8)
				decoder = new CDecompressPcm8Unsigned(&pcm_format,
							  	format_init,
							  	sound_data);
			else
				decoder = new CDecompressPcm16Signed(&pcm_format,
							  	format_init,
							  	sound_data);
			return format_init;
		}

		// �������� �� ������ MS ADPCM
		if (format->wFormatTag == 2) {
			decoder = new CDecompressMsAdpcm(&pcm_format,
						  	format_init,
						  	sound_data);
			return format_init;
		}

		// �������� �� ������ IMA ADPCM ������ �� MS
		if (format->wFormatTag == 17) {
			decoder = new CDecompressImaAdpcmMs(&pcm_format,
						  	format_init,
						  	sound_data);
			return format_init;
		}

		// �������� �� ������ Mpeg Layer 3
		if (format->wFormatTag == 85) {
			decoder = new CDecompressMpeg(&pcm_format, format_init, sound_data);
			return format_init;
		}
	}
	// ������ ���
	delete sound_data;
	sound_data = 0;
	delete decoder;
	decoder = 0;


	char* test = reader->get_file_ext(); 

	// �������� ���������� �����
	if (reader->get_file_ext() != 0 && !memcmp(reader->get_file_ext(),
											"wma",
											3)) {
		// ��������� ���� ��� wma
		sound_data = new CWmaFile(reader);
		decoder = new CDecompressWma(&pcm_format, format_init, sound_data);
		if (format_init)
			return format_init;

		delete sound_data;
		sound_data = 0;
		delete decoder;
		decoder = 0;
	} else {
		// �������� ������� ���� ��� Mpeg
		sound_data = new CMpegFile(reader);
		decoder = new CDecompressMpeg(&pcm_format, format_init, sound_data);
		if (format_init)
			return format_init;

		// ������ ���
		delete sound_data;
		sound_data = 0;
		delete decoder;
		decoder = 0;

		// ��������� ������� ��� Ogg
		sound_data = new COggFile(reader);
		decoder = new CDecompressOgg(&pcm_format, format_init, sound_data);
		if (format_init)
			return format_init;

		delete sound_data;
		sound_data = 0;
		delete decoder;
		decoder = 0;
		/*  	
				  // ��������� ������� ��� ��������� ������
				  sound_data	= new CTrackFile(reader);
				  decoder		= new CDecompressTrack(&pcm_format, format_init, sound_data);
				  if (format_init)
					 return format_init;
					delete sound_data;
					sound_data = 0;
					delete decoder;
					decoder = 0;
			*/
	}
	// ������ ������������� ������ 
	return false;
}

//-----------------------------------------------------------------------------
//	������� �������� ������ �� �����
//	�� �����	:	filename	- ��������� �� ��� �����
//					stream_flag	- ���� ��������� ������������� �����
//	�� ������	:	���������� �������� �������� ������
//-----------------------------------------------------------------------------
bool CSoundFile::CreateSoundDataFromFile(const char* filename, int stream_flag)
{
	bool ret = false;

	// ������ �� ������
	if (!this)
		return ret;

	// �������������� �������������� ���������� �����
	reader = new CReader(filename,
				 	stream_flag,
				 	ret,
				 	api._open,
				 	api._read,
				 	api._seek,
				 	api._close,
				 	api._malloc,
				 	api._free);
	if (!ret) {
		DeInit();
		return ret;
	}

	// ������������� ������
	ret = Init();
	if (!ret)
		DeInit();

	return ret;
}

//-----------------------------------------------------------------------------
//	������� �������� ������ �� ������
//	�� �����	:	memory_ptr	- ��������� �� ��� �����
//					memory_size	- ���� ��������� ������������� �����
//					new_memory	- ���� �������� ����� ������������ ������
//	�� ������	:	���������� �������� �������� ������
//-----------------------------------------------------------------------------
bool CSoundFile::CreateSoundDataFromMemory(void* memory,
	unsigned int memory_size, int new_memory)
{
	bool ret = false;

	// ������ �� ������
	if (!this)
		return ret;

	// �������������� �������������� ���������� �����
	reader = new CReader(memory,
				 	memory_size,
				 	new_memory,
				 	ret,
				 	api._malloc,
				 	api._free);
	if (!ret) {
		DeInit();
		return ret;
	}

	// ������������� ������
	ret = Init();
	if (!ret)
		DeInit();

	return ret;
}

//-----------------------------------------------------------------------------
//	��������� ������������ ������� ������� ������
//	�� �����	:	*
//	�� ������	:	*
//-----------------------------------------------------------------------------
void CSoundFile::DeInit(void)
{
	// ������� ���� ?
	if (decoder) {
		delete decoder;
		decoder = 0;
	}

	// ����� ������ � ���������� �������� ����� ���� ?
	if (sound_data) {
		delete sound_data;
		sound_data = 0;
	}
	// ����� ��� ������ � ������ ���� ?
	if (reader) {
		delete reader;
		reader = 0;
	}
}

//-----------------------------------------------------------------------------
//	�������� ���������� ������
//	�� �����	:	*
//	�� ������	:	���������� ������
//					true - ������ ��������
//					false - ������ ������� ��� ����������
//-----------------------------------------------------------------------------
bool CSoundFile::Check(void)
{
	return (this &&
		decoder &&
		sound_data &&
		reader &&
		(class_id == 0x53536746)) ?
		true :
		false;
}

//-----------------------------------------------------------------------------
//	��������� ��������� ������� �����
//	�� �����	:	*
//	�� ������	:	��������� �� ������ ����� (0 - ���� �� ���������������)
//-----------------------------------------------------------------------------
WAVEFORMATEX* CSoundFile::GetFormat(void)
{
	return Check() ? &pcm_format : 0;
}
//-----------------------------------------------------------------------------
//	���������� ������� ������
//	�� �����	:	buffer	- ��������� �� ����� ����������
//					start	- ��������� ������� � ����� ������������ 0
//					length	- ������ ���������� ������
//	�� ������	:	�� ������� ����� �������� ����������� �����
//-----------------------------------------------------------------------------
unsigned int CSoundFile::GetMonoData(void* buffer, unsigned int start,
	unsigned int length, bool loop)
{
	return Check() ? decoder->GetMonoSamples(buffer, start, length, loop) : 0;
}
//-----------------------------------------------------------------------------
//	���������� ������� ������
// �� �����    :  buffer   - ��������� �� ����� ����������
//  			  start    - ��������� ������� � ����� ������������ 0
//  			  length   - ������ ���������� ������
//	�� ������	:	�� ������� ����� �������� ����������� �����
//-----------------------------------------------------------------------------
unsigned int CSoundFile::GetStereoData(void* buffer, unsigned int start,
	unsigned int length, bool loop)
{
	return Check() ?
		decoder->GetStereoSamples(buffer, start, length, loop) :
		0;
}
//-----------------------------------------------------------------------------
// ���������� "�������������� �������" ������
// �� �����    :  buffer   - ��������� �� ����� ����������
//  			  length   - ������ ������ � �������
// �� ������   :  �� ������� ����� �������� ����������� �����
//-----------------------------------------------------------------------------
unsigned int CSoundFile::GetMonoMute(void* buffer, unsigned int length)
{
	return Check() ? decoder->GetMonoMute(buffer, length) : 0;
}
//-----------------------------------------------------------------------------
// ���������� "��������������� �������" ������
// �� �����    :  buffer	- ��������� �� ����� ����������
//  			  length	- ������ ������ � �������
//	�� ������   :  �� ������� ����� �������� ����������� �����
//-----------------------------------------------------------------------------
unsigned int CSoundFile::GetStereoMute(void* buffer, unsigned int length)
{
	return Check() ? decoder->GetStereoMute(buffer, length) : 0;
}
//-----------------------------------------------------------------------------
// ��������� ������ ���� ����� � ������
// �� �����    :  *
// �� ������   :  ������ ����� � ������
//-----------------------------------------------------------------------------
unsigned int CSoundFile::GetRealMonoDataSize(void)
{
	return Check() ? decoder->GetRealMonoDataSize() : 0;
}
//-----------------------------------------------------------------------------
//	��������� ������ ������ ����� � ������
//	�� �����	:	*
//	�� ������	:	������ ����� � ������
//-----------------------------------------------------------------------------
unsigned int CSoundFile::GetRealStereoDataSize(void)
{
	return Check() ? decoder->GetRealStereoDataSize() : 0;
}
//-----------------------------------------------------------------------------
// ��������� ������ ����� � �������
// �� �����    :  *
// �� ������   :  ������ ����� � �������
//-----------------------------------------------------------------------------
unsigned int CSoundFile::GetSamplesInFile(void)
{
	return Check() ? decoder->GetSamplesInFile() : 0;
}

//-----------------------------------------------------------------------------
// ��������� ������ ����� � �������
// �� �����    :	*
// �� ������   :	��������� ��������� �� ��� �����
//-----------------------------------------------------------------------------
char* CSoundFile::GetFileName(void)
{
	return Check() ? sound_data->get_file_name() : 0;
}