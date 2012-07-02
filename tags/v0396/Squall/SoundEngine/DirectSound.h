//-----------------------------------------------------------------------------
// ������ � Direct Sound
// �������� ��������� ��������� Squall
// �������     : AntiTank
// ����������� : ������������ ����� (�����)
//-----------------------------------------------------------------------------
#ifndef _DIRECT_SOUND_H_INCLUDED_
#define _DIRECT_SOUND_H_INCLUDED_

#include <dsound.h>

// �������� Direct Sound �������
LPDIRECTSOUND ds_Create(HWND window, REFCLSID clsid_irect, LPGUID device,
	int level);

// �������� Direct Sound �������
void ds_Release(LPDIRECTSOUND direct);

// �������� ���������� ������
LPDIRECTSOUNDBUFFER ds_CreatePrimary(LPDIRECTSOUND direct);

void ds_ReleasePrimary(LPDIRECTSOUNDBUFFER primary);

// ���������������� ���������� ������
int ds_ConfigurePrimary(LPDIRECTSOUNDBUFFER primary, int rate, int bits,
	int channels);

// �������� ��������� ��������� ������� 3D
int ds_TestAlgorithm(LPDIRECTSOUND direct, int alg);

// ��������� ���������� ���������� ���������������
int ds_GetCaps(LPDIRECTSOUND direct, LPDSCAPS caps);

// ��������� ���������� ���������
LPDIRECTSOUND3DLISTENER ds_CreateListener(LPDIRECTSOUNDBUFFER primary);

// ������������ ���������� ���������
void ds_ReleaseListener(LPDIRECTSOUND3DLISTENER listener);

// ��������� ���� ���������� ���������
int ds_GetAllListenerParameters(LPDIRECTSOUND3DLISTENER listener,
	LPDS3DLISTENER data);

// ��������� ���� ���������� ���������
int ds_SetAllListenerParameters(LPDIRECTSOUND3DLISTENER listener,
	LPDS3DLISTENER data, DWORD def);

// �������� ��������� ������
LPDIRECTSOUNDBUFFER ds_CreateBuffer(LPDIRECTSOUND direct, LPDSBUFFERDESC desc);

// ������������ ��������� ������
void ds_ReleaseBuffer(LPDIRECTSOUNDBUFFER buffer);

// ��������� 3� ����������
LPDIRECTSOUND3DBUFFER ds_Get3DInterface(LPDIRECTSOUNDBUFFER buffer);

// ������������ 3� ����������
void ds_Release3DInterface(LPDIRECTSOUND3DBUFFER buffer3d);
#endif