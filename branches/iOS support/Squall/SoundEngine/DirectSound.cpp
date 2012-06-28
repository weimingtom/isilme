//-----------------------------------------------------------------------------
// ������ � Direct Sound
// �������� ��������� ��������� Squall
// �������     : AntiTank
// ����������� : ������������ ����� (�����)
//-----------------------------------------------------------------------------
#include <dsound.h>

//-----------------------------------------------------------------------------
//	�������� Direct Sound �������
// �� �����    :  window		 - ������������� ����
//  			  clsid_direct   - ������������� Direct Sound
//  			  device		 - ������������� ���������� ���������������
//  			  level 		 - ������� ����������
// �� ������   :	��������� �� ��������� Direct Sound ������, ���� ��������
//  			  ����� 0 ������ �������� �� ����������
//-----------------------------------------------------------------------------
LPDIRECTSOUND ds_Create(HWND window, REFCLSID clsid_direct, LPGUID device,
	int level)
{
	// ��������� ����������
	LPDIRECTSOUND direct = 0;

	// ������������� COM
	CoInitialize(NULL);

	// �������� Direct Sound �������
	if (CoCreateInstance(clsid_direct,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IDirectSound,
			(void * *) &direct) != DS_OK)
		return false;

	// ������������� ���������� ���������������
	if (direct->Initialize(device) != DS_OK)
		return false;

	// ��������� ������������� ������
	if (direct->SetCooperativeLevel(window, level) != DS_OK)
		return false;

	return direct;
}

//-----------------------------------------------------------------------------
//	������������ Direct Sound �������
// �� �����    :  direct   - ��������� �� Direct Sound ������
// �� ������   :	*
//-----------------------------------------------------------------------------
void ds_Release(LPDIRECTSOUND direct)
{
	// �������� ������� ���������������
	if (direct)
		direct->Release();

	// ������������ COM
	CoUninitialize();
}

//-----------------------------------------------------------------------------
//	�������� ���������� ������
// �� �����    :  direct   - ��������� �� Direct Sound ������
// �� ������   :	��������� �� ��������� �����, � ������ ���� �������� ����� 0
//  			  ������ �������� �� ����������
//-----------------------------------------------------------------------------
LPDIRECTSOUNDBUFFER ds_CreatePrimary(LPDIRECTSOUND direct)
{
	DSBUFFERDESC dsbd;
	LPDIRECTSOUNDBUFFER primary;

	// ������ �� ������
	if (!direct)
		return 0;

	// �������� ������ ��� ��������� ������� � ���������� ������
	ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwFlags = DSBCAPS_PRIMARYBUFFER |
		DSBCAPS_CTRL3D |
		DSBCAPS_CTRLVOLUME;
	dsbd.dwBufferBytes = 0;
	dsbd.lpwfxFormat = NULL;

	// ��������� ������� � ���������� ������
	if (direct->CreateSoundBuffer(&dsbd, & primary, NULL) != DS_OK)
		return 0;

	return primary;
}

//-----------------------------------------------------------------------------
//	������������ ���������� ������
// �� �����    :  primary  - ��������� �� ��������� �����
// �� ������   :	*
//-----------------------------------------------------------------------------
void ds_ReleasePrimary(LPDIRECTSOUNDBUFFER primary)
{
	if (primary)
		primary->Release();
}

//-----------------------------------------------------------------------------
//	�������� ���������
// �� �����    :  primary  - ��������� �� ��������� �����
// �� ������   :	��������� �� ��������� ���������, � ������ ���� ��������
//  			  ����� 0 ������ �������� �� ����������
//-----------------------------------------------------------------------------
LPDIRECTSOUND3DLISTENER ds_CreateListener(LPDIRECTSOUNDBUFFER primary)
{
	LPDIRECTSOUND3DLISTENER listener;

	if (!primary)
		return 0;

	// ��������� ��������� �� ��������� ���������
	if (primary->QueryInterface(IID_IDirectSound3DListener,
				 	(void * *) &listener) == DS_OK)
		return listener;

	return 0;
}

//-----------------------------------------------------------------------------
//	������������ ���������� ���������
// �� �����    :  listener  - ��������� �� ��������� ���������
// �� ������   :	*
//-----------------------------------------------------------------------------
void ds_ReleaseListener(LPDIRECTSOUND3DLISTENER listener)
{
	if (listener)
		listener->Release();
}

//-----------------------------------------------------------------------------
//	��������� ���� ���������� ���������
// �� �����    :  listener - ��������� �� ��������� ���������
//  			  data     - ��������� �� ��������� � ������� ����� ���������
//  						 ��������� ���������
// �� ������   :	���������� ��������� ���������� ���������
//-----------------------------------------------------------------------------
int ds_GetAllListenerParameters(LPDIRECTSOUND3DLISTENER listener,
	LPDS3DLISTENER data)
{
	// �������� ������� ���������
	if (!listener)
		return false;

	// �������� ������ ���������
	data->dwSize = sizeof(DS3DLISTENER);

	// ��������� ���������� ���������
	if (listener->GetAllParameters(data) == DS_OK)
		return true;

	return false;
}

//-----------------------------------------------------------------------------
//	��������� ���� ���������� ���������
// �� �����    :  listener - ��������� �� ��������� ���������
//  			  data     - ��������� �� ��������� � ������� ����������
//  						 ��������� ���������
// �� ������   :	���������� ��������� ���������� ���������
//-----------------------------------------------------------------------------
int ds_SetAllListenerParameters(LPDIRECTSOUND3DLISTENER listener,
	LPDS3DLISTENER data, DWORD def)
{
	int ret = false;

	// �������� ������� ���������
	if (!listener)
		return ret;

	// ��������� �������
	ret = (listener->SetPosition(data->vPosition.x,
					 	data->vPosition.y,
					 	data->vPosition.z,
					 	def) == DS_OK) ?
		true :
		false;

	// ��������� �������� ���������
	if (ret)
		ret = (listener->SetVelocity(data->vVelocity.x,
						 	data->vVelocity.y,
						 	data->vVelocity.z,
						 	def) == DS_OK) ?
			true :
			false;

	// ��������� ����������
	if (ret)
		ret = (listener->SetOrientation(data->vOrientFront.x,
						 	data->vOrientFront.y,
						 	data->vOrientFront.z,
						 	data->vOrientTop.x,
						 	data->vOrientTop.y,
						 	data->vOrientTop.z,
						 	def) == DS_OK) ?
			true :
			false;

	// ��������� ���������
	if (ret)
		ret = (listener->SetDistanceFactor(data->flDistanceFactor, def) ==
			DS_OK) ?
			true :
			false;

	// ��������� ������� ��������
	if (ret)
		ret = (listener->SetRolloffFactor(data->flRolloffFactor, def) == DS_OK) ?
			true :
			false;

	// ��������� ������� ��������
	if (ret)
		ret = (listener->SetDopplerFactor(data->flDopplerFactor, def) == DS_OK) ?
			true :
			false;

	return ret;
}

//-----------------------------------------------------------------------------
//	���������������� ���������� ������
// �� �����    :  primary  - ��������� �� ��������� �����
//  			  rate     - ������� �������������
//  			  bits     - ���������� ��� �� �������
//  			  channels - ���������� �������
// �� ������   :	���������� ���������������� ���������� �����
//-----------------------------------------------------------------------------
int ds_ConfigurePrimary(LPDIRECTSOUNDBUFFER primary, int rate, int bits,
	int channels)
{
	WAVEFORMATEX wfx;

	if (!primary)
		return false;

	// ��������� ������ � ������� ���������� ��������� ������
	ZeroMemory(&wfx, sizeof(WAVEFORMATEX)); 
	wfx.wFormatTag = WAVE_FORMAT_PCM; 
	wfx.nChannels = channels;
	wfx.nSamplesPerSec = rate;
	wfx.wBitsPerSample = bits;
	wfx.nBlockAlign = wfx.wBitsPerSample / 8 * wfx.nChannels;
	wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;

	// �������������� ���������� ������
	if (primary->SetFormat(&wfx) != DS_OK)
		return false;

	return true;
}

//-----------------------------------------------------------------------------
//	�������� ����������� ������������� ��������� ����������� �����
// �� �����    :  direct   - ��������� ��������� Direct Sound
//  			  alg      - ����������� �������
// �� ������   :	���������� �������������
//-----------------------------------------------------------------------------
int ds_TestAlgorithm(LPDIRECTSOUND direct, int alg)
{
	// ���������� ����������
	int ret;
	DSBUFFERDESC dsbd;
	WAVEFORMATEX wfx;
	LPDIRECTSOUNDBUFFER buffer;

	// �������� ��������� � ��������
	wfx.wFormatTag = 1;
	wfx.nChannels = 2;
	wfx.nSamplesPerSec = 44100;
	wfx.wBitsPerSample = 16;
	wfx.nBlockAlign = (wfx.nChannels * wfx.wBitsPerSample) >> 3;
	wfx.nAvgBytesPerSec = wfx.nBlockAlign * wfx.nSamplesPerSec;
	wfx.cbSize = 0;

	// �������� ������� ������� ���������������
	if (direct) {
		// ��������� ������ ���������� ������
		ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
		dsbd.dwSize = sizeof(DSBUFFERDESC);
		dsbd.dwFlags = DSBCAPS_STATIC |
			DSBCAPS_CTRLFREQUENCY |
			DSBCAPS_CTRLVOLUME |
			DSBCAPS_GLOBALFOCUS |
			DSBCAPS_CTRL3D |
			DSBCAPS_MUTE3DATMAXDISTANCE;
		dsbd.dwBufferBytes = 128;
		dsbd.lpwfxFormat = &wfx;
		/* !!! ������ !!!
					// ������ ������� ������ ����������� �����
					switch(alg)
				  {
						case 0x0:
						dsbd.guid3DAlgorithm = DS3DALG_DEFAULT;
						break;
						case 0x1:
						dsbd.guid3DAlgorithm = DS3DALG_NO_VIRTUALIZATION;
						break;
						case 0x2:
						dsbd.guid3DAlgorithm = DS3DALG_HRTF_FULL;
						break;
						case 0x3:
						dsbd.guid3DAlgorithm = DS3DALG_HRTF_LIGHT;
						break;
					}*/

		// �������� ���������� ������
		ret = (direct->CreateSoundBuffer(&dsbd, & buffer, NULL) == DS_OK) ?
			true :
			false;
		if (ret)
			buffer->Release();
	}

	// ������ ���������
	return ret;
}

//-----------------------------------------------------------------------------
//	��������� ���������� ���������� ���������������
// �� �����    :  direct   - ��������� ��������� Direct Sound
//  			  caps     - ��������� �� ��������� ����������� ���������
//  						 ���������� ���������������
// �� ������   :	���������� ��������� ����������
//-----------------------------------------------------------------------------
int ds_GetCaps(LPDIRECTSOUND direct, LPDSCAPS caps)
{
	// �������� ������� �������
	if (direct) {
		caps->dwSize = sizeof(DSCAPS);
		// ��������� ������� �������
		if (direct->GetCaps(caps) == DS_OK)
			return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
//	�������� ��������� ������
// �� �����    :  direct   - ��������� ��������� Direct Sound
//  			  desc     - ��������� �� ��������� ����������� ���������
//  						 ������������ ������
// �� ������   :	��������� �� ��������� �������� �����, ���� �������� ����� 0
//  			  ������ �������� �� ����������
//-----------------------------------------------------------------------------
LPDIRECTSOUNDBUFFER ds_CreateBuffer(LPDIRECTSOUND direct, LPDSBUFFERDESC desc)
{
	LPDIRECTSOUNDBUFFER buffer = 0;

	// �������� ������� Direct Sound �������
	if (!direct)
		return 0;

	// �������� ���������� ������
	if (direct->CreateSoundBuffer(desc, & buffer, NULL) == DS_OK)
		return buffer;

	// �������� �� ����������
	return 0;
}

//-----------------------------------------------------------------------------
//	������������ ��������� ������
// �� �����    :  buffer   - ��������� �� �������� �����
// �� ������   :	*
//-----------------------------------------------------------------------------
void ds_ReleaseBuffer(LPDIRECTSOUNDBUFFER buffer)
{
	if (buffer)
		buffer->Release();
}

//-----------------------------------------------------------------------------
//	��������� ����������� ���������� ��� ��������� ������
// �� �����    :  buffer   - ��������� �� �������� ����� ��� �������� �����
//  						 �������� ���������� ���������
// �� ������   :	��������� �� ��������� ���������� ���������, ���� ��������
//  			  ����� 0 ������ ��������� �� ����������
//-----------------------------------------------------------------------------
LPDIRECTSOUND3DBUFFER ds_Get3DInterface(LPDIRECTSOUNDBUFFER buffer)
{
	LPDIRECTSOUND3DBUFFER buffer3d = 0;

	// �������� ������� ��������� ������
	if (!buffer)
		return 0;

	// ��������� ����������� ����������
	if (buffer->QueryInterface(IID_IDirectSound3DBuffer, (VOID * *) buffer3d) ==
		DS_OK)
		return buffer3d;

	// ��������� �� ����������
	return 0;
}

//-----------------------------------------------------------------------------
//	������������ ����������� ���������� ��������� ������
// �� �����    :  buffer   - ��������� �� ���������� ��������� ��������� ������
// �� ������   :	*
//-----------------------------------------------------------------------------
void ds_Release3DInterface(LPDIRECTSOUND3DBUFFER buffer3d)
{
	if (buffer3d)
		buffer3d->Release();
}