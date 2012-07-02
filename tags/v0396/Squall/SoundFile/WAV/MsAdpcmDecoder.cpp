//-----------------------------------------------------------------------------
//	����� �������� ADPCM �������, ������ �� MicroSoft
//	�������� ��������� ��������� �����
//	�������		: AntiTank
//	�����������	: ������������ ����� (�����)
//-----------------------------------------------------------------------------

// ���������
#include "MsAdpcmDecoder.h"

// ������� ��������� ������� IMA ADPCM
static const int IndexTable[16] = {
	230, 230, 230, 230, 307, 409, 512, 614, 768, 614, 512, 409, 307, 230, 230,
	230, 
};

//-----------------------------------------------------------------------------
// ���������
//-----------------------------------------------------------------------------
#pragma pack(1)

// ��������� ��������������� ���������
struct SMonoHeader {
	char table_index;
	short step;
	short cur_value;
	short prev_value;
};

// ��������� ����������������� ���������
struct SStereoHeader {
	char l_table_index;
	char r_table_index;
	short l_step;
	short r_step;
	short l_cur_value;
	short r_cur_value;
	short l_prev_value;
	short r_prev_value;
};

// ��������� ��������� ������
struct SChannelState {
	int coef_1;
	int coef_2;
	int step;
	int previous_value;
	int current_value;
};

//-----------------------------------------------------------------------------
//	������������� ����� �������
//	�� �����	:	delta_code	- ��� ��������
//					state		- ��������� ������������� ������
//	�� ������	:	������������� ��������
//-----------------------------------------------------------------------------
WORD DecodeMsAdpcm(char delta_code, SChannelState& state)
{
	int data;
	delta_code >>= 4;

	data = (state.step * delta_code) +
		(((state.coef_2 * state.previous_value) +
		(state.coef_1 * state.current_value)) >>
		8);
	if (data > 32767)
		data = 32767;
	else if (data < -32768)
		data = -32768;

	state.step = (state.step * IndexTable[delta_code & 0xF]) >> 8;
	if (state.step < 16)
		state.step = 16;

	state.previous_value = state.current_value;
	state.current_value = data;
	return data;
}

//-----------------------------------------------------------------------------
//	������������� ��������������� ������
//	�� �����	:	*
//	�� ������	:	���������� �������������� �������
//-----------------------------------------------------------------------------
DWORD CDecompressMsAdpcm::DecodeMONOPacket(void)
{
	SChannelState state;
	int bytes;
	// ������ ���������
	if (SourceData->read(_packetBuffer, _bytesPerPacket) != _bytesPerPacket)
		return 0;

	char* in_buffer = (char*) _packetBuffer;
	short* out_buffer = _left;

	bytes = _bytesPerPacket;

	char value =* in_buffer;
	if (value > _numCoef)
		return 0;

	state.coef_1 = _coefTable[value].Coef1;
	state.coef_2 = _coefTable[value].Coef2;
	state.step = ((SMonoHeader *) in_buffer)->step;
	state.current_value = ((SMonoHeader *) in_buffer)->cur_value;
	state.previous_value = ((SMonoHeader *) in_buffer)->prev_value;

	*out_buffer++ = state.previous_value;
	*out_buffer++ = state.current_value;

	bytes -= sizeof(SMonoHeader);
	in_buffer += sizeof(SMonoHeader);

	while (bytes) {
		value = *in_buffer++;
		*out_buffer++ = DecodeMsAdpcm(value, state);

		value <<= 4;
		*out_buffer++ = DecodeMsAdpcm(value, state);

		bytes--;
	}
	return _samplesPerPacket;
}

//-----------------------------------------------------------------------------
//	������������� ������
//	�� �����	:	*
//	�� ������	:	���������� �������������� �������
//-----------------------------------------------------------------------------
DWORD CDecompressMsAdpcm::DecodeSTEREOPacket(void)
{
	SChannelState state[2];
	int bytes;
	char value;
	// ������ ���������
	if (SourceData->read(_packetBuffer, _bytesPerPacket) != _bytesPerPacket)
		return 0;

	char* in_buffer = (char*) _packetBuffer;
	short* l_out_buffer = _left;
	short* r_out_buffer = _rigth;

	bytes = _bytesPerPacket;

	value = ((SStereoHeader *) in_buffer)->l_table_index;
	if (value > _numCoef)
		return 0;

	state[0].coef_1 = _coefTable[value].Coef1;
	state[0].coef_2 = _coefTable[value].Coef2;
	state[0].step = ((SStereoHeader *) in_buffer)->l_step;
	state[0].current_value = ((SStereoHeader *) in_buffer)->l_cur_value;
	state[0].previous_value = ((SStereoHeader *) in_buffer)->l_prev_value;

	value = ((SStereoHeader *) in_buffer)->r_table_index;
	if (value > _numCoef)
		return 0;

	state[1].coef_1 = _coefTable[value].Coef1;
	state[1].coef_2 = _coefTable[value].Coef2;
	state[1].step = ((SStereoHeader *) in_buffer)->r_step;
	state[1].current_value = ((SStereoHeader *) in_buffer)->r_cur_value;
	state[1].previous_value = ((SStereoHeader *) in_buffer)->r_prev_value;

	*l_out_buffer++ = state[0].previous_value;
	*l_out_buffer++ = state[0].current_value;
	*r_out_buffer++ = state[1].previous_value;
	*r_out_buffer++ = state[1].current_value;

	bytes -= sizeof(SStereoHeader);
	in_buffer += sizeof(SStereoHeader);

	while (bytes) {
		value = *in_buffer++;
		*l_out_buffer++ = DecodeMsAdpcm(value, state[0]);

		value <<= 4;
		*r_out_buffer++ = DecodeMsAdpcm(value, state[1]);

		bytes--;
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
CDecompressMsAdpcm::CDecompressMsAdpcm(WAVEFORMATEX* pcm_format, bool& flag,
	CAbstractSoundFile* a)
	: CAbstractDecompressor(pcm_format, flag, a)
{
	flag = false;
	// ��������� ��������� �� ������
	SMS_ADPCM_Format* format = (SMS_ADPCM_Format*) SourceData->GetFmt();

	// ���������� ������� ����� ���������
	_channels = format->fmt.nChannels;					// ���������� �������� �������
	_samplesPerPacket = format->SamplesPerPacket;					// ���������� ������� � ������
	_bytesPerPacket = (((_samplesPerPacket - 2) / 2) + 7) * _channels;// �������� ���������� ���� �� �����
	_packetof = SourceData->size / _bytesPerPacket;		// ����������� ���������� ������� � �����
	_curPacket = 0;

	_numCoef = format->NumCoef;
	_coefTable = (SCoef *) ((char *) format + sizeof(SMS_ADPCM_Format));

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
		if (_channels == 1)
			DecodeMONOPacket();
		else
			DecodeSTEREOPacket();
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
CDecompressMsAdpcm::~CDecompressMsAdpcm()
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
DWORD CDecompressMsAdpcm::GetMonoSamples(void* buffer, DWORD start,
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
			if (_channels == 1)
				DecodeMONOPacket();
			else
				DecodeSTEREOPacket();
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
DWORD CDecompressMsAdpcm::GetStereoSamples(void* buffer, DWORD start,
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
			if (_channels == 1)
				DecodeMONOPacket();
			else
				DecodeSTEREOPacket();
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
DWORD CDecompressMsAdpcm::GetMonoMute(void* buffer, DWORD length)
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
DWORD CDecompressMsAdpcm::GetStereoMute(void* buffer, DWORD length)
{
	// ��� ��� ������ 16 ������ -> samples*16/8*2
	length <<= 2;

	// ������� �����
	memset(buffer, 0, length);

	return length;
}
