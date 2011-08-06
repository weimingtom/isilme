#include "CDXOutput.h"
#include "HiddenWindow.h"

/////////////////////////////////////////////////
// �������
/////////////////////////////////////////////////
#define DX_DEVICE_GROWBY	  4

// ����������� ����������
int CDXOutput::_init = 0;
dx_device_list_t CDXOutput::_deviceList;

//-----------------------------------------------------------------------------
// ��������� ��������� ������ ������ ���������
// �� �����    :  Id	- ������������� ����������
//  			  Desc  - ��� ����������
//  			  Mod   - ��� ����� � ���������
//  			  Data  - ��������� �� ������ ��������� ���������
// �� ������   :  TRUE  - ���������� ������������
//  			  FALSE - ��������� ������������
//-----------------------------------------------------------------------------
BOOL CALLBACK dx_DirectSoundEnumerate(LPGUID Id, LPSTR Desc, LPSTR Mod,
	HWND hWnd)
{
	int i;
	LPDIRECTSOUND direct;
	LPDIRECTSOUNDBUFFER primary;
	LPDIRECTSOUND3DLISTENER listener;
	dx_device_t* device;

	// ���������� ����������
	direct = 0;
	primary = 0;
	device = 0;

	// �������� Direct Sound �������
	direct = ds_Create(hWnd, CLSID_DirectSound, Id, DSSCL_EXCLUSIVE);

	// �������� ���������� ������
	primary = ds_CreatePrimary(direct);

	// �������� ���������
	listener = ds_CreateListener(primary);

	// ���������������� ���������� ������ ������ ?
	if (ds_ConfigurePrimary(primary, 44100, 16, 2)) {
		// ����� ���������� ���� ��� ���������� ?
		if (CDXOutput::_deviceList._size == CDXOutput::_deviceList._capacity)
			CDXOutput::DeviceGrowArray();

		// �������� ����� ������ ��� ����� ����������
		device = (dx_device_t *) malloc(sizeof(dx_device_t));
		memset(device, 0, sizeof(dx_device_t));

		// �������� �������������
		device->_id = Id;

		// ��������� ��� ��������
		i = (strlen(Desc) > (DEVICE_NAME_LEN - 1)) ?
			DEVICE_NAME_LEN -
			1 :
			strlen(Desc);
		memcpy(device->_name, Desc, i);
		device->_name[i] = 0;

		// ��������� ���������� ���������� ���������������
		if (ds_GetCaps(direct, & device->_caps)) {
			// �������� ������� ���������� ������� 3D �����
			for (i = 0; i < 4; i++)
				device->_alg[i] = ds_TestAlgorithm(direct, i);

			// �������� ������� EAX �����������
			for (i = 0; i <= EAX_NUM; i++)
				device->_eax[i] = eax_TestSupport(direct, i);

			// �������� ������� ZOOMFX
			device->_zoomfx = zoomfx_TestSupport(direct);

			// ��������� ������ �������� � ������
			i = CDXOutput::_deviceList._size++;
			CDXOutput::_deviceList._array[i] = device;
		} else {
			// ��������� ������
			free(device);
		}
	}

	// ������������ ���������
	ds_ReleaseListener(listener);

	// ������������ ���������� ������
	ds_ReleasePrimary(primary);

	// ������������ ���������� ���������������
	ds_Release(direct);

	// ���������� �����
	return TRUE;
}

//-----------------------------------------------------------------------------
// C������� ������ ��������� ���������������
// �� �����    :
// �� ������   :
//-----------------------------------------------------------------------------
int CDXOutput::CreateDeviceList(void)
{
	HWND hWnd = 0;

	// �������� ������� ��������� ���������������
	if (waveOutGetNumDevs() == 0)
		return false;

	// �������� �������� ����
	hWnd = CreateHiddenWindow();
	if (!hWnd)
		return false;

	// ������������ ���� ��������� ���������������
	DirectSoundEnumerate((LPDSENUMCALLBACK) dx_DirectSoundEnumerate, hWnd);

	// �������� �������� ����
	ReleaseHiddenWindow(hWnd);

	return true;
}

//-----------------------------------------------------------------------------
// C������� ������ ��������� ���������������
// �� �����    :
// �� ������   :
//-----------------------------------------------------------------------------
void CDXOutput::DeviceGrowArray(void)
{
	dx_device_t** newlist;

	// ���������� �������
	_deviceList._capacity += DX_DEVICE_GROWBY;

	// ��������� ������ �������
	newlist = (dx_device_t * *)
		malloc(_deviceList._capacity * sizeof(dx_device_t *));

	// ���������� ������ �������
	memset(newlist, 0, _deviceList._capacity * sizeof(dx_device_t *));

	// ����������� ������� ������� � �����
	if (_deviceList._size > 0)
		memcpy(newlist,
			_deviceList._array,
			_deviceList._size * sizeof(dx_device_t *));

	// ������������ ������� �������
	free(_deviceList._array);

	// ������� ����� ������ � ����
	_deviceList._array = newlist;
}

//-----------------------------------------------------------------------------
// ���������� ������ � ������
// �� �����    :  *
// �� ������   :  *
//-----------------------------------------------------------------------------
void CDXOutput::Startup()
{
	if (_init == 0) {
		// ��������� ������
		memset(&_deviceList, 0, sizeof(dx_device_list_t));

		// �������� ��������� ��� �������� ������ ���������
		DeviceGrowArray();

		// �������� ������ ���������
		CreateDeviceList();

		// ���� �������������
		_init = 1;
	}
}

//-----------------------------------------------------------------------------
// ���������� ������ � �������
// �� �����    :  *
// �� ������   :  *
//-----------------------------------------------------------------------------
void CDXOutput::Shutdown()
{
	_init = 0;
}


//-----------------------------------------------------------------------------
// ����������� ������
// �� �����    :  *
// �� ������   :  *
//-----------------------------------------------------------------------------
CDXOutput::CDXOutput()
{
	Startup();
}

//-----------------------------------------------------------------------------
// ���������� ������
// �� �����    :  *
// �� ������   :  *
//-----------------------------------------------------------------------------
CDXOutput::~CDXOutput()
{
	Shutdown();
}

//-----------------------------------------------------------------------------
// ������������� DirectSound
// �� �����    :  iWindow     - ������� ���� � �������� �������� ������
//  			  iDe�ive     - ������������� ���������� ���������������
//  			  iRate 	  - ������� ������������� �����
//  			  iBits 	  - ���������� ��� �� �������
//  			  iChannels   - ���������� �������
// �� ������	:	���������� ������������� DirectSound
//-----------------------------------------------------------------------------
int CDXOutput::Init(HWND iWindow, unsigned int iDevice, int iRate, int iBits,
	int iChannels)
{
	int ok = false;
	// ������� ����������
	_directSound = 0;
	_primary = 0;
	_listener = 0;

	// �������� ������ ����������
	ok = (iDevice < (unsigned int)_deviceList._size) ? true : false;

	// �������� Direct Sound �������
	if (ok) {
		_directSound = ds_Create(iWindow,
					   	CLSID_DirectSound,
					   	_deviceList._array[iDevice]->_id,
					   	DSSCL_EXCLUSIVE);
		ok = _directSound ? true : false;
	}

	// �������� ���������� ������
	if (ok) {
		_primary = ds_CreatePrimary(_directSound);
		ok = _primary ? true : false;
	}

	// �������� ���������
	if (ok) {
		_listener = ds_CreateListener(_primary);
		ok = _listener ? true : false;
	}

	// ��������� ���������� ���������
	if (ok)
		ok = ds_GetAllListenerParameters(_listener, & _listenerParameters);

	// ���������������� ���������� ������
	if (ok)
		ok = ds_ConfigurePrimary(_primary, iRate, iBits, iChannels);

	// � ������ ������ ��������� ��� ��� ������
	if (!ok)
		Free();

	// ��� ������ �������
	return ok;
}

//-----------------------------------------------------------------------------
// ������������ DirectSound �������
// �� �����		:	*
// �� ������	:	���������� ��������������� DirectSound
//-----------------------------------------------------------------------------
void CDXOutput::Free(void)
{
	// ������������ ���������� ���������
	ds_ReleaseListener(_listener);

	// ������������ ���������� ������
	ds_ReleasePrimary(_primary);

	// ������������ DirectSound ����������
	ds_Release(_directSound);

	// ������� ����������
	_listener = 0;
	_primary = 0;
	_directSound = 0;
}

//-----------------------------------------------------------------------------
// ��������� ���������� ��������� ���������������
// �� �����    :  
// �� ������   :  
//-----------------------------------------------------------------------------
int CDXOutput::GetNumDevice(void)
{
	// ������������� ����
	Startup();

	// ������ ���������� ��������� ���������������
	return _deviceList._size;
}

//-----------------------------------------------------------------------------
// ��������� ����� ���������� ���������������
// �� �����    :  iDevice  - ���������� ����� ���������� � ������
// �� ������   :  ��������� �� ������ � ������ ����������
//-----------------------------------------------------------------------------
char* CDXOutput::GetDeviceName(int iDevice)
{
	// ������������� ����
	Startup();

	// ����� ���������� ���� ?
	if (iDevice >= _deviceList._size)
		return 0;

	// ������ ���
	return _deviceList._array[iDevice]->_name;
}
/*
//-----------------------------------------------------------------------------
// ��������� �������������� ���������� ���������������
// �� �����    :  iDevice  - ���������� ����� ���������� � ������
// �� ������   :  ������������� ����������
//-----------------------------------------------------------------------------
LPGUID CDXOutput::GetDeviceID(int iDevice)
{
   // ������������� ����
   Startup();

   // ����� ���������� ���� ?
   if (iDevice >= _deviceList._size)
	  return NULL;

   // ������ �������������
   return _deviceList._array[iDevice]->_id;
}
*/
//-----------------------------------------------------------------------------
// ��������� ��������� �� ������ ����������
// �� �����    :  iDevice  - ���������� ����� ���������� � ������
// �� ������   :  ��������� �� ������ ����������
//-----------------------------------------------------------------------------
dx_device_t* CDXOutput::GetDevice(int device)
{
	// ������������� ����
	Startup();

	// ����� ���������� ���� ?
	if (device >= _deviceList._size)
		return 0;

	// ������ �������������
	return _deviceList._array[device];
}
