//-----------------------------------------------------------------------------
// ������ � ZOOMFX �����������
// ��������� ��������� ��������� "�����"
// �������     : AntiTank
// ����������� : ������������ ����� (�����)
//-----------------------------------------------------------------------------

// ���������
#include "ZoomFX.h"
#include "ZoomFX_api.h"

// ������������� ����������
GUID ZOOMFX_Guid = {
	0xCD5368E0, 0x3450, 0x11D3,
	{ 0x8B, 0x6E, 0x00, 0x10, 0x5A, 0x9B, 0x7B, 0xBC }
};

//-----------------------------------------------------------------------------
// ��������� ���������� ��� ��������� ������
// �� �����    :  buffer   - ��������� �� �������� ����� ��� �������� �����
//  						 �������� ���������
// �� ������   :  ��������� �� ��������� ���������
//-----------------------------------------------------------------------------
LPKSPROPERTYSET zoomfx_GetBufferInterface(LPDIRECTSOUNDBUFFER buffer)
{
	LPKSPROPERTYSET prop;

	// �������� ������� ������
	if (!buffer)
		return 0;

	// ��������� ����������
	if (buffer->QueryInterface(IID_IKsPropertySet, (void * *) &prop) == DS_OK)
		return prop;

	// ������
	return 0;
}

//-----------------------------------------------------------------------------
// �������� ����������� ������ � ������
// �� �����    :  prop  - ��������� �� ���������
// �� ������   :  ��������� ������ � ������
//-----------------------------------------------------------------------------
int zoomfx_TestQuerySupport(LPKSPROPERTYSET prop)
{
	unsigned long support;

	// �������� ����������
	if (!prop)
		return false;

	// �������� ��������� ���������
	if (prop->QuerySupport(ZOOMFX_Guid, DSPROPERTY_ZOOMFXBUFFER_ALL, & support) ==
		DS_OK) {
		// �������� ����������� ������ � ������
		if ((support & KSPROPERTY_SUPPORT_GET) &&
			(support & KSPROPERTY_SUPPORT_SET))
			return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
// ��������� ����������
// �� �����    :  prop  - ��������� �� ���������
//  			  data  - ��������� �� ��������������� ������
// �� ������   :  ��������� ���������
//-----------------------------------------------------------------------------
int zoomfx_Set(LPKSPROPERTYSET prop, void* data)
{
	// �������� ������� ����������
	if (prop) {
		if (prop->Set(ZOOMFX_Guid,
				  	DSPROPERTY_ZOOMFXBUFFER_ALL,
				  	NULL,
				  	0,
				  	data,
				  	sizeof(ZOOMFX_BUFFERPROPERTIES)) == DS_OK)
			return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
// ��������� ����������
// �� �����    :  prop  - ��������� �� ���������
//  			  data  - ��������� ���� ����� ��������� ���������
// �� ������   :  ��������� ���������
//-----------------------------------------------------------------------------
int zoomfx_Get(LPKSPROPERTYSET prop, void* data)
{
	unsigned long read;

	// �������� ������� ����������
	if (prop) {
		if (prop->Get(ZOOMFX_Guid,
				  	DSPROPERTY_ZOOMFXBUFFER_ALL,
				  	NULL,
				  	0,
				  	data,
				  	sizeof(ZOOMFX_BUFFERPROPERTIES),
				  	& read) == DS_OK)
			return true;
	}
	return true;
}

//-----------------------------------------------------------------------------
// �������� ������� ZOOMFX ����������
// �� �����    :  direct   - ��������� �� ������ ���������������
// �� ������   :  ������� ZOOMFX ����������
//-----------------------------------------------------------------------------
int zoomfx_TestSupport(LPDIRECTSOUND direct)
{
	// ���������� ����������
	WAVEFORMATEX wfx;   	 // ������ �����
	DSBUFFERDESC dsbd;  	 // ����������
	int ok; 		// ���� ������������� ZOOMFX ����������

	// ������������� ������
	LPDIRECTSOUNDBUFFER Buffer;
	LPKSPROPERTYSET KsProp;

	// �������� ��������� � ��������
	wfx.wFormatTag = 1;
	wfx.nChannels = 2;
	wfx.nSamplesPerSec = 44100;
	wfx.wBitsPerSample = 16;
	wfx.nBlockAlign = (wfx.nChannels * wfx.wBitsPerSample) >> 3;
	wfx.nAvgBytesPerSec = wfx.nBlockAlign * wfx.nSamplesPerSec;
	wfx.cbSize = 0;

	// ������� ���������
	ok = false;
	Buffer = 0;
	KsProp = 0;

	// �������� ������� ������� ���������������
	if (direct) {
		// ��������� ������ ���������� ������
		ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
		dsbd.dwSize = sizeof(DSBUFFERDESC);
		dsbd.dwFlags = DSBCAPS_STATIC | DSBCAPS_CTRL3D;
		dsbd.dwBufferBytes = 128;
		dsbd.lpwfxFormat = &wfx;

		// �������� ���������� ������
		ok = (direct->CreateSoundBuffer(&dsbd, & Buffer, NULL) == DS_OK) ?
			true :
			false;

		// ������� ��������� ��� ������ � ZOOMFX
		KsProp = zoomfx_GetBufferInterface(Buffer);

		// �������� ����������� ������ � ������
		ok = zoomfx_TestQuerySupport(KsProp);

		// ��������� EAX ���������
		if (KsProp) {
			KsProp->Release();
			KsProp = 0;
		}

		// ��������� �����
		if (Buffer) {
			Buffer->Release();
			Buffer = 0;
		}
	}
	return ok;
}