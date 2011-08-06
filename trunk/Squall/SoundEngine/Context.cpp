//-----------------------------------------------------------------------------
//	������ �� ��������� ��������
//	�������� ��������� ��������� �����
//	�������		: AntiTank
//	�����������	: ������������ ����� (�����)
//-----------------------------------------------------------------------------

// ���������
#include <stdio.h>
#include <dsound.h>
#include <math.h>
#include "Squall.h"
#include "Context.h"
#include "SquallApi.h"
#include "DirectSound.h"

//-----------------------------------------------------------------------------
// ������������� DirectSound
// �� �����		:	hWnd			- ������� ���� � �������� �������� ������
//					De�ive			- ������������� ���������� ���������������
//					SampleRate		- ������� ������������� �����
//					BitsPerSample	- ���������� ��� �� �������
//					Channels		- ���������� �������
// �� ������	:	���������� ������������� DirectSound
//-----------------------------------------------------------------------------
int context_s::InitAudio(HWND window, LPGUID device, int rate, int bits,
	int channels)
{
	int ok = false;
	// ������� ����������
	_directSound = 0;
	_primary = 0;
	_listener = 0;

	// �������� Direct Sound �������
	_directSound = ds_Create(window,
				   	CLSID_DirectSound,
				   	device,
				   	DSSCL_EXCLUSIVE);
	ok = _directSound ? true : false;

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
		ok = ds_ConfigurePrimary(_primary, rate, bits, channels);

	// � ������ ������ ��������� ��� ��� ������
	if (!ok)
		FreeAudio();

	// ��� ������ �������
	return ok;
}

//-----------------------------------------------------------------------------
// ������������ DirectSound �������
// �� �����		:	*
// �� ������	:	���������� ��������������� DirectSound
//-----------------------------------------------------------------------------
void context_s::FreeAudio(void)
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
// ��������� ������ ������ �� ��������������
// �� �����    :  ChannelID   - ������������� �������� ������
// �� ������   :  ����� ������, � ������ ������� -1
//-----------------------------------------------------------------------------
int context_s::GetChannelIndex(int ChannelID)
{
	int index;
	int count;

	index = ChannelID & 0xFF;
	count = ChannelID >> 8;

	// �������� �������
	if (index >= _channels)
		return -1;

	// �������� ��������
	if (_channelsArray[index]._count != count)
		return -1;

	// �������� ������������ ������
	if (_channelsArray[index].Status.STAGE == EMPTY)
		return -1;

	return index;
}

//-----------------------------------------------------------------------------
//	��������� ������ ������ �� ��������������
//	�� �����	:	Priority	- ��������� ������������ ������
//	�� ������	:	����� ���������� ������, ���� �������� ����� -1
//					��� ��������� �������.
//-----------------------------------------------------------------------------
int context_s::GetFreeChannel(int Priority)
{
	// ����������
	int index;
	float Dist = 0.0f;
	float direct = 0.0f;

	// �������� ������� ���������� ������
	for (int i = 0; i < _channels; i++) {
		// ����� �������� ?
		if (_channelsArray[i].Status.STAGE == EMPTY) {
			index = i;
			break;
		} else {
			// ����� ����������� ����������
			if (Priority >= _channelsArray[i].Priority) {
				Priority = _channelsArray[i].Priority;
				index = i;
				/*  		  // ���������� ��������� �� ��������� �����
								 if( _channelsArray[i].DS3D_Buffer != 0 )
								 {
									direct = sqrtf(   powf((_listenerParameters.vPosition.x - _channelsArray[i].Param.ds3d.vPosition.x), 2) +
													  powf((_listenerParameters.vPosition.y - _channelsArray[i].Param.ds3d.vPosition.y), 2) + 
													  powf((_listenerParameters.vPosition.z - _channelsArray[i].Param.ds3d.vPosition.z), 2));
									if( Dist <= direct )
									{
										   index = i;
									   Dist = direct;
									}
								 }*/
			}
		}
	}

	// ����� ����� ?
	if (_channelsArray[index].Status.STAGE != EMPTY)
		_channelsArray[index].DeleteSoundBuffer();


	return index;
}

int context_s::GetChannelID(int ChannelIndex)
{
	// ���������� ������
	if (_channelsArray[ChannelIndex]._count > 0xFFFF)
		_channelsArray[ChannelIndex]._count = 1;
	else
		_channelsArray[ChannelIndex]._count++;

	return _channelsArray[ChannelIndex]._count << 8 | ChannelIndex;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//				��������� ��� ������ �� �������� �������
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//	���������� �������� ������� � ����
//	�� �����	:	��������� �� ������ ��������� ���������
//	�� ������	:	0 - ����� ������
//-----------------------------------------------------------------------------
DWORD WINAPI SoundThreadProc(LPVOID param)
{
	DWORD result;
	int i;
	context_s* Data = (context_s*) param;
	SSample* cur;

	// ����������� ����
	while (Data->_event) {
		// ��������� �����
		if (WaitForSingleObject(Data->_event, 5) == WAIT_TIMEOUT) {
			// �������� ����������� ���������
			result = WaitForSingleObject(Data->_mutex, 5);

			// ������ ��������
			if (result == WAIT_FAILED) {
				return 0;
			}

			// ����� ������������
			if (result == WAIT_OBJECT_0) {
				// ��������� ���� ������
				for (i = 0, cur = (SSample*) Data->_channelsArray;
					i < Data->_channels;
					i++, cur++) {
					// ����� ���� ?
					if (cur->Status.STAGE != EMPTY) {
						// ���������� ������
						if (!cur->Update(Data->_listenerParameters.vPosition.x,
								  	Data->_listenerParameters.vPosition.y,
								  	Data->_listenerParameters.vPosition.z)) {
							// �������� ������ � ������ ������
							cur->Stop();
							cur->DeleteSoundBuffer();
						}
					}
				}

				// ��������� ���� ������
				for (i = 0, cur = (SSample*) Data->_channelsArray;
					i < Data->_channels;
					i++, cur++) {
					if (cur->Status.STAGE != EMPTY) // ����� ���� ?
						cur->UpdateWorker();
				}

				// ������� ���������� ���������
				if (Data->_worker) {
					if ((timeGetTime() - Data->_prevWorkerTime) >
						Data->_workerUpdateTime) {
						Data->_prevWorkerTime = timeGetTime();
						// ����� �����������
						Data->_worker(Data->_workerUserData);
					}
				}

				// ��������� ������
				ReleaseMutex(Data->_mutex);
			}
		}
	}
	return 0;
}

//-----------------------------------------------------------------------------
//	��������� �������� ����������� ������� � ����
//	�� �����	:	*
//	�� ������	:	���������� �������� ����������� �����
//-----------------------------------------------------------------------------
bool context_s::CreateSoundThread(void)
{
	// �������� �������
	if (!(_event = CreateEvent(0, TRUE, 0, 0))) {
		return false;
	}

	// �������� ����������� 
	if (!(_thread = CreateThread(NULL,
						0,
						(LPTHREAD_START_ROUTINE) SoundThreadProc,
						(LPVOID)this,
						0,
						& _threadID))) {
		return false;
	}

	// ��������� ����������
	if (SetThreadPriority(_thread, THREAD_PRIORITY_TIME_CRITICAL) == NULL) {
		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------
//	�������� ����������� �������� �������
//	�� �����	:	*
//	�� ������	:	���������� �������� ����������� �����
//-----------------------------------------------------------------------------
void context_s::DeleteSoundThread(void)
{
	// ���� ���� �����, �� ������ ���
	if (_thread) {
		TerminateThread(_thread, 0);
		_thread = 0;
	}

	// ���� ���� ���������������� ������� �� ������ ���
	if (_event) {
		CloseHandle(_event);
		_event = 0;
	}
}

//-----------------------------------------------------------------------------
//	������������� EAX ���������
//	�� �����	:	��������� �� ���������� � ������� ����� ��������� EAX
//					���������
//	�� ������	:	����������
//-----------------------------------------------------------------------------
int context_s::InitAudioExtensions(void)
{
	// ���������� ����������
	int i, ok;
	WAVEFORMATEX wfx;		// ������ �����
	DSBUFFERDESC dsbd;		// ����������
	device_t* device;  // ��������� �� ��������� ���������� ���������������


	// ���������� ����������
	for (i = 0; i <= EAX_NUM; i++)
		_eaxSupport[i] = 0;
	_useEax = 0;
	_zoomfxSupport = 0;

	_eaxBuffer = 0;
	_eaxListener = 0;

	// ��������� ���������� � �������� �����������
	device = api_GetDevice(_curDevice);
	if (!device)
		return false;

	// ��������� ��������� � EAX �����������
	for (i = 0; i <= EAX_NUM; i++) {
		_eaxSupport[i] = device->_eax[i];
		if (device->_eax[i])
			_useEax = i;
	}

	// ��������� ��������� � ZOOMFX ����������
	_zoomfxSupport = device->_zoomfx;

	// �������� ��������� � ��������
	wfx.wFormatTag = 1;
	wfx.nChannels = 2;
	wfx.nSamplesPerSec = 44100;
	wfx.wBitsPerSample = 16;
	wfx.nBlockAlign = (wfx.nChannels * wfx.wBitsPerSample) >> 3;
	wfx.nAvgBytesPerSec = wfx.nBlockAlign * wfx.nSamplesPerSec;
	wfx.cbSize = 0;

	// ��������� ������ ���������� ������
	ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwFlags = DSBCAPS_STATIC | DSBCAPS_CTRL3D;
	dsbd.dwBufferBytes = 128;
	dsbd.lpwfxFormat = &wfx;

	// �������� ������� ���������� ���������������
	ok = _directSound ? true : false;

	// �������� ���������� ������
	if (ok) {
		_eaxBuffer = ds_CreateBuffer(_directSound, & dsbd);
		ok = _eaxBuffer ? true : false;
	}

	// ��������� EAX ����������
	if (ok) {
		_eaxListener = eax_GetBufferInterface(_eaxBuffer);
		ok = _eaxListener ? true : false;
	}

	// � ������ ������ ��������� ������� �������
	if (!ok)
		FreeAudioExtensions();

	return ok;
}

//-----------------------------------------------------------------------------
//	������������ EAX ���������
//	�� �����	:	*
//	�� ������	:	*
//-----------------------------------------------------------------------------
void context_s::FreeAudioExtensions(void)
{
	// ��������� ��������� EAX ���������
	if (_eaxListener) {
		_eaxListener->Release();
		_eaxListener = 0;
	}

	// ��������� EAX �����
	ds_ReleaseBuffer(_eaxBuffer);
	_eaxBuffer = 0;
}

//-----------------------------------------------------------------------------
//	��������� ������ �������� ���������� ���������������
// �� �����    :  cur_device  - ����� �������� ���������� ��������������� 
//  			  new_device  - ����� ������ ���������� ���������������
// �� ������   :	���������� ��������� ������ ���������� ���������������
//-----------------------------------------------------------------------------
int context_s::SetDevice(DWORD cur_device, DWORD new_device)
{
	int result = true;

	// ���������� ��������� ��� �������� ������������� ������
	struct SSaveBuffer {
		SChannelParam Param;
		int PlayPosition;
	};

	int i;
	int ret;		// ������������ ��������
	int channel = 0;				 // ������� �������������� �����
	LPGUID NewDevice = 0;   			  // ������������� ������ ���������� ���������������
	LPGUID CurDevice = 0;   			  // ������������� �������� ���������� ���������������
	DS3DLISTENER temp_list;  // ����� � �������������� ����������� ���������
	SSaveBuffer* temp;  	 // ����� � ������� ���� �������

	temp = 0;
	i = 0;

	CurDevice = api_GetDeviceID(cur_device);
	NewDevice = api_GetDeviceID(new_device);

	// �������� ��������� �������
	if (IsTrue(result)) {
		// ������� ������ ��� ������������� �����
		temp = (SSaveBuffer *) malloc(sizeof(SSaveBuffer) * _channels);

		// ������ �������� ������
		for (channel = 0; channel < _channels; channel++) {
			if (_channelsArray[channel].Status.STAGE != EMPTY) {
				// �������� ��������� ������
				memcpy(&temp[channel].Param,
					& _channelsArray[channel].Param,
					sizeof(SChannelParam));
				_channelsArray[channel].GetPlayPosition(&temp[channel].PlayPosition);

				// ������ ����� 3D
				if (_channelsArray[channel].DS3D_Buffer) {
					_channelsArray[channel].DS3D_Buffer->Release();
					_channelsArray[channel].DS3D_Buffer = 0;
				}
				// ������ �����
				if (_channelsArray[channel].DS_Buffer) {
					_channelsArray[channel].DS_Buffer->Release();
					_channelsArray[channel].DS_Buffer = 0;
				}
			}
		}
		// �������� ��������� ���������
		memcpy(&temp_list, & _listenerParameters, sizeof(DS3DLISTENER));

		// ������ ��������� EAX ���������
		FreeAudioExtensions();

		// ������ ������� ���������� ���������������
		FreeAudio();
	}

	// ��������� ������ ���������� ���������������
	if (IsTrue(result))
		if (!InitAudio(_window, NewDevice, _sampleRate, _bitPerSample, 2))
			result = SQUALL_ERROR_CREATE_DIRECT_SOUND;

	// ������������� �������� ����������
	if (IsTrue(result)) {
		InitAudioExtensions();

		// ���������� ��������� ���������
		memcpy(&_listenerParameters, & temp_list, sizeof(DS3DLISTENER));
		if (!ds_SetAllListenerParameters(_listener,
			 	& _listenerParameters,
			 	DS3D_IMMEDIATE))
			result = SQUALL_ERROR_SET_LISTENER_PARAM;
	}


	// ���������� �������� ������
	if (IsTrue(result)) {
		for (channel = 0; channel < _channels; channel++) {
			if (_channelsArray[channel].Status.STAGE != EMPTY) {
				if (_channelsArray[channel].Status.SOUND_TYPE ==
					TYPE_POSITIONED) {
					// �������� ������					   
					ret = _channelsArray[channel].Create3DSoundBuffer(_directSound,
												  	_channelsArray[channel].SoundFile->GetFormat(),
												  	_channelsArray[channel].SoundFile->GetRealMonoDataSize(),
												  	_bufferSize,
												  	_used3DAlgorithm,
												  	_useEax,
												  	_useHW3D);
					// ���������� � ��������� ����������
					if (ret) {
						memcpy(&_channelsArray[channel].Param,
							& temp[channel].Param,
							sizeof(SChannelParam));
						ret = (_channelsArray[channel].DS3D_Buffer->SetAllParameters(&_channelsArray[channel].Param.ds3d,
																		DS3D_IMMEDIATE) ==
							DS_OK) ?
							true :
							false;
					}
					// ��������� ���������
					if (ret)
						ret = _channelsArray[channel].SetVolume(temp[channel].Param.Volume);
					// ��������� �������
					if (ret)
						ret = _channelsArray[channel].SetFrequency(temp[channel].Param.Frequency);
					// ��������� ������� ���������������
					if (ret)
						ret = _channelsArray[channel].SetPlayPosition(temp[channel].PlayPosition);
				} else {
					// �������� ������
					ret = _channelsArray[channel].CreateSoundBuffer(_directSound,
												  	_channelsArray[channel].SoundFile->GetFormat(),
												  	_channelsArray[channel].SoundFile->GetRealStereoDataSize(),
												  	_bufferSize,
												  	_useHW2D);
					// ��������� ���������
					if (ret)
						ret = _channelsArray[channel].SetVolume(temp[channel].Param.Volume);
					// ��������� �������
					if (ret)
						ret = _channelsArray[channel].SetFrequency(temp[channel].Param.Frequency);
					// ��������� ��������
					if (ret)
						ret = _channelsArray[channel].SetPan(temp[channel].Param.Pan);
					// ��������� ������� ���������������
					if (ret)
						ret = _channelsArray[channel].SetPlayPosition(temp[channel].PlayPosition);
				}

				// �������� ������� ������
				if (!ret) {
					break;
				}
			}
		}
	}
	/*
	   // � ������ ������� ������ ��� �������
	   if (error)
	   {
		  // ������ ��������� EAX ���������
		   FreeAudioExtensions();
		   // ������ ������� ���������� ���������������
		   FreeAudio();
		   // �������� ����� ���������� ���������������
		   error = (InitAudio(hWnd, CurDevice, SampleRate, BitPerSample, 2)) ? AGSS_NO_ERROR : AGSS_ERROR_CREATE_DIRECT_SOUND;
		   if (!error)
		  {
			   // ���������� ��������� ���������
			   memcpy(&_listenerParameters, &temp_list, sizeof(DS3DLISTENER));
			   error = (ds_SetAllListenerParameters(_listener, &_listenerParameters, DS3D_IMMEDIATE)) ? AGSS_NO_ERROR : AGSS_ERROR_SET_LISTENER_PARAMETERS;
		   }
		   // ���������� EAX ���������
		   InitAudioExtensions();
		   // ���������� �������� ������
		   if (!error)
		  {
			   for (channel = 0; channel < _channels; channel++)
			 {
				   if (_channelsArray[channel].Status.STAGE != EMPTY)
				{
					   if (_channelsArray[channel].Status.SOUND_TYPE == TYPE_POSITIONED)
				   {
					  // �������� ������					   
					  ret = _channelsArray[channel].Create3DSoundBuffer(_directSound, _channelsArray[channel].SoundFile->GetFormat(), _channelsArray[channel].SoundFile->GetRealMonoDataSize(), BufferSize, Used3DAlgorithm, _useEax, HardwareAcceleration3D);
					  // ���������� � ��������� ����������
					  if (ret)
					  {
							  memcpy(&_channelsArray[channel].Param, &temp[channel].Param, sizeof(SChannelParam));
							  ret = (_channelsArray[channel].DS3D_Buffer->SetAllParameters(&_channelsArray[channel].Param.ds3d, DS3D_IMMEDIATE) == DS_OK) ? true : false;
					  }
					  // ��������� ���������
					  if (ret)
							  ret = _channelsArray[channel].SetVolume(temp[channel].Param.Volume);
					  // ��������� �������
						   if (ret)
							  ret = _channelsArray[channel].SetFrequency(temp[channel].Param.Frequency);
					  // ��������� ������� ���������������
						   if (ret)
							  ret = _channelsArray[channel].SetPlayPosition(temp[channel].PlayPosition);
					   } else
				   {
					  // �������� ������
						   ret = _channelsArray[channel].CreateSoundBuffer(_directSound, _channelsArray[channel].SoundFile->GetFormat(), _channelsArray[channel].SoundFile->GetRealStereoDataSize(), BufferSize, HardwareAcceleration2D);
					  // ��������� ���������
						   if (ret)
							  ret = _channelsArray[channel].SetVolume(temp[channel].Param.Volume);
					  // ��������� �������
						   if (ret)
							   ret = _channelsArray[channel].SetFrequency(temp[channel].Param.Frequency);
					  // ��������� ��������
						   if (ret)
							  ret = _channelsArray[channel].SetPan(temp[channel].Param.Pan);
					  // ��������� ������� ���������������
						   if (ret)
							  ret = _channelsArray[channel].SetPlayPosition(temp[channel].PlayPosition);
					   }
				   // �������� ������� ������
				   if (!ret)
					  break;
				   }
			   }
		   }
	   }
	*/
	if (temp)
		free(temp);

	return ret;
}
