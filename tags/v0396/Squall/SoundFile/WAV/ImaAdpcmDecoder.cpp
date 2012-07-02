//-----------------------------------------------------------------------------
//	����� �������� IMA ADPCM ������� ������ �� MS
//	�������� ��������� ��������� �����
//	�������		: AntiTank
//	�����������	: ������������ ����� (�����)
//-----------------------------------------------------------------------------

#include "ImaAdpcmDecoder.h"

// ������� ��������� �������� ������� ���� ��� IMA ADPCM
static const int _stepSizeTable[89] = {
	7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 19, 21, 23, 25, 28, 31, 34, 37, 41,
	45, 50, 55, 60, 66, 73, 80, 88, 97, 107, 118, 130, 143, 157, 173, 190,
	209, 230, 253, 279, 307, 337, 371, 408, 449, 494, 544, 598, 658, 724, 796,
	876, 963, 1060, 1166, 1282, 1411, 1552, 1707, 1878, 2066, 2272, 2499,
	2749, 3024, 3327, 3660, 4026, 4428, 4871, 5358, 5894, 6484, 7132, 7845,
	8630, 9493, 10442, 11487, 12635, 13899, 15289, 16818, 18500, 20350, 22385,
	24623, 27086, 29794, 32767
};

// ������� ��������� ������� IMA ADPCM
static const int indexAdjustTable[16] = {
	-1, -1, -1, -1, 2, 4, 6, 8, -1, -1, -1, -1, 2, 4, 6, 8, 
};

// ���������� ��������� IMA ADPCM ������
struct SImaState {
	int index;
	int previousValue;
};

//-----------------------------------------------------------------------------
//	������������� ������ ���������
//	�� �����	:	deltaCode	- �������� ���������
//					state		- ��������� ��� ������������� ������
//	�� ������	:	��������������� ��������
//-----------------------------------------------------------------------------
WORD ImaAdpcmDecode(BYTE deltaCode, SImaState& state)
{
	// �������� �������� ������� �������� ����
	int step = _stepSizeTable[state.index];

	// ������� ����������, ����������� ������� �������� ����
	// �������������� ���: ���������� = (deltaCode+0.5)*���/4
	int difference = step >> 3;
	if (deltaCode & 1)
		difference += step >> 2;
	if (deltaCode & 2)
		difference += step >> 1;
	if (deltaCode & 4)
		difference += step;
	if (deltaCode & 8)
		difference = -difference;

	// ��������� ����� �������
	state.previousValue += difference;
	if (state.previousValue > 32767)
		state.previousValue = 32767;
	else if (state.previousValue < -32768)
		state.previousValue = -32768;

	// ��������� �������� ���� ��� ��������� ��������� �������
	state.index += indexAdjustTable[deltaCode];
	if (state.index < 0)
		state.index = 0;
	else if (state.index > 88)
		state.index = 88;
	return state.previousValue;
}

//-----------------------------------------------------------------------------
//	������������� ������
//	�� �����	:	*
//	�� ������	:	���������� �������������� �������
//-----------------------------------------------------------------------------
DWORD CDecompressImaAdpcmMs::DecodePacket(void)
{
	BYTE b;
	DWORD i, remaining;
	short* left_ptr;
	short* rigth_ptr;

	// ��������� ������� � ������ ������
	SImaState state[2];

	// ������ ���������
	if (SourceData->read(_packetBuffer, _bytesPerPacket) != _bytesPerPacket)
		return 0;

	char* bytePtr = _packetBuffer;

	// ������� ��������� �� ������
	left_ptr = _left;
	rigth_ptr = _rigth;

	// �������� ���� ������
	if (_channels == 1)	// ���� ������
	{
		// ������������� ������ ������
		state[0].previousValue = bytePtr[1] * 0x100 + bytePtr[0];
		bytePtr += 2;
		state[0].index = *bytePtr++;
		if ((*bytePtr++) || (state[0].index > 88))
			return 0;
		*left_ptr++ = state[0].previousValue;

		remaining = _samplesPerPacket - 1;

		while (remaining) {
			for (i = 0; i < 4; i++) {
				b = *bytePtr++;
				*left_ptr++ = ImaAdpcmDecode(b & 0xf, state[0]);
				*left_ptr++ = ImaAdpcmDecode((b >> 4) & 0xf, state[0]);
			}
			remaining -= 8;
		}
	} else {
		// ������ ������

		// ������������� ������ ������
		state[0].previousValue = bytePtr[1] * 0x100 + bytePtr[0];
		bytePtr += 2;
		state[0].index = *bytePtr++;
		if ((*bytePtr++) || (state[0].index > 88))
			return 0;
		*left_ptr++ = state[0].previousValue;

		// ������������� ������� ������
		state[1].previousValue = bytePtr[1] * 0x100 + bytePtr[0];
		bytePtr += 2;
		state[1].index = *bytePtr++;
		if ((*bytePtr++) || (state[1].index > 88))
			return 0;
		*rigth_ptr++ = state[1].previousValue;

		remaining = _samplesPerPacket - 1;

		while (remaining) {
			for (i = 0; i < 4; i++) {
				b = *bytePtr++;
				*left_ptr++ = ImaAdpcmDecode(b & 0xf, state[0]);
				*left_ptr++ = ImaAdpcmDecode((b >> 4) & 0xf, state[0]);
			}

			for (i = 0; i < 4; i++) {
				b = *bytePtr++;
				*rigth_ptr++ = ImaAdpcmDecode(b & 0xf, state[1]);
				*rigth_ptr++ = ImaAdpcmDecode((b >> 4) & 0xf, state[1]);
			}
			remaining -= 8;
		}
	}
	return _samplesPerPacket;
}

//-----------------------------------------------------------------------------
//	����������� ��������
//	�� �����	:	pcm_format	- ��������� �� ��������� �������, ���� 
//								  ��������� ��������� �����
//					flag		- ��������� �� ���������� � ������� ���������
//								  ���� ���������� �������������
//					a			- ��������� �� ����������� �������� ����
//								  ��������
//	�� ������	:	*
//-----------------------------------------------------------------------------
CDecompressImaAdpcmMs::CDecompressImaAdpcmMs(WAVEFORMATEX* pcm_format,
	bool& flag, CAbstractSoundFile* a)
	: CAbstractDecompressor(pcm_format, flag, a)
{
	flag = false;
	// ��������� ��������� �� ������
	SIMA_ADPCM_Format* format = (SIMA_ADPCM_Format*) SourceData->GetFmt();

	// ���������� ������� ����� ���������
	_channels = format->fmt.nChannels;					// ���������� �������� �������
	_samplesPerPacket = format->SamplesPerPacket;					// ���������� ������� � ������
	_bytesPerPacket = ((_samplesPerPacket + 7) / 2) * _channels;// �������� ���������� ���� �� �����
	_packetof = SourceData->size / _bytesPerPacket;		// ����������� ���������� ������� � �����
	_curPacket = 0;

	// �������� �� ���������� ������� � ����� (������ �� ������)
	if ((!_channels) || (_channels > 2))
		return;

	// ������� ����� ��� ������������� ������ ������, ������� ������ � ������ ��� �����
#if AGSS_USE_MALLOC
	_packetBuffer = (char *) malloc(_samplesPerPacket * _channels * 2 +
							 	_bytesPerPacket);
#else
	_packetBuffer = (char *) GlobalAlloc(GPTR,
							 	_samplesPerPacket * _channels * 2 +
							 	_bytesPerPacket);
#endif

	if (_packetBuffer != 0) {
		// �������� ��������� �� ������ �����
		_left = (short *) (_packetBuffer + _bytesPerPacket);

		// �������� ��������� �� ����� ��������������� �������
		_rigth = _left + _samplesPerPacket;

		// ����������� ������ ��� Direct X (����� Direct X �� ������ ������� �����)
		pcm_format->wFormatTag = 1;
		pcm_format->wBitsPerSample = 16;
		pcm_format->nSamplesPerSec = format->fmt.nSamplesPerSec;
		pcm_format->nChannels = format->fmt.nChannels;
		pcm_format->nBlockAlign = (pcm_format->nChannels * pcm_format->wBitsPerSample) >>
			3;
		pcm_format->nAvgBytesPerSec = pcm_format->nBlockAlign * pcm_format->nSamplesPerSec;

		// ���������� ���� �����
		DecodePacket();
		flag = true;
		return;
	}

	// ������� ������ � ������ �������
	_left = 0;
	_rigth = 0;
}

//-----------------------------------------------------------------------------
//	���������� ��������
//	�� �����	:	*
//	�� ������	:	*
//-----------------------------------------------------------------------------
CDecompressImaAdpcmMs::~CDecompressImaAdpcmMs()
{
	// ��������� ������� ������
	if (_packetBuffer) {
#if AGSS_USE_MALLOC
		free(_packetBuffer);
#else
		GlobalFree(_packetBuffer);
#endif
	}

	// ������� ���������
	_packetBuffer = 0;
	_left = 0;
	_rigth = 0;
}

//-----------------------------------------------------------------------------
//	������������ IMA ADPCM ������� ������ �� MS � ���� ������
//	�� �����	:	buffer	- ��������� �� �����
//					start	- �������� � ������ �����, � �������
//					length	- ���������� ������� ��� �������������
//	�� ������	:	�� ������� ���� ��������� ����� � �������
//					������ ������
//-----------------------------------------------------------------------------
DWORD CDecompressImaAdpcmMs::GetMonoSamples(void* buffer, DWORD start,
	DWORD length, bool loop)
{
	int s;
	short* Out;
	short* LeftPtr;
	short* RigthPtr;
	DWORD Offset;
	DWORD NeedPacket;
	DWORD Samples;

	// �������� � ����� ������ ���������� ������
	NeedPacket = (start / _samplesPerPacket) * _bytesPerPacket;
	// �������� �������� � ������������ ������
	Offset = start % _samplesPerPacket;
	// ������������� ����������
	Out = (short *) buffer;

	while (length) {
		// �������� �� ���������� � ������ ������
		if (_curPacket != NeedPacket) {
			if ((_curPacket + _bytesPerPacket) != NeedPacket)
				SourceData->seek(NeedPacket, FILE_BEGIN);
			// ������������� ������ ������
			_curPacket = NeedPacket;
			DecodePacket();
		}

		// ������ �������� � ������
		LeftPtr = _left + Offset;
		RigthPtr = _rigth + Offset;
		Samples = _samplesPerPacket - Offset;
		Offset = 0;

		// ��������� ���������� ������� ��� ���������� �� ������� ������
		if (Samples > length)
			Samples = length;
		length -= Samples;

		// ������ �������
		if (_channels == 1) {
			// ���� ������
			do {
				*Out++ = *LeftPtr++;
			} while (--Samples);
		} else {
			// ������ ������
			do {
				s = ((int) * LeftPtr + (int) * RigthPtr) >> 1;
				if (s < -32768)
					s = -32768;
				else if (s > 32767)
					s = 32767;
				*Out++ = (short) s;
				LeftPtr++;
				RigthPtr++;
			} while (--Samples);
		}
		if (length)
			NeedPacket += _bytesPerPacket;
	}

	// ������ ����� � ����������� ������
	return (DWORD) Out - (DWORD) buffer;
}

//-----------------------------------------------------------------------------
//	������������ IMA ADPCM ������� ������ �� MS � ������ ������
//	�� �����	:	buffer	- ��������� �� �����
//					start	- �������� � ������ �����, � �������
//					length	- ���������� ������� ��� �������������
//	�� ������	:	�� ������� ���� ��������� ����� � �������
//					������ ������
//-----------------------------------------------------------------------------
DWORD CDecompressImaAdpcmMs::GetStereoSamples(void* buffer, DWORD start,
	DWORD length, bool loop)
{
	short* Out;
	short* LeftPtr;
	short* RigthPtr;
	DWORD Offset;
	DWORD NeedPacket;
	DWORD Samples;

	// �������� � ����� ������ ���������� ������
	NeedPacket = (start / _samplesPerPacket) * _bytesPerPacket;
	// �������� �������� � ������������ ������
	Offset = start % _samplesPerPacket;
	// ������������� ����������
	Out = (short *) buffer;

	while (length) {
		// �������� �� ���������� � ������ ������
		if (_curPacket != NeedPacket) {
			if ((_curPacket + _bytesPerPacket) != NeedPacket)
				SourceData->seek(NeedPacket, FILE_BEGIN);
			// ������������� ������ ������
			_curPacket = NeedPacket;
			DecodePacket();
		}

		// ������ �������� � ������
		LeftPtr = _left + Offset;
		RigthPtr = _rigth + Offset;
		Samples = _samplesPerPacket - Offset;
		Offset = 0;

		// ��������� ���������� ������� ��� ���������� �� ������� ������
		if (Samples > length)
			Samples = length;
		length -= Samples;

		// ������ ������
		if (_channels == 1) {
			// ���� ������
			do {
				*Out++ = *LeftPtr;
				*Out++ = *LeftPtr;
				LeftPtr++;
			} while (--Samples);
		} else {
			// ������ ������
			do {
				*Out++ = *LeftPtr++;
				*Out++ = *RigthPtr++;
			} while (--Samples);
		}
		if (length)
			NeedPacket += _bytesPerPacket;
	}

	// ������ ����� � ����������� ������
	return (DWORD) Out - (DWORD) buffer;
}
//-----------------------------------------------------------------------------
//	�������� ������ �� ������� ������� ������
//	�� �����	:	buffer	- ��������� �� �����
//					length	- ���������� �������
//	�� ������	:	�� ������� ���� ��������� �����
//-----------------------------------------------------------------------------
DWORD CDecompressImaAdpcmMs::GetMonoMute(void* buffer, DWORD length)
{
	// ��� ��� ������ 16 ������ -> samples*16/8*1
	length <<= 1;

	// ������� �����
	memset(buffer, 0, length);

	return length;
}

//-----------------------------------------------------------------------------
//	�������� ������ �� ������� ������� ������
//	�� �����	:	buffer	- ��������� �� �����
//					length	- ���������� �������
//	�� ������	:	�� ������� ���� ��������� �����
//-----------------------------------------------------------------------------
DWORD CDecompressImaAdpcmMs::GetStereoMute(void* buffer, DWORD length)
{
	// ��� ��� ������ 16 ������ -> samples*16/8*2
	length <<= 2;

	// ������� �����
	memset(buffer, 0, length);

	return length;
}
