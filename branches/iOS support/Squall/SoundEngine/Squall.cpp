//-----------------------------------------------------------------------------
// �������� ���������
// �������� ��������� ��������� �����
// �������     : AntiTank
// ����������� : ������������ ����� (�����)
//-----------------------------------------------------------------------------

// ���������
#include <stdio.h>
#include <math.h>
#include "Squall.h"
#include "Eax.h"
#include "ZoomFX.h"
#include "SoundFile.h"
#include "Context.h"
#include "Channels.h"
#include "Reader.h"

#include "SquallApi.h"
#include "HiddenWindow.h"
#include "DirectSound.h"

#include "CDXOutput.h"

// ������������ ����������
#pragma comment(lib, "dxguid")
#pragma comment(lib, "dsound")
#pragma comment(lib, "winmm")

// ������ ������, �������� ������ � ���������� ������ ���������
#if SQUALL_DEBUG
static const char* ErrorTable[] = {
	"", "SQUALL_ERROR_NO_SOUND", "SQUALL_ERROR_MEMORY",
	"SQUALL_ERROR_UNINITIALIZED", "SQUALL_ERROR_INVALID_PARAM",
	"SQUALL_ERROR_CREATE_WINDOW", "SQUALL_ERROR_CREATE_DIRECT_SOUND",
	"SQUALL_ERROR_CREATE_THREAD", "SQUALL_ERROR_SET_LISTENER_PARAM",
	"SQUALL_ERROR_GET_LISTENER_PARAM", "SQUALL_ERROR_NO_FREE_CHANNEL",
	"SQUALL_ERROR_CREATE_CHANNEL", "SQUALL_ERROR_CHANNEL_NOT_FOUND",
	"SQUALL_ERROR_SET_CHANNEL_PARAM", "SQUALL_ERROR_GET_CHANNEL_PARAM",
	"SQUALL_ERROR_METHOD", "SQUALL_ERROR_ALGORITHM", "SQUALL_ERROR_NO_EAX",
	"SQUALL_ERROR_EAX_VERSION", "SQUALL_ERROR_SET_EAX_PARAM",
	"SQUALL_ERROR_GET_EAX_PARAM", "SQUALL_ERROR_NO_ZOOMFX",
	"SQUALL_ERROR_SET_ZOOMFX_PARAM", "SQUALL_ERROR_GET_ZOOMFX_PARAM",
	"SQUALL_ERROR_UNKNOWN", "SQUALL_ERROR_SAMPLE_INIT",
	"SQUALL_ERROR_SAMPLE_BAD", "SQUALL_ERROR_SET_MIXER_PARAM",
	"SQUALL_ERROR_GET_MIXER_PARAM", 
};
#endif

// ������� ��� �������������� ���������
int volume_table[100];

int naturalvolume_to_dxvolume( float volume )
{
	if( volume == 0 ) // andrewp: log10(0) is undefined
		return -10000;

	return (int)floorf(10000.0f * .5f * log10f(volume));
}

int dxvolume_to_squallvolume( int dxvolume )
{
	int result = (int)floorf(100 * expf(dxvolume * (2.303f / (10000.0f * .5f)))); // andrewp: this must correlate with 'volume_table'

	if( result < 0 )
		result = 0;
	else
	if( result > 100 )
		result = 100;
	
	return result;
}

//-----------------------------------------------------------------------------
// �������� ���������� 
// �� �����    :  in	- ��������� �� ��������� � �������� �����������
//  			  out   - ��������� �� ��������� ���� ����� ���������
//  					  �������������� ��������
// �� ������   :  *
//-----------------------------------------------------------------------------
void InitParameters(squall_parameters_t* in, squall_parameters_t* out)
{
	// �������� ������� �����������
	if (IsBadReadPtr(in, sizeof(squall_parameters_t))) {
		// �������� ���������� �� ���������
		memset(out, 0, sizeof(squall_parameters_t));
	} else {
		// ��������� ��� ����
		memcpy(out, in, sizeof(squall_parameters_t));
	}

	// �������� ������� �����
	if (out->SampleRate <= 0)
		out->SampleRate = 44100;
	else if (out->SampleRate > 48000)
		out->SampleRate = 48000;

	// �������� ���������� ���
	if ((out->BitPerSample != 8) && (out->BitPerSample != 16))
		out->BitPerSample = 16;

	// �������� ������� ������������� ���������� �������
	if (out->Channels <= 0)
		out->Channels = 16;
	else if (out->Channels > 256)
		out->Channels = 256;

	// �������� ������� ��������� ������
	if (out->BufferSize <= 0)
		out->BufferSize = 200;
	else if (out->BufferSize > 5000)
		out->BufferSize = 5000;

	// �������� ��������� ��������� ����������� ������������
	if ((out->UseAlg < 0) || (out->UseAlg > SQUALL_ALG_3D_LIGHT))
		out->UseAlg = SQUALL_ALG_3D_DEFAULT;

	// �������� ������ ������ ���������
	if ((out->ListenerMode != 0) && (out->ListenerMode != 1))
		out->ListenerMode = SQUALL_LISTENER_MODE_IMMEDIATE;

	// ������ ���������
	if (out->DistanceFactor <= 0.0f) // ��������� �� ����� ���� ������������� ��� ������ 0
		out->DistanceFactor = 1.0f;

	// ������ ��������� ����� � ����������� �� ���������
	if (out->RolloffFactor <= 0.0f)
		out->RolloffFactor = 1.0f;
	else if (out->RolloffFactor > 10.0f)
		out->RolloffFactor = 10.0f;

	// ������� ������
	if (out->DopplerFactor <= 0.0f)
		out->DopplerFactor = 1;
	else if (out->DopplerFactor > 10.0f)
		out->DopplerFactor = 10.0f;

	// ������ �� ���������� ����������� 2D
	if ((out->UseHW2D != 0) && (out->UseHW2D != 1))
		out->UseHW2D = true;

	// ������ �� ���������� ����������� 3D
	if ((out->UseHW3D != 0) && (out->UseHW3D != 1))
		out->UseHW3D = true;

	// �������� ����
	if (!IsWindow((HWND) out->Window))
		out->Window = 0;

	// �������� ���������� ���������������
	if ((out->Device <= 0) || (out->Device >= api_GetNumDevice()))
		out->Device = 0;
}

//-----------------------------------------------------------------------------
// ������������ ������� � ���������
// �� �����    :  context  - ��������� �� ����������� ��������
// �� ������   :  *
//-----------------------------------------------------------------------------
void LockContext(context_t* context)
{
	// �������� ������� ���������
	if (!context)
		return;

	// ����� ������� ?
	if (context->_threadID != GetCurrentThreadId())
		WaitForSingleObject(context->_mutex, INFINITE);
}

//-----------------------------------------------------------------------------
// ��������������� ������� � ���������
// �� �����    :  context  - ��������� �� �������������� ��������
// �� ������   :  *
//-----------------------------------------------------------------------------
void UnlockContext(context_t* context)
{
	// �������� ������� ���������
	if (!context)
		return;

	// ����� ������� ?
	if (context->_threadID != GetCurrentThreadId())
		ReleaseMutex(context->_mutex);
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//  			   ������ ������������� / ������������
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// ������������� �������� ������� �����
// �� �����    :  
// SystemParam -  ��������� �� ��������� � �����������
//  		��������� ��������� ��� �������������.
//  		���� �������� ����� ����� 0 �� ��������
//  		��������� ������� ��������� ������� �
//  		���������� �����������:
// Window 		= 0 	(������� ���� ����)
// Device 		= 0 	(���������� �� ���������)
// SampleRate 		= 44100
// BitPerSample		= 16
// Channels   		= 16
// UseHW2D		= true  (������������)
// UseHW3D		= true  (������������)
// UseAlg 		= 0 	(�������� �� ���������)
// BufferSize 		= 200
// ListenerMode		= 0 	(����������� ����������)
// DistanceFactor	= 1.0f
// RolloffFactor	= 1.0f
// DopplerFactor	= 1.0f
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Init(squall_parameters_t* SystemParam)
#else
DLL_API int SQUALL_Init(squall_parameters_t* SystemParam)
#endif
{
	// ����������
	int i = 0;
	context_t* context = 0;
	LPGUID device = 0;
	HWND hidden = 0;
	int result = true;
	bool init = false;
	squall_parameters_t sys;

	// �������� �������������� ������
#ifndef _USRDLL
	if (IsBadReadPtr(this, sizeof(this)))
		result = SQUALL_ERROR_UNINITIALIZED;
#endif

	// �������� ������� ���������� ���������������
	if (IsTrue(result))
		if (api_GetNumDevice() == 0)
			result = SQUALL_ERROR_NO_SOUND;


	// �������� ������� ����������
	for (i = 0; i < 100; ++i)
		volume_table[i] = naturalvolume_to_dxvolume(i * (1 / 99.0f));

	// �������� ������� ����������
	InitParameters(SystemParam, & sys);

	// �������� ������� ���� � �������� ����� ����������� ���������
	if (IsTrue(result))
		if (!sys.Window) {
			// �������� �������� ����
			hidden = CreateHiddenWindow();
			if (!hidden)
				result = SQUALL_ERROR_CREATE_WINDOW;
			else
				sys.Window = hidden;
		}

#ifndef _USRDLL
	// ��������� ������ ��� ������ ���������
	if (IsTrue(result)) {
		context = api_CreateContext(this);
		if (!context)
			result = SQUALL_ERROR_MEMORY;
	}
#else
	context = &api._context;
#endif

	// ����������� ������ � ���������
	LockContext(context);

	// ��������� ����������
	if (IsTrue(result)) {
		// �������� ������
		while (context->_mutex == 0)
			context->_mutex = CreateMutex(0, 0, 0);

		// ����������� ����������
		context->_bitPerSample = sys.BitPerSample;
		context->_sampleRate = sys.SampleRate;
		context->_channels = sys.Channels;
		context->_bufferSize = sys.BufferSize;
		context->_used3DAlgorithm = sys.UseAlg;
		context->_deferred = sys.ListenerMode ?
			DS3D_DEFERRED :
			DS3D_IMMEDIATE;
		context->_useHW2D = sys.UseHW2D;
		context->_useHW3D = sys.UseHW3D;
		context->_curDevice = sys.Device;

		// ���������� �������
		context->_prevWorkerTime = timeGetTime();
		context->_hiddenWindow = hidden;
		context->_window = (HWND) sys.Window;

		// ���������� ����������
#if SQUALL_DEBUG
		// ������� ��������� � �������� ��������� ���������
		api_LogTime("SQUALL_Init(0x%X)", (void *) SystemParam);
		api_Log("\t\t[out]Window                   = 0x%X", sys.Window);
		api_Log("\t\t[out]Device                   = %d", sys.Device);
		api_Log("\t\t[out]SampleRate               = %d", sys.SampleRate);
		api_Log("\t\t[out]BitPerSample             = %d", sys.BitPerSample);
		api_Log("\t\t[out]Channels                 = %d", sys.Channels);
		api_Log("\t\t[out]UseAlg                   = %d", sys.UseAlg);
		api_Log("\t\t[out]BufferSize               = %d", sys.BufferSize);
		api_Log("\t\t[out]ListenerMode             = %d", sys.ListenerMode);
		api_Log("\t\t[out]DistanceFactor           = %f", sys.DistanceFactor);
		api_Log("\t\t[out]RolloffFactor            = %f", sys.RolloffFactor);
		api_Log("\t\t[out]DopplerFactor            = %f", sys.DopplerFactor);
		api_Log("\t\t[out]UseHW2D                  = %d", sys.UseHW2D);
		api_Log("\t\t[out]UseHW3D                  = %d", sys.UseHW3D);
#endif

		// ������� ������ ��� ������ ������
		context->_channelsArray = (SSample *)
			api_malloc(sizeof(SSample) * context->_channels);
		if (context->_channelsArray) {
			// ������� ���������
			memset(context->_channelsArray,
				0,
				sizeof(SSample) * context->_channels);
		} else {
			// ������ ��������� ������
			result = SQUALL_ERROR_MEMORY;
		}
	}

	if (IsTrue(result)) {
		// ��������� ��������� �� ������������� ���������� ���������������
		device = api_GetDeviceID(sys.Device);

		// ������������� �������� �������
		if (!context->InitAudio(context->_window,
					  	device,
					  	context->_sampleRate,
					  	context->_bitPerSample,
					  	2))
			result = SQUALL_ERROR_CREATE_DIRECT_SOUND;
	}

	// ������������� �������� ����������
	if (IsTrue(result))
		context->InitAudioExtensions();

	// ��������� ��������� ���������
	if (IsTrue(result)) {
		context->_listenerParameters.flRolloffFactor = sys.RolloffFactor;
		context->_listenerParameters.flDopplerFactor = sys.DopplerFactor;
		context->_listenerParameters.flDistanceFactor = sys.DistanceFactor;
		if (!ds_SetAllListenerParameters(context->_listener,
			 	& context->_listenerParameters,
			 	DS3D_IMMEDIATE))
			result = SQUALL_ERROR_SET_LISTENER_PARAM;
	}

	// �������� ����������� �������� �������
	if (IsTrue(result))
		if (!context->CreateSoundThread())
			result = SQUALL_ERROR_CREATE_THREAD;

	// �������� ������� ������ � ������ ��� ��������
	if (IsFalse(result)) {
		// �������� ����������� �������� �������
		context->DeleteSoundThread();

		// ������������ �������� ����������
		context->FreeAudioExtensions();

		// ������������ �������� �������
		context->FreeAudio();

		// ������ ������ �� �������
		api_free(context->_channelsArray);
		context->_channelsArray = 0;

		// ������ ������� ����
		ReleaseHiddenWindow(context->_hiddenWindow);
		context->_hiddenWindow = 0;
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ������ ������
	UnlockContext(context);
	return result;
}
//-----------------------------------------------------------------------------
// ������������ ������� �������� �������� ��������
// �� �����    :  *
// �� ������   :  *
//-----------------------------------------------------------------------------
#ifndef _USRDLL
void Squall::Free(void)
#else
DLL_API void SQUALL_Free(void)
#endif
{
	context_t* context = 0;
	int result = true;

#ifndef _USRDLL
	// ��������� ���������
	context = api_GetContext(this);
	if (!context)
		result = SQUALL_ERROR_UNINITIALIZED;
#else
	context = &api._context;
#endif

#if SQUALL_DEBUG
	api_LogTime("SQUALL_Free()");
#endif

	// ����������� ������ ������
	LockContext(context);

	if (context->_channelsArray) {
		// ��������� � ������ ��� ������
		for (int i = 0; i < context->_channels; i++) {
			context->_channelsArray[i].Stop();
			context->_channelsArray[i].DeleteSoundBuffer();
		}
	}

	// ��������� �����
	Sleep(500);

	// �������� ����������� �������� �������
	context->DeleteSoundThread();

	// ������������ �������� ����������
	context->FreeAudioExtensions();

	// ������������ �������� �������
	context->FreeAudio();

	// ������ ������ �� �������
	if (context->_channelsArray) {
		api_free(context->_channelsArray);
		context->_channelsArray = 0;
	}

	// ������ ������� ����
	if (context->_hiddenWindow) {
		DestroyWindow(context->_hiddenWindow);
		context->_hiddenWindow = 0;
	}

	// ������������ ������ ������
	UnlockContext(context);

	// ����� ������
	if (context->_mutex) {
		CloseHandle(context->_mutex);
		context->_mutex = 0;
	}

#ifndef _USRDLL
	// ������ ����������
	if (context)
		api_ReleaseContext(this);
#else
	memset(context, 0, sizeof(context_t));
#endif

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif
	// ������������ ����
	api_Shutdown();
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//  				  ������ ���������� ����������
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// ���������/���������� ����� ���� �������� �������
// �� �����    :  Pause -  ���� ���������/���������� �����
//  					   �������� ����� ��������� ��������� ��������
//  					   true  - �������� �����
//  					   false - ��������� �����
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Pause(int Pause)
#else
DLL_API int SQUALL_Pause(int Pause)
#endif
{
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Pause(%d)", Pause);
#endif

	// ������������ ��� ����� � ������
	if (IsTrue(result))
		for (int i = 0; i < context->_channels; i++)
			if (context->_channelsArray[i].Status.STAGE != EMPTY)
				context->_channelsArray[i].Pause(Pause);

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}
//-----------------------------------------------------------------------------
// ��������� ���� �������� �������
// �� �����    :  *
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Stop(void)
#else
DLL_API int SQUALL_Stop(void)
#endif
{
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Stop()");
#endif

	// ��������� ��������������� ���� �������
	if (IsTrue(result))
		for (int i = 0; i < context->_channels; i++)
			if (context->_channelsArray[i].Status.STAGE != EMPTY)
				context->_channelsArray[i].Stop();

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//  					������ ��������� ���������
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// ��������� ������ ���������� ���������������
// �� �����    :  Num   -  ����� ������ ���������� ���������������, �������� 
//  					   ��������� ������ ���� � �������� �� 0 �� ��������
#ifndef _USRDLL
//  					   ����������� � ������� ������ GetNumDevice.
#else
//  					   ����������� � ������� ������ SQUALL_GetNumDevice.
#endif
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::SetDevice(int Num)
#else
DLL_API int SQUALL_SetDevice(int Num)
#endif
{
	// ������ �� ������
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_SetDevice(%d)", Num);
#endif

	// �������� ����������
	if (IsTrue(result))
		if ((Num < 0) || (Num >= api_GetNumDevice()))
			result = SQUALL_ERROR_INVALID_PARAM;

	// ��������� ������ ���������� ���������������
	if (IsTrue(result))
		context->SetDevice(context->_curDevice, Num);

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("error = %s", ErrorTable[-result]);
#endif

	// ������������ ������ ������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ������ �������� ���������� ���������������
// �� �����    :  *
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//  			  � ������ ��������� ������ ��������� �������� ����� ��������
//  			  ���������� ���������������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::GetDevice(void)
#else
DLL_API int SQUALL_GetDevice(void)
#endif
{
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_GetDevice()");
#endif

	// ������ ����� �������� ����������
	if (IsTrue(result))
		result = context->_curDevice;

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("error = %s", ErrorTable[-result]);
	else
		api_Log("\t\tresult = %d", result);
#endif

	// ������������ ������ ������
	UnlockContext(context);
	return result;
}
//-----------------------------------------------------------------------------
// ���������/���������� ������������� ���������� ����������� �����
// �� �����    :  UseHW2D  -  ���� ������������ ������������� ����������
//  						  ����������� ���������� �������� �������,
//  						  �������� ����� ��������� ��������� ��������:
//  						  true   - ������������ ���������� �����������
//  						  false  - �� ������������ ���������� �����������
//  			  UseHW3D  -  ���� ������������ ������������� ����������
//  						  ����������� ����������� �������� �������
//  						  �������� ����� ��������� ��������� ��������:
//  						  true   - ������������ ���������� �����������
//  						  false  - �� ������������ ���������� �����������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::SetHardwareAcceleration(int UseHW2D, int UseHW3D)
#else
DLL_API int SQUALL_SetHardwareAcceleration(int UseHW2D, int UseHW3D)
#endif
{
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_SetHardwareAcceleration(%d, %d)", UseHW2D, UseHW3D);
#endif

	// ��������� ������ ���������� ���������������
	if (IsTrue(result)) {
		context->_useHW2D = UseHW2D;
		context->_useHW3D = UseHW3D;
		context->SetDevice(context->_curDevice, context->_curDevice);
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("error = %s", ErrorTable[-result]);
#endif

	// ������������ ������ ������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ������� �������� ������������� ���������� ����������� �����
// �� �����    :  UseHW2D  -  ��������� �� ���������� � ������� ����� ���������
//  						  ������� �������� ������������� ����������
//  						  ����������� ��� ���������� �������� �������
//  			  UseHW3D  -  ��������� �� ���������� � ������� ����� ���������
//  						  ������� �������� ������������� ����������
//  						  ����������� ��� ����������� �������� �������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::GetHardwareAcceleration(int* UseHW2D, int* UseHW3D)
#else
DLL_API int SQUALL_GetHardwareAcceleration(int* UseHW2D, int* UseHW3D)
#endif
{
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_GetHardwareAcceleration(0x%X, 0x%X)", UseHW2D, UseHW3D);
#endif

	if (IsBadWritePtr(UseHW2D, sizeof(int)))
		UseHW2D = 0;

	if (IsBadWritePtr(UseHW3D, sizeof(int)))
		UseHW3D = 0;

	// �������� ����������
	if (IsTrue(result))
		if ((UseHW2D == 0) && (UseHW3D == 0))
			result = SQUALL_ERROR_INVALID_PARAM;

	// ��������� ������ ���������� ���������������
	if (IsTrue(result)) {
		if (UseHW2D)
			*UseHW2D = context->_useHW2D;
		if (UseHW3D)
			*UseHW3D = context->_useHW3D;
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("error = %s", ErrorTable[-result]);
	else {
		if (UseHW2D)
			api_Log("UseHW2D = %d", * UseHW2D);
		if (UseHW3D)
			api_Log("UseHW3D = %d", * UseHW3D);
	}
#endif

	// ������������ ������ ������
	UnlockContext(context);
	return result;
}
//-----------------------------------------------------------------------------
// ��������� ������ ���������
// �� �����    :  Mode  -  ������������� ������, �������� ����� ���������
//  					   ��������� ��������:
//  					   SQUALL_SPEAKER_DEFAULT   - ��������� �� ���������
//  					   SQUALL_SPEAKER_HEADPHONE - �������� (�������� ��������)
//  					   SQUALL_SPEAKER_MONO  	- ���� ������� (1.0)
//  					   SQUALL_SPEAKER_STEREO	- ������ ������� (2.0)
//  					   SQUALL_SPEAKER_QUAD  	- ������ ������� (4.0)
//  					   SQUALL_SPEAKER_SURROUND  - ������ ������� � �������
//  												  ������ �������� (4.1)
//  					   SQUALL_SPEAKER_5POINT1   - ���� ��������� ������� �
//  												  ������� ������ �������� (5.1)
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::SetSpeakerMode(int Mode)
#else
DLL_API int SQUALL_SetSpeakerMode(int Mode)
#endif
{
	unsigned int   mode;
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_SetSpeakerMode(%d)", Mode);
#endif

	// �������� ����������
	if (IsTrue(result))
		if ((Mode < 0) || (Mode > SQUALL_SPEAKER_5POINT1))
			result = SQUALL_ERROR_INVALID_PARAM;

	// ����������� ���� ���������
	if (IsTrue(result)) {
		mode = 0;
		switch (Mode) {
		case SQUALL_SPEAKER_HEADPHONE:
			mode = DSSPEAKER_HEADPHONE;
			break;
		case SQUALL_SPEAKER_MONO:
			mode = DSSPEAKER_MONO;
			break;
		case SQUALL_SPEAKER_STEREO:
			mode = DSSPEAKER_STEREO;
			break;
		case SQUALL_SPEAKER_QUAD:
			mode = DSSPEAKER_QUAD;
			break;
		case SQUALL_SPEAKER_SURROUND:
			mode = DSSPEAKER_SURROUND;
			break;
			//  	   case SQUALL_SPEAKER_5POINT1:
			//  		  mode = DSSPEAKER_5POINT1;
			//  		  break;
			//  	   case SQUALL_SPEAKER_7POINT1:
			//  		  mode = DSSPEAKER_7POINT1;
			//  		break;
		}
	}

	// ��������� ���� ���������
	if (IsTrue(result))
		if ((!context->_directSound) ||
			(context->_directSound->SetSpeakerConfig(mode) != DS_OK))
			result = SQUALL_ERROR_UNKNOWN;

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("error = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
//	��������� �������� ������ ���������
//	�� �����	:  *
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//  			  � ������ ��������� ������ ��������� �������� ����� ��������
//  			  ������ ���������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::GetSpeakerMode(void)
#else
DLL_API int SQUALL_GetSpeakerMode(void)
#endif
{
	unsigned long  mode = 0;
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_GetSpeakerMode()");
#endif

	// ��������� ���� ���������
	if (IsTrue(result))
		if ((!context->_directSound) ||
			(context->_directSound->GetSpeakerConfig(&mode) != DS_OK))
			result = SQUALL_ERROR_UNKNOWN;

	// ����������� ���� ���������
	if (IsTrue(result)) {
		switch (DSSPEAKER_CONFIG(mode)) {
		case DSSPEAKER_HEADPHONE:
			result = SQUALL_SPEAKER_HEADPHONE;
			break;
		case DSSPEAKER_MONO:
			result = SQUALL_SPEAKER_MONO;
			break;
		case DSSPEAKER_STEREO:
			result = SQUALL_SPEAKER_STEREO;
			break;
		case DSSPEAKER_QUAD:
			result = SQUALL_SPEAKER_QUAD;
			break;
		case DSSPEAKER_SURROUND:
			result = SQUALL_SPEAKER_SURROUND;
			break;
			//  	   case DSSPEAKER_5POINT1:
			//  		  result = SQUALL_SPEAKER_5POINT1;
			//  		  break;
			//  	   case DSSPEAKER_7POINT1:
			//  		  result = SQUALL_SPEAKER_7POINT1;
			//  		break;
		}
	}


	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else
		api_Log("\t\tresult = %d", result);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}
//-----------------------------------------------------------------------------
// ��������� ��������� ������� ����������� �����
// �� �����    :  Algoritm -  ��� ������������ ��������� ������� �����
//  						  �������� ����� ��������� ��������� ��������:
//  						  SQUALL_ALG_3D_DEFAULT - �������� �� ���������
//  						  SQUALL_ALG_3D_OFF 	- 2D ��������
//  						  SQUALL_ALG_3D_FULL	- ����������� 3D ��������
//  						  SQUALL_ALG_3D_LIGTH   - ����������� 3D ��������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Set3DAlgorithm(int Algorithm)
#else
DLL_API int SQUALL_Set3DAlgorithm(int Algorithm)
#endif
{
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Set3DAlgorithm(%d)", Algorithm);
#endif

	// �������� ����������
	if (IsTrue(result))
		if ((Algorithm < 0) || (Algorithm > SQUALL_ALG_3D_LIGHT))
			result = SQUALL_ERROR_INVALID_PARAM;

	// �������� ��������� ���������
	if (IsTrue(result))
		if (context->_support3DAlgTab[Algorithm])
			context->_support3DAlgTab[Algorithm] = Algorithm;
		else
			result = SQUALL_ERROR_ALGORITHM;

		// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� �������� ��������� ������� ����������� �����
// �� �����    :  *
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//  			  � ������ ��������� ������ ��������� �������� ����� ��������
//  			  ��������� ������� ����������� �����, ��������� �����
//  			  ��������� ��������� ��������:
//  			  SQUALL_ALG_3D_DEFAULT - �������� �� ���������
//  			  SQUALL_ALG_3D_OFF 	- 2D ��������
//  			  SQUALL_ALG_3D_FULL	- ����������� 3D ��������
//  			  SQUALL_ALG_3D_LIGTH   - ����������� 3D ��������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Get3DAlgorithm(void)
#else
DLL_API int SQUALL_Get3DAlgorithm(void)
#endif
{
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Get3DAlgorithm()");
#endif

	// ��������� ���������
	if (IsTrue(result))
		result = context->_used3DAlgorithm;

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else
		api_Log("\t\tresult = %d", result);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}
//-----------------------------------------------------------------------------
// ��������� ������ ������� ��������� ������ � ������������
// �� �����    :  BufferSize  -  ����� ������ ��������� ������, � ������������
//  							 �������� ������ ������ � �������� �� 200
//  							 �� 5000
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::SetBufferSize(int BufferSize)
#else
DLL_API int SQUALL_SetBufferSize(int BufferSize)
#endif
{
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_SetBufferSize(%d)", BufferSize);
#endif

	// �������� ����������
	if ((BufferSize <= 0) || (BufferSize > 5000))
		result = SQUALL_ERROR_INVALID_PARAM;

	// ��������� ���������
	if (IsTrue(result))
		context->_bufferSize = BufferSize;

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� �������� ������� ��������� ������ � ������������
// �� �����    :  *
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//  			  � ������ ��������� ������ ��������� �������� ������� ������
//  			  ��������� ������ � ������������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::GetBufferSize(void)
#else
DLL_API int SQUALL_GetBufferSize(void)
#endif
{
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_GetBufferSize()");
#endif

	// ��������� ���������
	if (IsTrue(result))
		result = context->_bufferSize;

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else
		api_Log("\t\tresult = %d", result);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}
//-----------------------------------------------------------------------------
// ��������� ������� ������� ������ � �������
// �� �����    :  UserAlloc   -  ��������� �� ������� ����� ��������� ������
//  			  UserFree    -  ��������� �� ������� ����� ������������ ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::SetMemoryCallbacks(squall_callback_alloc_t UserAlloc,
	squall_callback_free_t UserFree)
#else
DLL_API int SQUALL_SetMemoryCallbacks(squall_callback_alloc_t UserAlloc,
	squall_callback_free_t UserFree)
#endif
{
	int result = true;

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_SetMemoryCallbacks(0x%X, 0x%X)", UserAlloc, UserFree);
#endif

	// �������� ����������
	if (IsBadCodePtr((FARPROC) UserAlloc) || IsBadCodePtr((FARPROC) UserFree))
		result = SQUALL_ERROR_INVALID_PARAM;

	// ��������� ������� ������� ������ � �������
	api_SetMemoryCallbacks(UserAlloc, UserFree);

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	return result;
}

//-----------------------------------------------------------------------------
// ��������� ������� ������� ��� ������ � �������
// �� �����    :  UserOpen    -  ��������� �� ������� ����� �������� ������
//  			  UserSeek    -  ��������� �� ������� ����� ����������������
//  							 � �������� �����
//  			  UserRead    -  ��������� �� ������� ����� ������ ������ ��
//  							 ��������� �����
//  			  UserClose   -  ��������� �� ������� ����� �������� ���������
//  							 �����
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::SetFileCallbacks(squall_callback_open_t UserOpen,
	squall_callback_seek_t UserSeek, squall_callback_read_t UserRead,
	squall_callback_close_t UserClose)
#else
DLL_API int SQUALL_SetFileCallbacks(squall_callback_open_t UserOpen,
	squall_callback_seek_t UserSeek, squall_callback_read_t UserRead,
	squall_callback_close_t UserClose)
#endif
{
	int result = true;

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_SetFileCallbacks(0x%X, 0x%X, 0x%X, 0x%X)",
		UserOpen,
		UserSeek,
		UserRead,
		UserClose);
#endif

	// �������� ����������
	if (IsBadCodePtr((FARPROC) UserOpen) ||
		IsBadCodePtr((FARPROC) UserRead) ||
		IsBadCodePtr((FARPROC)
			UserSeek) ||
		IsBadCodePtr((FARPROC)
			UserClose))
		result = SQUALL_ERROR_INVALID_PARAM;

	// ��������� ������� ������� ������ � �������
	api_SetFileCallbacks(UserOpen, UserRead, UserSeek, UserClose);

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	return result;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//  			  ������ ��� ��������� ���������� � �������
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// ��������� ���������� ��������� ��������������� �����
// �� �����    :  *
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������.
//  			  � ������ ��������� ������ ��������� �������� ����������
//  			  ��������� ��������������� � �������. ���� � ������� ���
//  			  ��������� ��������������� ��������� ����� ����� 0.
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::GetNumDevice(void)
#else
DLL_API int SQUALL_GetNumDevice(void)
#endif
{
	int result = true;

	CDXOutput* dx = 0;//new CDXOutput();

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_GetNumDevice()");
#endif

	// ������� ���������� ��������� ���������������
	//result = api_GetNumDevice();
	result = dx->GetNumDevice();

	// ���������� ����������
#if SQUALL_DEBUG
	api_Log("\t\tresult = %d", result);
#endif

	// ������ ��������� ������
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ����� ���������� �� ��������� ������
// �� �����    :  Num      -  ����� ����������, �������� ��������� ������ ����
//  						  � �������� �� 0 �� �������� ����������� � �������
#ifndef _USRDLL
//  						  ������ GetNumDevice.
#else
//  						  ������ SQUALL_GetNumDevice.
#endif
//  			  Buffer   -  ��������� �� ����� ���� ����� ��������� ���
//  						  ���������� ���������������
//  			  Size     -  ������ ������������ ������ � ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::GetDeviceName(int Num, char* Name, int Len)
#else
DLL_API int SQUALL_GetDeviceName(int Num, char* Name, int Len)
#endif
{
	int length;
	char* name;
	int result = true;

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_GetDeviceName(%d, 0x%X, %d)", Num, Name, Len);
#endif

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

	// �������� ����������
	if (IsTrue(result))
		if ((Len <= 0) ||
			(Num < 0) ||
			(Num >= api_GetNumDevice()) ||
			IsBadWritePtr(Name,
																	  	Len))
			result = SQUALL_ERROR_INVALID_PARAM;

	// ��������� ��������� �� ��� ���������� ���������������
	if (IsTrue(result)) {
		name = api_GetDeviceName(Num);
		if (!name)
			result = SQUALL_ERROR_UNKNOWN;
	}

	// ����������� ����� � ��������� �����
	if (IsTrue(result)) {
		length = ((int) strlen(name) > (Len - 1)) ? Len - 1 : strlen(name);
		memcpy(Name, name, length);
		Name[length] = 0;
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("error = %s", ErrorTable[-result]);
	else
		api_Log("\t\t[out]*Name = %s", Name);
#endif

	// ��������� ������
	return result;
}
//-----------------------------------------------------------------------------
// ��������� ������� ���������� ��������������� �� ��������� ������
// �� �����    :  Num   -  ����� ����������, �������� ��������� ������ ���� �
//  					   �������� �� 0 �� �������� ����������� � �������
#ifndef _USRDLL
//  					   ������ GetNumDevice.
#else
//  					   ������ SQUALL_GetNumDevice.
#endif
//  			  Caps  -  ��������� �� ��������� � ������� ����� ���������
//  					   �������� ���������� ���������������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::GetDeviceCaps(int Num, squall_device_caps_t* Caps)
#else
DLL_API int SQUALL_GetDeviceCaps(int Num, squall_device_caps_t* Caps)
#endif
{
	device_t* dev;
	int result = true;

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_GetDeviceCaps(%d, 0x%X)", Num, Caps);
#endif

	// �������� ������� ���������� ���������������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

	// �������� ����������
	if (IsTrue(result))
		if ((Num < 0) ||
			(Num >= api_GetNumDevice()) ||
			IsBadWritePtr(Caps,
				sizeof(squall_device_caps_t)))
			result = SQUALL_ERROR_INVALID_PARAM;

	// ��������� ��������� ����������
	if (IsTrue(result)) {
		// ���������� ��������� ����� �����������
		memset(Caps, 0, sizeof(squall_device_caps_t));

		// ��������� ��������� �� ������ ���������� ���������������
		dev = api_GetDevice(Num);
		if (dev) {
			// �������� ������� ����������� ���������� �������
			if (dev->_caps.dwFreeHwMixingAllBuffers != 0) {
				Caps->HardwareChannels = dev->_caps.dwFreeHwMixingAllBuffers;
				Caps->Flags |= SQUALL_DEVICE_CAPS_HARDWARE;
			}

			// �������� ������� ���������� ���������� 3D �������
			if (dev->_caps.dwFreeHw3DAllBuffers != 0) {
				Caps->Hardware3DChannels = dev->_caps.dwFreeHw3DAllBuffers;
				Caps->Flags |= SQUALL_DEVICE_CAPS_HARDWARE_3D;
			}
			// �������� ������� ��������� EAX 1.0
			if (dev->_eax[1] != 0)
				Caps->Flags |= SQUALL_DEVICE_CAPS_EAX10;

			// �������� ������� ��������� EAX 2.0
			if (dev->_eax[2] != 0)
				Caps->Flags |= SQUALL_DEVICE_CAPS_EAX20;

			// �������� ������� ��������� EAX 3.0
			if (dev->_eax[3] != 0)
				Caps->Flags |= SQUALL_DEVICE_CAPS_EAX30;

			// �������� ������� ��������� ZOOMFX
			if (dev->_zoomfx != 0)
				Caps->Flags |= SQUALL_DEVICE_CAPS_ZOOMFX;
		} else
			result = SQUALL_ERROR_UNKNOWN;
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("error = %s", ErrorTable[-result]);
	else {
		api_Log("\t\t[out]Caps->Flags              = %d", Caps->Flags);
		api_Log("\t\t[out]Caps->HardwareChannels   = %d",
			Caps->HardwareChannels);
		api_Log("\t\t[out]Caps->Hardware3DChannels = %d",
			Caps->Hardware3DChannels);
	}
#endif

	return result;
}
//-----------------------------------------------------------------------------
// ��������� ������������ ������ EAX ����������
// �� �����    :  *
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//  			  � ������ ��������� ������ ��������� �������� �����������
//  			  ��������� ������ EAX
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::GetEAXVersion(void)
#else
DLL_API int SQUALL_GetEAXVersion(void)
#endif
{
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_GetEAXVersion()");
#endif

	// ��������� ���������
	if (IsTrue(result))
		result = context->_useEax;

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else
		api_Log("\t\tresult = %d", result);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}
//-----------------------------------------------------------------------------
// ��������� ���������� � �������
// �� �����    :  Info  -  ��������� �� ��������� � ������� ����� ���������
//  					   ���������� � ��������� �������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::GetChannelsInfo(squall_channels_t* Info)
#else
DLL_API int SQUALL_GetChannelsInfo(squall_channels_t* Info)
#endif
{
	// ����������
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_GetChannelsInfo(0x%X)", Info);
#endif

	// �������� ���������
	if (IsTrue(result))
		if (IsBadWritePtr(Info, sizeof(squall_channels_t)))
			result = SQUALL_ERROR_INVALID_PARAM;
		else
			memset(Info, 0, sizeof(squall_channels_t));

		// ���� ����������
	if (IsTrue(result)) {
		for (int i = 0; i < context->_channels; i++) {
			if (context->_channelsArray[i].Status.STAGE != EMPTY) {
				// ����� ���������� ?
				if (context->_channelsArray[i].Status.SOUND_TYPE ==
					TYPE_AMBIENT) {
					if (context->_channelsArray[i].Status.STAGE == PLAY)
						Info->Play++;    // ���������� ��������������� ���������� �������
					if (context->_channelsArray[i].Status.STAGE == PAUSE)
						Info->Pause++;  	// ���������� ������� � ����� ���������� �������
					if (context->_channelsArray[i].Status.STAGE == PREPARE)
						Info->Prepare++;	// ���������� �������������� ���������� �������
				}

				// ����� ����������� ?
				if (context->_channelsArray[i].Status.SOUND_TYPE ==
					TYPE_POSITIONED) {
					if (context->_channelsArray[i].Status.STAGE == PLAY)
						Info->Play3D++;    // ���������� ��������������� ����������� �������
					if (context->_channelsArray[i].Status.STAGE == PAUSE)
						Info->Pause3D++;	  // ���������� ������� � ����� ����������� �������
					if (context->_channelsArray[i].Status.STAGE == PREPARE)
						Info->Prepare3D++;    // ���������� �������������� ����������� �������
				}
			}
		}
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else {
		api_Log("\t\t[out]Info->Play        = %d", Info->Play);
		api_Log("\t\t[out]Info->Pause       = %d", Info->Pause);
		api_Log("\t\t[out]Info->Prepare     = %d", Info->Prepare);
		api_Log("\t\t[out]Info->Play3D      = %d", Info->Play3D);
		api_Log("\t\t[out]Info->Pause3D     = %d", Info->Pause3D);
		api_Log("\t\t[out]Info->Prepare3D   = %d", Info->Prepare3D);
	}
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//  				  ������ ��� ������ �� ����������
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// ��������� ����� ���������� ���������
// �� �����    :  Position -  ��������� �� ��������� � ������ ������������
//  						  ������� ���������. � ������ ���� ������� ���������
//  						  �������� �� �����, �� ������ �������� ������
//  						  ��������� 0 
//  			  Front    -  ��������� �� ��������� � ����� �������� 
//  						  ������������ ����������� ���������. � ������ ����
//  						  ������ ������������ ����������� ��������� ��������
//  						  �� �����, �� ������ �������� ������ ��������� 0
//  			  Top      -  ��������� �� ��������� � ����� ��������
//  						  ������������� ����������� ���������. � ������ ����
//  						  ������ ������������� ����������� �������� �� �����,
//  						  �� ������ �������� ������ ��������� 0
//  			  Velocity -  ��������� �� ��������� � ����� ��������
//  						  �������� ����������� ���������. � ������ ����
//  						  �������� ����������� ��������� �������� �� �����,
//  						  �� ������ �������� ������ ��������� 0.
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Listener_SetParameters(float* Position, float* Front, float* Top,
	float* Velocity)
#else
DLL_API int SQUALL_Listener_SetParameters(float* Position, float* Front,
	float* Top, float* Velocity)
#endif
{
	int change;
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Listener_SetParameters(0x%X, 0x%X, 0x%X, 0x%X)",
		Position,
		Front,
		Top,
		Velocity);
#endif

	// �������� ����������
	if (IsBadReadPtr(Position, sizeof(float) * 3))
		Position = 0;
	if (IsBadReadPtr(Front, sizeof(float) * 3))
		Front = 0;
	if (IsBadReadPtr(Top, sizeof(float) * 3))
		Top = 0;
	if (IsBadReadPtr(Velocity, sizeof(float) * 3))
		Velocity = 0;

	// ���������� ����������
#if SQUALL_DEBUG
	if (Position) {
		api_Log("\t\t[in]Position->x = %f", Position[0]);
		api_Log("\t\t[in]Position->y = %f", Position[1]);
		api_Log("\t\t[in]Position->z = %f", Position[2]);
	}
	if (Front) {
		api_Log("\t\t[in]Front->x    = %f", Front[0]);
		api_Log("\t\t[in]Front->y    = %f", Front[1]);
		api_Log("\t\t[in]Front->z    = %f", Front[2]);
	}
	if (Top) {
		api_Log("\t\t[in]Top->x      = %f", Top[0]);
		api_Log("\t\t[in]Top->y      = %f", Top[1]);
		api_Log("\t\t[in]Top->z      = %f", Top[2]);
	}
	if (Velocity) {
		api_Log("\t\t[in]Velocity->x = %f", Velocity[0]);
		api_Log("\t\t[in]Velocity->y = %f", Velocity[1]);
		api_Log("\t\t[in]Velocity->z = %f", Velocity[2]);
	}
#endif

	// �������� ������� ���������
	if (IsTrue(result))
		if (!context->_listener)
			result = SQUALL_ERROR_UNKNOWN;

	// ��������� ����������
	if (IsTrue(result)) {
		change = false;
		// �������� ������ ?
		if (Position) {
			// �������� ���������
			if ((Position[0] != context->_listenerParameters.vPosition.x) ||
				(Position[1] != context->_listenerParameters.vPosition.y) ||
				(Position[2] != context->_listenerParameters.vPosition.z)) {
				context->_listenerParameters.vPosition.x = Position[0];
				context->_listenerParameters.vPosition.y = Position[1];
				context->_listenerParameters.vPosition.z = Position[2];
				change = true; // ��������� ����������
			}
		}

		// �������� ������ ?
		if (Velocity) {
			// �������� ���������
			if ((Velocity[0] != context->_listenerParameters.vVelocity.x) ||
				(Velocity[1] != context->_listenerParameters.vVelocity.y) ||
				(Velocity[2] != context->_listenerParameters.vVelocity.z)) {
				context->_listenerParameters.vVelocity.x = Velocity[0];
				context->_listenerParameters.vVelocity.y = Velocity[1];
				context->_listenerParameters.vVelocity.z = Velocity[2];
				change = true; // ��������� ����������
			}
		}

		// �������� ������ ?
		if (Front) {
			// �������� ���������
			if ((Front[0] != context->_listenerParameters.vOrientFront.x) ||
				(Front[1] != context->_listenerParameters.vOrientFront.y) ||
				(Front[2] != context->_listenerParameters.vOrientFront.z)) {
				context->_listenerParameters.vOrientFront.x = Front[0];
				context->_listenerParameters.vOrientFront.y = Front[1];
				context->_listenerParameters.vOrientFront.z = Front[2];
				change = true; // ��������� ����������
			}
		}

		// �������� ������ ?
		if (Top) {
			// �������� ���������
			if ((Top[0] != context->_listenerParameters.vOrientTop.x) ||
				(Top[1] != context->_listenerParameters.vOrientTop.y) ||
				(Top[2] != context->_listenerParameters.vOrientTop.z)) {
				context->_listenerParameters.vOrientTop.x = Top[0];
				context->_listenerParameters.vOrientTop.y = Top[1];
				context->_listenerParameters.vOrientTop.z = Top[2];
				change = true; // ��������� ����������
			}
		}

		// ��������� ����� ����������
		if (change)
			if (!ds_SetAllListenerParameters(context->_listener,
				 	& context->_listenerParameters,
				 	context->_deferred))
				result = SQUALL_ERROR_SET_LISTENER_PARAM;
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ������� ���������� ���������
// �� �����    :  Position -  ��������� �� ��������� � ������� ����� 
//  						  ��������� ������� ���������� ���������. � ������
//  						  ���� �������� ��������� ��������� �� ���������
//  						  ����������, �� ������ �������� ������ ��������� 0.
//  			  Front    -  ��������� �� ��������� � ������� �����
//  						  ��������� ������� ������ ������������ 
//  						  ����������� ���������. � ������ ���� ������
//  						  ������������ ����������� ��������� �� ���������
//  						  ����������, �� ������ �������� ������ ��������� 0.
//  			  Top      -  ��������� �� ��������� � ������� �����
//  						  ��������� ������� ������ ������������� 
//  						  ����������� ���������. � ������ ���� ������
//  						  ������������� ����������� ��������� �� ���������
//  						  ����������, �� ������ �������� ������ ��������� 0.
//  			  Velocity -  ��������� �� ��������� � ������� �����
//  						  ��������� ������� ������ �������� �����������
//  						  ���������. � ������ ���� �������� �����������
//  						  ��������� �� ��������� ����������, �� ������
//  						  �������� ������ ��������� 0.
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Listener_GetParameters(float* Position, float* Front, float* Top,
	float* Velocity)
#else
DLL_API int SQUALL_Listener_GetParameters(float* Position, float* Front,
	float* Top, float* Velocity)
#endif
{
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Listener_GetParameters(0x%X, 0x%X, 0x%X, 0x%X)",
		Position,
		Front,
		Top,
		Velocity);
#endif

	// �������� ����������
	if (IsBadWritePtr(Position, sizeof(float) * 3))
		Position = 0;
	if (IsBadWritePtr(Front, sizeof(float) * 3))
		Front = 0;
	if (IsBadWritePtr(Top, sizeof(float) * 3))
		Top = 0;
	if (IsBadWritePtr(Velocity, sizeof(float) * 3))
		Velocity = 0;

	// �������� ������� ���������
	if (IsTrue(result))
		if (!context->_listener)
			result = SQUALL_ERROR_UNKNOWN;

	// ������ �� ������
	if (IsTrue(result)) {
		// �������� ������ ?
		if (Position) {
			Position[0] = context->_listenerParameters.vPosition.x;
			Position[1] = context->_listenerParameters.vPosition.y;
			Position[2] = context->_listenerParameters.vPosition.z;
		}

		// �������� ������ ?
		if (Front) {
			Front[0] = context->_listenerParameters.vOrientFront.x;
			Front[1] = context->_listenerParameters.vOrientFront.y;
			Front[2] = context->_listenerParameters.vOrientFront.z;
		}

		// �������� ������ ?
		if (Top) {
			Top[0] = context->_listenerParameters.vOrientTop.x;
			Top[1] = context->_listenerParameters.vOrientTop.y;
			Top[2] = context->_listenerParameters.vOrientTop.z;
		}

		// �������� ������ ?
		if (Velocity) {
			Velocity[0] = context->_listenerParameters.vVelocity.x;
			Velocity[1] = context->_listenerParameters.vVelocity.y;
			Velocity[2] = context->_listenerParameters.vVelocity.z;
		}
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else {
		if (Position) {
			api_Log("\t\t[out]Position->x = %f", Position[0]);
			api_Log("\t\t[out]Position->y = %f", Position[1]);
			api_Log("\t\t[out]Position->z = %f", Position[2]);
		}
		if (Front) {
			api_Log("\t\t[out]Front->x    = %f", Front[0]);
			api_Log("\t\t[out]Front->y    = %f", Front[1]);
			api_Log("\t\t[out]Front->z    = %f", Front[2]);
		}
		if (Top) {
			api_Log("\t\t[out]Top->x      = %f", Top[0]);
			api_Log("\t\t[out]Top->y      = %f", Top[1]);
			api_Log("\t\t[out]Top->z      = %f", Top[2]);
		}
		if (Velocity) {
			api_Log("\t\t[out]Velocity->x = %f", Velocity[0]);
			api_Log("\t\t[out]Velocity->y = %f", Velocity[1]);
			api_Log("\t\t[out]Velocity->z = %f", Velocity[2]);
		}
	}
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ����� �������� ����������� ���������
// �� �����    :  Velocity -  ��������� �� ��������� � ����� �������� 
//  						  �������� ����������� ���������.
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Listener_SetVelocity(float* Velocity)
#else
DLL_API int SQUALL_Listener_SetVelocity(float* Velocity)
#endif
{
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Listener_SetVelocity(0x%X)", Velocity);
#endif

	// �������� ����������
	if (IsBadReadPtr(Velocity, sizeof(float) * 3)) {
		Velocity = 0;
		result = SQUALL_ERROR_INVALID_PARAM;
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (Velocity) {
		api_Log("\t\t[in]Velocity->x = %f", Velocity[0]);
		api_Log("\t\t[in]Velocity->y = %f", Velocity[1]);
		api_Log("\t\t[in]Velocity->z = %f", Velocity[2]);
	}
#endif

	// �������� ������� ���������
	if (IsTrue(result))
		if (!context->_listener)
			result = SQUALL_ERROR_UNKNOWN;

	// ��������� ����������
	if (IsTrue(result)) {
		// �������� ���������
		if ((Velocity[0] != context->_listenerParameters.vVelocity.x) ||
			(Velocity[1] != context->_listenerParameters.vVelocity.y) ||
			(Velocity[2] != context->_listenerParameters.vVelocity.z)) {
			// ������� ����� ��������� �������� ���������
			context->_listenerParameters.vVelocity.x = Velocity[0];
			context->_listenerParameters.vVelocity.y = Velocity[1];
			context->_listenerParameters.vVelocity.z = Velocity[2];
			// ��������� ����� ���������� �������� ���������
			if (context->_listener->SetVelocity(context->_listenerParameters.vVelocity.x,
										context->_listenerParameters.vVelocity.y,
										context->_listenerParameters.vVelocity.z,
										context->_deferred) !=
				DS_OK)
				result = SQUALL_ERROR_SET_LISTENER_PARAM;
		}
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ������� �������� ����������� ���������
// �� �����    :  Velocity - ��������� �� ��������� � ������� �����
//  						 ��������� ������� ������ �������� �����������
//  						 ���������.
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Listener_GetVelocity(float* Velocity)
#else
DLL_API int SQUALL_Listener_GetVelocity(float* Velocity)
#endif
{
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Listener_GetVelocity(0x%X)", Velocity);
#endif

	// �������� ����������
	if (IsBadWritePtr(Velocity, sizeof(float) * 3)) {
		Velocity = 0;
		result = SQUALL_ERROR_INVALID_PARAM;
	}

	// �������� ������� ���������
	if (IsTrue(result))
		if (!context->_listener)
			result = SQUALL_ERROR_UNKNOWN;

	// ��������� ����������
	if (IsTrue(result)) {
		Velocity[0] = context->_listenerParameters.vVelocity.x;
		Velocity[1] = context->_listenerParameters.vVelocity.y;
		Velocity[2] = context->_listenerParameters.vVelocity.z;
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else {
		api_Log("\t\t[out]Velocity->x = %f", Velocity[0]);
		api_Log("\t\t[out]Velocity->y = %f", Velocity[1]);
		api_Log("\t\t[out]Velocity->z = %f", Velocity[2]);
	}
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ����� ������� ��������� � ������������
// �� �����    :  Position -  ��������� �� ��������� � ����� ��������
//  						  �������� ����������� ���������.
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Listener_SetPosition(float* Position)
#else
DLL_API int SQUALL_Listener_SetPosition(float* Position)
#endif
{
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Listener_SetPosition(0x%X)", Position);
#endif

	// �������� ����������
	if (IsBadReadPtr(Position, sizeof(float) * 3)) {
		Position = 0;
		result = SQUALL_ERROR_INVALID_PARAM;
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (Position) {
		api_Log("\t\t[in]Position->x = %f", Position[0]);
		api_Log("\t\t[in]Position->y = %f", Position[1]);
		api_Log("\t\t[in]Position->z = %f", Position[2]);
	}
#endif

	// �������� ������� ���������
	if (IsTrue(result))
		if (!context->_listener)
			result = SQUALL_ERROR_UNKNOWN;

	// ��������� ����������
	if (IsTrue(result)) {
		// �������� ���������
		if ((Position[0] != context->_listenerParameters.vPosition.x) ||
			(Position[1] != context->_listenerParameters.vPosition.y) ||
			(Position[2] != context->_listenerParameters.vPosition.z)) {
			// �������� ����� ���������� ���������
			context->_listenerParameters.vPosition.x = Position[0];
			context->_listenerParameters.vPosition.y = Position[1];
			context->_listenerParameters.vPosition.z = Position[2];
			// ��������� ����� ��������� ���������
			if (context->_listener->SetPosition(Position[0],
										Position[1],
										Position[2],
										DS3D_IMMEDIATE) != DS_OK)
				result = SQUALL_ERROR_SET_LISTENER_PARAM;
		}
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ������� ������� ��������� � ������������
// �� �����    :  Position -  ��������� �� ��������� � ������� �����
//  						  ��������� ������� ������ �������� �����������
//  						  ���������.
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Listener_GetPosition(float* Position)
#else
DLL_API int SQUALL_Listener_GetPosition(float* Position)
#endif
{
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Listener_GetPosition(0x%X)", Position);
#endif

	// �������� ����������
	if (IsBadWritePtr(Position, sizeof(float) * 3)) {
		Position = 0;
		result = SQUALL_ERROR_INVALID_PARAM;
	}

	// �������� ������� ���������
	if (IsTrue(result))
		if (!context->_listener)
			result = SQUALL_ERROR_UNKNOWN;

	// ��������� ����������
	if (IsTrue(result)) {
		Position[0] = context->_listenerParameters.vPosition.x;
		Position[1] = context->_listenerParameters.vPosition.y;
		Position[2] = context->_listenerParameters.vPosition.z;
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else {
		// ������� ���������� � ������� ���������
		api_Log("\t\t[out]Position->x = %f", Position[0]);
		api_Log("\t\t[out]Position->y = %f", Position[1]);
		api_Log("\t\t[out]Position->z = %f", Position[2]);
	}
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}
//-----------------------------------------------------------------------------
// ��������� ������ ������������ �������������� ���������
// �� �����    :  DistanceFactor -  ����� ����������� �������������� ���������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Listener_SetDistanceFactor(float DistanceFactor)
#else
DLL_API int SQUALL_Listener_SetDistanceFactor(float DistanceFactor)
#endif
{
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Listener_SetDistanceFactor(%f)", DistanceFactor);
#endif

	// �������� ����������
	if ((DistanceFactor <= 0.0f) || (DistanceFactor > 10.0f))
		result = SQUALL_ERROR_INVALID_PARAM;

	// �������� ������� ���������
	if (IsTrue(result))
		if (!context->_listener)
			result = SQUALL_ERROR_UNKNOWN;

	// ��������� ����������
	if (IsTrue(result)) {
		// �������� ���������
		if (context->_listenerParameters.flDistanceFactor != DistanceFactor) {
			// ��������� ������ �����������
			context->_listenerParameters.flDistanceFactor = DistanceFactor;
			if (context->_listener->SetDistanceFactor(DistanceFactor,
										context->_deferred) != DS_OK)
				result = SQUALL_ERROR_SET_LISTENER_PARAM;
		}
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}
//-----------------------------------------------------------------------------
// ��������� �������� ������������ �������������� ���������
// �� �����    :  DistanceFactor -  ��������� �� ���������� � ������� �����
//  								��������� ������� ����������� 
//  								�������������� ���������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Listener_GetDistanceFactor(float* DistanceFactor)
#else
DLL_API int SQUALL_Listener_GetDistanceFactor(float* DistanceFactor)
#endif
{
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Listener_GetDistanceFactor(0x%X)", DistanceFactor);
#endif

	// �������� ����������
	if (IsTrue(result))
		if (IsBadWritePtr(DistanceFactor, sizeof(float)))
			result = SQUALL_ERROR_INVALID_PARAM;

	// �������� ������� ���������
	if (IsTrue(result))
		if (!context->_listener)
			result = SQUALL_ERROR_UNKNOWN;

	// ��������� ����������
	if (IsTrue(result))
		*DistanceFactor = context->_listenerParameters.flDistanceFactor;

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else
		api_Log("\t\t[out]*DistanceFactor = %f", * DistanceFactor);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}
//-----------------------------------------------------------------------------
// ��������� ������ ������������ ��������� ����� � ����������� �� ���������
// �� �����    :  RolloffFactor  -  ����� ����������� �������������� ���������
//  								�����,  �������� ��������� ������ ����
//  								� �������� �� 0.1f �� 10.0f
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Listener_SetRolloffFactor(float RolloffFactor)
#else
DLL_API int SQUALL_Listener_SetRolloffFactor(float RolloffFactor)
#endif
{
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Listener_SetRolloffFactor(%f)", RolloffFactor);
#endif

	// �������� ����������
	if ((RolloffFactor <= 0.0f) || (RolloffFactor > 10.0f))
		result = SQUALL_ERROR_INVALID_PARAM;

	// �������� ������� ���������
	if (IsTrue(result))
		if (!context->_listener)
			result = SQUALL_ERROR_UNKNOWN;

	if (IsTrue(result)) {
		// �������� ���������
		if (context->_listenerParameters.flRolloffFactor != RolloffFactor) {
			// ��������� ������ �����������
			context->_listenerParameters.flRolloffFactor = RolloffFactor;
			if (context->_listener->SetRolloffFactor(RolloffFactor,
										context->_deferred) != DS_OK)
				result = SQUALL_ERROR_SET_LISTENER_PARAM;
		}
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}
//-----------------------------------------------------------------------------
// ��������� �������� ������������ ��������� ����� � ����������� �� ���������
// �� �����    :  RolloffFactor  -  ��������� �� ���������� � ������� �����
//  								��������� ������� ����������� ��������������
//  								��������� �����
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Listener_GetRolloffFactor(float* RolloffFactor)
#else
DLL_API int SQUALL_Listener_GetRolloffFactor(float* RolloffFactor)
#endif
{
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Listener_GetRolloffFactor(%f)", RolloffFactor);
#endif

	// �������� ����������
	if (IsTrue(result))
		if (IsBadWritePtr(RolloffFactor, sizeof(float)))
			result = SQUALL_ERROR_INVALID_PARAM;

	// �������� ������� ���������
	if (IsTrue(result))
		if (!context->_listener)
			result = SQUALL_ERROR_UNKNOWN;

	// ��������� ����������
	if (IsTrue(result))
		*RolloffFactor = context->_listenerParameters.flRolloffFactor;

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else
		api_Log("\t\t[out]*RolloffFactor = %f", * RolloffFactor);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ������ ������������ ������� ��������
// �� �����    :  DopplerFactor  -  ����� ����������� ������� ��������, ��������
//  								��������� ������ ���� � �������� �� 0.1f
//  								�� 10.0f
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Listener_SetDopplerFactor(float DopplerFactor)
#else
DLL_API int SQUALL_Listener_SetDopplerFactor(float DopplerFactor)
#endif
{
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Listener_SetDopplerFactor(%f)", DopplerFactor);
#endif

	// �������� ����������
	if ((DopplerFactor <= 0.0f) || (DopplerFactor > 10.0f))
		result = SQUALL_ERROR_INVALID_PARAM;

	// �������� ������� ���������
	if (IsTrue(result))
		if (!context->_listener)
			result = SQUALL_ERROR_UNKNOWN;

	if (IsTrue(result)) {
		// �������� ���������
		if (context->_listenerParameters.flDopplerFactor != DopplerFactor) {
			// ��������� ������ �����������
			context->_listenerParameters.flDopplerFactor = DopplerFactor;
			if (context->_listener->SetDopplerFactor(DopplerFactor,
										context->_deferred) != DS_OK)
				result = SQUALL_ERROR_SET_LISTENER_PARAM;
		}
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� �������� ������������ ������� ��������
// �� �����    :  DopplerFactor  -  ��������� �� ���������� � ������� �����
//  								��������� ������� ����������� �������
//  								��������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Listener_GetDopplerFactor(float* DopplerFactor)
#else
DLL_API int SQUALL_Listener_GetDopplerFactor(float* DopplerFactor)
#endif
{
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Listener_GetDopplerFactor(0x%X)", DopplerFactor);
#endif

	// �������� ����������
	if (IsTrue(result))
		if (IsBadWritePtr(DopplerFactor, sizeof(float)))
			result = SQUALL_ERROR_INVALID_PARAM;

	// �������� ������� ���������
	if (IsTrue(result))
		if (!context->_listener)
			result = SQUALL_ERROR_UNKNOWN;

	// ��������� ����������
	if (IsTrue(result))
		*DopplerFactor = context->_listenerParameters.flDopplerFactor;

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else
		api_Log("\t\t[out]*DopplerFactor = %f", * DopplerFactor);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ���������� ���������� ��������
// �� �����    :  *
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
// ����������  :  ������ ����� ����� ����� ��������� ������ � ��� ������ �����
//  			  ��������� �������� �� �������������� ���������� ����������
//  			  ��������. �� ���� ��� ������������� ��������� ���������
//  			  ��������� � ����� SQUALL_LISTENER_MODE_DEFERRED
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Listener_Update(void)
#else
DLL_API int SQUALL_Listener_Update(void)
#endif
{
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Listener_Update()");
#endif

	// �������� ������� ���������
	if (IsTrue(result))
		if (!context->_listener)
			result = SQUALL_ERROR_UNKNOWN;
		else if (context->_listener->CommitDeferredSettings() != DS_OK)
			result = SQUALL_ERROR_UNKNOWN;

		// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ����������������� �������� ���������
// �� �����    :  Preset   -  ����� ������������������ ��������
//  						  �������� ����� ��������� ��������� ��������:
//  						  SQUALL_EAX_OFF
//  						  SQUALL_EAX_GENERIC
//  						  SQUALL_EAX_PADDEDCELL
//  						  SQUALL_EAX_ROOM
//  						  SQUALL_EAX_BATHROOM
//  						  SQUALL_EAX_LIVINGROOM
//  						  SQUALL_EAX_STONEROOM
//  						  SQUALL_EAX_AUDITORIUM
//  						  SQUALL_EAX_CONCERTHALL
//  						  SQUALL_EAX_CAVE
//  						  SQUALL_EAX_ARENA
//  						  SQUALL_EAX_HANGAR
//  						  SQUALL_EAX_CARPETEDHALLWAY
//  						  SQUALL_EAX_HALLWAY
//  						  SQUALL_EAX_STONECORRIDOR
//  						  SQUALL_EAX_ALLEY
//  						  SQUALL_EAX_FOREST
//  						  SQUALL_EAX_CITY
//  						  SQUALL_EAX_MOUNTAINS
//  						  SQUALL_EAX_QUARRY
//  						  SQUALL_EAX_PLAIN
//  						  SQUALL_EAX_PARKINGLOT
//  						  SQUALL_EAX_SEWERPIPE
//  						  SQUALL_EAX_UNDERWATER
//  						  SQUALL_EAX_DRUGGED
//  						  SQUALL_EAX_DIZZY
//  						  SQUALL_EAX_PSYCHOTIC
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Listener_EAX_SetProperties(int Version,
	squall_eax_listener_t* Properties)
#else
DLL_API int SQUALL_Listener_EAX_SetProperties(int Version,
	squall_eax_listener_t* Properties)
#endif
{
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Listener_EAX_SetProperties(%d, 0x%X)",
		Version,
		Properties);
#endif

	// �������� ������� EAX
	if (IsTrue(result))
		if (!context->_useEax)
			result = SQUALL_ERROR_NO_EAX;

	// �������� ����������
	if (IsTrue(result))
		if ((Version <= 0) ||
			(Version > EAX_NUM) ||
			IsBadReadPtr(Properties,
				sizeof(squall_eax_listener_t))) {
			Properties = 0;
			result = SQUALL_ERROR_INVALID_PARAM;
		}

	// ���������� ����������
#if SQUALL_DEBUG
	if (Properties) {
		// � ����������� �� ������ ��������� ���������
		switch (Version) {
			// EAX 1.0
		case 1:
			api_Log("\t\t[in]Properties->Environment       = %d",
				Properties->eax1.Environment);
			api_Log("\t\t[in]Properties->Volume            = %f",
				Properties->eax1.Volume);
			api_Log("\t\t[in]Properties->DecayTime_sec     = %f",
				Properties->eax1.DecayTime_sec);
			api_Log("\t\t[in]Properties->Damping           = %f",
				Properties->eax1.Damping);
			break;

			// EAX 2.0
		case 2:
			api_Log("\t\t[in]Properties->Room              = %d",
				Properties->eax2.Room);
			api_Log("\t\t[in]Properties->RoomHF            = %d",
				Properties->eax2.RoomHF);
			api_Log("\t\t[in]Properties->RoomRolloffFactor = %f",
				Properties->eax2.RoomRolloffFactor);
			api_Log("\t\t[in]Properties->DecayTime         = %f",
				Properties->eax2.DecayTime);
			api_Log("\t\t[in]Properties->DecayHFRatio      = %f",
				Properties->eax2.DecayHFRatio);
			api_Log("\t\t[in]Properties->Reflections       = %d",
				Properties->eax2.Reflections);
			api_Log("\t\t[in]Properties->ReflectionsDelay  = %f",
				Properties->eax2.ReflectionsDelay);
			api_Log("\t\t[in]Properties->Reverb            = %d",
				Properties->eax2.Reverb);
			api_Log("\t\t[in]Properties->ReverbDelay       = %f",
				Properties->eax2.ReverbDelay);
			api_Log("\t\t[in]Properties->Environment       = %d",
				Properties->eax2.Environment);
			api_Log("\t\t[in]Properties->EnvSize           = %f",
				Properties->eax2.EnvironmentSize);
			api_Log("\t\t[in]Properties->EnvDiffusion      = %f",
				Properties->eax2.EnvironmentDiffusion);
			api_Log("\t\t[in]Properties->AirAbsorptionHF   = %f",
				Properties->eax2.AirAbsorptionHF);
			api_Log("\t\t[in]Properties->Flags             = %d",
				Properties->eax2.Flags);
			break;

			// EAX 3.0
		case 3:
			api_Log("\t\t[in]Properties->Environment          = %d",
				Properties->eax3.Environment);
			api_Log("\t\t[in]Properties->EnvironmentSize      = %f",
				Properties->eax3.EnvironmentSize);
			api_Log("\t\t[in]Properties->EnvironmentDiffusion = %f",
				Properties->eax3.EnvironmentDiffusion);
			api_Log("\t\t[in]Properties->Room                 = %d",
				Properties->eax3.Room);
			api_Log("\t\t[in]Properties->RoomHF               = %d",
				Properties->eax3.RoomHF);
			api_Log("\t\t[in]Properties->RoomLF               = %d",
				Properties->eax3.RoomLF);
			api_Log("\t\t[in]Properties->DecayTime            = %f",
				Properties->eax3.DecayTime);
			api_Log("\t\t[in]Properties->DecayHFRatio         = %f",
				Properties->eax3.DecayHFRatio);
			api_Log("\t\t[in]Properties->DecayLFRatio         = %f",
				Properties->eax3.DecayLFRatio);
			api_Log("\t\t[in]Properties->Reflections          = %d",
				Properties->eax3.Reflections);
			api_Log("\t\t[in]Properties->ReflectionsDelay     = %f",
				Properties->eax3.ReflectionsDelay);
			api_Log("\t\t[in]Properties->ReflectionsPan[x]    = %f",
				Properties->eax3.ReflectionsPan[0]);
			api_Log("\t\t[in]Properties->ReflectionsPan[y]    = %f",
				Properties->eax3.ReflectionsPan[1]);
			api_Log("\t\t[in]Properties->ReflectionsPan[z]    = %f",
				Properties->eax3.ReflectionsPan[2]);
			api_Log("\t\t[in]Properties->Reverb               = %d",
				Properties->eax3.Reverb);
			api_Log("\t\t[in]Properties->ReverbDelay          = %f",
				Properties->eax3.ReverbDelay);
			api_Log("\t\t[in]Properties->ReverbPan[x]         = %f",
				Properties->eax3.ReverbPan[0]);
			api_Log("\t\t[in]Properties->ReverbPan[y]         = %f",
				Properties->eax3.ReverbPan[1]);
			api_Log("\t\t[in]Properties->ReverbPan[z]         = %f",
				Properties->eax3.ReverbPan[2]);
			api_Log("\t\t[in]Properties->EchoTime             = %f",
				Properties->eax3.EchoTime);
			api_Log("\t\t[in]Properties->EchoDepth            = %f",
				Properties->eax3.EchoDepth);
			api_Log("\t\t[in]Properties->ModulationTime       = %f",
				Properties->eax3.ModulationTime);
			api_Log("\t\t[in]Properties->ModulationDepth      = %f",
				Properties->eax3.ModulationDepth);
			api_Log("\t\t[in]Properties->AirAbsorptionHF      = %f",
				Properties->eax3.AirAbsorptionHF);
			api_Log("\t\t[in]Properties->HFReference          = %f",
				Properties->eax3.HFReference);
			api_Log("\t\t[in]Properties->LFReference          = %f",
				Properties->eax3.LFReference);
			api_Log("\t\t[in]Properties->RoomRolloffFactor    = %f",
				Properties->eax3.RoomRolloffFactor);
			api_Log("\t\t[in]Properties->Flags                = %d",
				Properties->eax3.Flags);
			break;
		}
	}
#endif

	// �������� ����������� ����������
	if (IsTrue(result)) {
		// ��������� ���������
		memcpy(&context->_eaxLP, Properties, sizeof(squall_eax_listener_t));
		if (context->_eaxSupport[Version])
			result = SQUALL_ERROR_EAX_VERSION;
	}

	// ��������� ����������
	if (IsTrue(result))
		if (!eax_Set(context->_eaxListener,
			 	EAX_LISTENER,
			 	Version,
			 	& context->_eaxLP))
			result = SQUALL_ERROR_SET_EAX_PARAM;

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ����� EAX ���������� ���������
// �� �����    :  Version     -  ����� ������ EAX ����������
//  			  Properties  -  ��������� �� ��������� � ������ EAX �����������
//  							 ���������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Listener_EAX_GetProperties(int Version,
	squall_eax_listener_t* Properties)
#else
DLL_API int SQUALL_Listener_EAX_GetProperties(int Version,
	squall_eax_listener_t* Properties)
#endif
{
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Listener_EAX_GetProperties(%d, 0x%X)",
		Version,
		Properties);
#endif

	// �������� ������� EAX
	if (IsTrue(result))
		if (!context->_useEax)
			result = SQUALL_ERROR_NO_EAX;

	// �������� ����������
	if (IsTrue(result))
		if ((Version <= 0) ||
			(Version > EAX_NUM) ||
			IsBadWritePtr(Properties,
				sizeof(squall_eax_listener_t))) {
			Properties = 0;
			result = SQUALL_ERROR_INVALID_PARAM;
		}


	// �������� ������
	if (IsTrue(result))
		if (context->_eaxSupport[Version])
			result = SQUALL_ERROR_EAX_VERSION;

	// ��������� ����������
	if (IsTrue(result))
		if (eax_Get(context->_eaxListener,
				EAX_LISTENER,
				Version,
				& context->_eaxLP))
			memcpy(Properties,
				& context->_eaxLP,
				sizeof(squall_eax_listener_t));
		else
			result = SQUALL_ERROR_GET_EAX_PARAM;

		// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else {
		if (Properties) {
			switch (Version) {
				// EAX 1.0
			case 1:
				api_Log("\t\t[out]Properties->Environment       = %d",
					Properties->eax1.Environment);
				api_Log("\t\t[out]Properties->Volume            = %f",
					Properties->eax1.Volume);
				api_Log("\t\t[out]Properties->DecayTime_sec     = %f",
					Properties->eax1.DecayTime_sec);
				api_Log("\t\t[out]Properties->Damping           = %f",
					Properties->eax1.Damping);
				break;
				// EAX 2.0
			case 2:
				api_Log("\t\t[out]Properties->Room              = %d",
					Properties->eax2.Room);
				api_Log("\t\t[out]Properties->RoomHF            = %d",
					Properties->eax2.RoomHF);
				api_Log("\t\t[out]Properties->RoomRolloffFactor = %f",
					Properties->eax2.RoomRolloffFactor);
				api_Log("\t\t[out]Properties->DecayTime         = %f",
					Properties->eax2.DecayTime);
				api_Log("\t\t[out]Properties->DecayHFRatio      = %f",
					Properties->eax2.DecayHFRatio);
				api_Log("\t\t[out]Properties->Reflections       = %d",
					Properties->eax2.Reflections);
				api_Log("\t\t[out]Properties->ReflectionsDelay  = %f",
					Properties->eax2.ReflectionsDelay);
				api_Log("\t\t[out]Properties->Reverb            = %d",
					Properties->eax2.Reverb);
				api_Log("\t\t[out]Properties->ReverbDelay       = %f",
					Properties->eax2.ReverbDelay);
				api_Log("\t\t[out]Properties->Environment       = %d",
					Properties->eax2.Environment);
				api_Log("\t\t[out]Properties->EnvSize           = %f",
					Properties->eax2.EnvironmentSize);
				api_Log("\t\t[out]Properties->EnvDiffusion      = %f",
					Properties->eax2.EnvironmentDiffusion);
				api_Log("\t\t[out]Properties->AirAbsorptionHF   = %f",
					Properties->eax2.AirAbsorptionHF);
				api_Log("\t\t[out]Properties->Flags             = %d",
					Properties->eax2.Flags);
				break;
				// EAX 3.0
			case 3:
				api_Log("\t\t[out]Properties->Environment          = %d",
					Properties->eax3.Environment);
				api_Log("\t\t[out]Properties->EnvironmentSize      = %f",
					Properties->eax3.EnvironmentSize);
				api_Log("\t\t[out]Properties->EnvironmentDiffusion = %f",
					Properties->eax3.EnvironmentDiffusion);
				api_Log("\t\t[out]Properties->Room                 = %d",
					Properties->eax3.Room);
				api_Log("\t\t[out]Properties->RoomHF               = %d",
					Properties->eax3.RoomHF);
				api_Log("\t\t[out]Properties->RoomLF               = %d",
					Properties->eax3.RoomLF);
				api_Log("\t\t[out]Properties->DecayTime            = %f",
					Properties->eax3.DecayTime);
				api_Log("\t\t[out]Properties->DecayHFRatio         = %f",
					Properties->eax3.DecayHFRatio);
				api_Log("\t\t[out]Properties->DecayLFRatio         = %f",
					Properties->eax3.DecayLFRatio);
				api_Log("\t\t[out]Properties->Reflections          = %d",
					Properties->eax3.Reflections);
				api_Log("\t\t[out]Properties->ReflectionsDelay     = %f",
					Properties->eax3.ReflectionsDelay);
				api_Log("\t\t[out]Properties->ReflectionsPan[x]    = %f",
					Properties->eax3.ReflectionsPan[0]);
				api_Log("\t\t[out]Properties->ReflectionsPan[y]    = %f",
					Properties->eax3.ReflectionsPan[1]);
				api_Log("\t\t[out]Properties->ReflectionsPan[z]    = %f",
					Properties->eax3.ReflectionsPan[2]);
				api_Log("\t\t[out]Properties->Reverb               = %d",
					Properties->eax3.Reverb);
				api_Log("\t\t[out]Properties->ReverbDelay          = %f",
					Properties->eax3.ReverbDelay);
				api_Log("\t\t[out]Properties->ReverbPan[x]         = %f",
					Properties->eax3.ReverbPan[0]);
				api_Log("\t\t[out]Properties->ReverbPan[y]         = %f",
					Properties->eax3.ReverbPan[1]);
				api_Log("\t\t[out]Properties->ReverbPan[z]         = %f",
					Properties->eax3.ReverbPan[2]);
				api_Log("\t\t[out]Properties->EchoTime             = %f",
					Properties->eax3.EchoTime);
				api_Log("\t\t[out]Properties->EchoDepth            = %f",
					Properties->eax3.EchoDepth);
				api_Log("\t\t[out]Properties->ModulationTime       = %f",
					Properties->eax3.ModulationTime);
				api_Log("\t\t[out]Properties->ModulationDepth      = %f",
					Properties->eax3.ModulationDepth);
				api_Log("\t\t[out]Properties->AirAbsorptionHF      = %f",
					Properties->eax3.AirAbsorptionHF);
				api_Log("\t\t[out]Properties->HFReference          = %f",
					Properties->eax3.HFReference);
				api_Log("\t\t[out]Properties->LFReference          = %f",
					Properties->eax3.LFReference);
				api_Log("\t\t[out]Properties->RoomRolloffFactor    = %f",
					Properties->eax3.RoomRolloffFactor);
				api_Log("\t\t[out]Properties->Flags                = %d",
					Properties->eax3.Flags);
				break;
			}
		}
	}
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}
//-----------------------------------------------------------------------------
// ��������� ������� EAX ���������� ���������
// �� �����    :  Version     -  ����� ������ EAX ����������
//  			  Properties  -  ��������� �� ��������� ���� ���� ���������
//  							 ������� EAX ��������� ���������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Listener_EAX_SetPreset(int Preset)
#else
DLL_API int SQUALL_Listener_EAX_SetPreset(int Preset)
#endif
{
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Listener_EAX_SetPreset(%d)", Preset);
#endif

	// �������� ������� EAX
	if (IsTrue(result))
		if (!context->_useEax)
			result = SQUALL_ERROR_NO_EAX;

	// �������������� ������ ���������
	Preset++;

	// �������� ����������
	if (IsTrue(result))
		if ((Preset < 0) || (Preset > 26))
			result = SQUALL_ERROR_INVALID_PARAM;

	// ��������� ���������
	if (IsTrue(result))
		if (!eax_Preset(context->_eaxListener, context->_useEax, Preset))
			result = SQUALL_ERROR_SET_EAX_PARAM;

	// ��������� ������� ����������
	if (IsTrue(result))
		if (!eax_Get(context->_eaxListener,
			 	EAX_LISTENER,
			 	context->_useEax,
			 	& context->_eaxLP))
			result = SQUALL_ERROR_GET_EAX_PARAM;

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ����������� ���������
// �� �����    :  Worker	  -  ��������� �� ���������� ���������, � ������
//  							 ���� �������� ����� 0, ���������� ����������
//  							 ����� ������.
//  			  Param 	  -  ��������� �� ������ ������������, � ������
//  							 ������ ������������ ���, �� ������ ��������
//  							 ����� ��������� 0
//  			  UpdateTime  -  ���������� ������� ����� ������� �����
//  							 �������� ���������� �������� ������ ������
//  							 � �������� �� 1 �� 5000
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Listener_SetWorker(squall_callback_listener_t Worker, void* Param,
	unsigned int UpdateTime)
#else
DLL_API int SQUALL_Listener_SetWorker(squall_callback_listener_t Worker,
	void* Param, unsigned int UpdateTime)
#endif
{
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Listener_SetWorker(0x%X, 0x%X, %d)",
		Worker,
		Param,
		UpdateTime);
#endif

	if (IsTrue(result)) {
		if (Worker == 0) {
			// ����� �����������
			context->_worker = 0;
			context->_workerUserData = 0;
			context->_workerUpdateTime = 0;
		} else {
			// �������� ����������
			if (IsBadCodePtr((FARPROC) Worker) || (UpdateTime <= 0))
				result = SQUALL_ERROR_INVALID_PARAM;

			if (IsTrue(result)) {
				// ������� ��������� �����������
				context->_worker = Worker;
				context->_workerUserData = Param;
				context->_workerUpdateTime = UpdateTime;
			}
		}
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ��������������� ���������� �����, ����������� ������
// �� ����� :  SampleID 	- ������������� ����������� �����
//  		   Loop 	- ���� ������������ ���������������
//  					  true   - �������������� ���� � ����� ����������
//  					  false  - ������������� ���� ���� ���
//  		   Group	- �������������� ������������ ������ � ������
//  		   Start	- ���� ������� ����� �� ��������� �������� ������
//  					  true   - ����� ������ ������������� ����� ��
//  					  false  - ����� ����� ������ �����������, ��� ����
//  							����� ������ ��������������� �����
//  							������� ����� CHANNEL_Start()
//  		   Priority - ��������� ������������ ��������� ������,
//  					  �������� ������ ������ � �������� �� 0 �� 255
//  		   Volume      - ��������� ������������ ��������� ������,
//  					  �������� ������ ������ � �������� �� 0 �� 100
//  		   Frequency   - ������� ������������ ��������� ������
//  					  �������� ������ ������ � �������� �� 100 �� 100000
//  		   Pan  	   - �������� ������������ ��������� ������
//  					  �������� ������ ������ � �������� �� 0 �� 100
// �� ������   :  ������������� ��������� ������, ���� �������� �������� �����
//  		   0, ������ ��������� ������, ����� ������ ����� ������
//  		   ������ ����� SYSTEM_GetError()
// ����������  :  1. ��������������� ������������� � ��������������� ����� � 
//  		   ������ �����. �� ���� ����� ������������ ������� ������
//  		   ������
//-----------------------------------------------------------------------------
int CreateChannel(context_t* context, int SampleID, int Loop,
	int ChannelGroupID, int Start, int Priority, int Volume, int Frequency,
	int Pan)
{
	// ����������
	int channel = - 1;
	int count = 0;
	CSoundFile* SoundData = 0;
	int result = true;

	// ��������� ��������� �� ������ ������
	SoundData = api_SampleGetFile(SampleID);
	if (!SoundData)
		result = SQUALL_ERROR_SAMPLE_BAD;

	// ����� ���������� ����� ��� ����
	if (IsTrue(result)) {
		channel = context->GetFreeChannel(Priority);
		if (channel < 0)
			result = SQUALL_ERROR_NO_FREE_CHANNEL;
	}

	// �������� ������� ����� � �������� �������� �����
	if (IsTrue(result)) {
		// ���������� �����
		count = context->_channelsArray[channel]._count;
		memset(&context->_channelsArray[channel], 0, sizeof(SSample));
		context->_channelsArray[channel]._count = count;

		// ���������� ������� �������� ���������
		context->_channelsArray[channel].ChannelID = context->GetChannelID(channel);
		context->_channelsArray[channel].Status.SOUND_TYPE = TYPE_AMBIENT;
		context->_channelsArray[channel].GroupID = ChannelGroupID;
		context->_channelsArray[channel].Status.SAMPLE_LOOP = Loop;
		context->_channelsArray[channel].SoundFile = SoundData;
		context->_channelsArray[channel].SampleID = SampleID;
		context->_channelsArray[channel].EndPtr = SoundData->GetSamplesInFile();
		context->_channelsArray[channel].MasterSize = context->_channelsArray[channel].EndPtr;
		context->_channelsArray[channel].SamplesPerSec = SoundData->GetFormat()->nSamplesPerSec;
		context->_channelsArray[channel].Priority = Priority;
		context->_channelsArray[channel].Status.STAGE = PREPARE;

		// �������� �������� �����
		if (!context->_channelsArray[channel].CreateSoundBuffer(context->_directSound,
											  	SoundData->GetFormat(),
											  	SoundData->GetSamplesInFile(),
											  	context->_bufferSize,
											  	context->_useHW2D))
			result = SQUALL_ERROR_CREATE_CHANNEL;
	}

	// ���������� ������� ������ �������� ������
	if (IsTrue(result))
		if (!context->_channelsArray[channel].FillSoundBuffer(0))
			result = SQUALL_ERROR_SET_CHANNEL_PARAM;

	// ��������� ������ ��������� ������
	if (IsTrue(result))
		if (!context->_channelsArray[channel].SetVolume(volume_table[Volume]))
			result = SQUALL_ERROR_SET_CHANNEL_PARAM;

	// ��������� �������
	if (IsTrue(result))
		if (Frequency)
			if (!context->_channelsArray[channel].SetFrequency(Frequency))
				result = SQUALL_ERROR_SET_CHANNEL_PARAM;

	// ��������� ��������
	if (IsTrue(result))
		if (!context->_channelsArray[channel].SetPan(Pan))
			result = SQUALL_ERROR_SET_CHANNEL_PARAM;

	// �������� �� ���������������
	if (IsTrue(result))
		if (Start)
			if (!context->_channelsArray[channel].Play())
				result = SQUALL_ERROR_SET_CHANNEL_PARAM;

	// ���� ���� ������ ������ ��� ��������
	if (IsFalse(result)) {
		if (channel != -1) {
			context->_channelsArray[channel].DeleteSoundBuffer();
			context->_channelsArray[channel].Status.STAGE = EMPTY;
		}
	}

	// ���� ������ �� ���� ������ ������������� ������
	if (IsTrue(result))
		result = context->_channelsArray[channel].ChannelID;

	// ������ ��������� ������
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ��������������� ��������� �����, ����������� ������
// �� ����� :  SampleID 	- ������������� ����������� �����
//  		   Loop 	- ���� ������������ ���������������
//  					  true   - �������������� ���� � ����� ����������
//  					  false  - ������������� ���� ���� ���
//  		   Group	- �������������� ������������ ������ � ������
//  		   Start	- ���� ������� ����� �� ��������� �������� ������
//  					  true   - ����� ������ ������������� ����� ��
//  					  false  - ����� ����� ������ �����������, ��� ����
//  							����� ������ ��������������� �����
//  							������� ����� CHANNEL_Start()
//  		   Position - ��������� �� ��������� ��������� ���������
//  					  ���������
//  		   Velocity - ��������� �� ������ �������� ��������� �����,
//  					  ���� �������� �������� �� �����, �� ������
//  					  �������� ����� ���� ����� 0
//  		   Priority - ��������� ������������ ��������� ������,
//  					  �������� ������ ������ � �������� �� 0 �� 255
//  		   Volume      - ��������� ������������ ��������� ������,
//  					  �������� ������ ������ � �������� �� 0 �� 100
//  		   Frequency   - ������� ������������ ��������� ������
//  					  �������� ������ ������ � �������� �� 100 �� 100000
//  		   MinDist     - ����������� ��������� ����������
//  		   MaxDist     - ������������ ��������� ����������
// �� ������   :  ������������� ��������� ������, ���� �������� �������� �����
//  		   0, ������ ��������� ������, ����� ������ ����� ������
//  		   ������ ����� SYSTEM_GetError()
// ����������  :  1. ��������������� ������������� � ��������������� ����� � 
//  		   ���� �����. �� ���� ����� ������������ ������� ���� ������
//-----------------------------------------------------------------------------
int CreateChannel3D(context_t* context, int SampleID, int Loop,
	int ChannelGroupID, int Start, float* Position, float* Velocity,
	int Priority, int Volume, int Frequency, float MinDist, float MaxDist)
{
	// ����������
	int channel = - 1;
	int count = 0;
	CSoundFile* SoundData = 0;
	int result = true;


	// ���������� ��������� �� ��������� �����
	float dx = context->_listenerParameters.vPosition.x - Position[0];
	float dy = context->_listenerParameters.vPosition.y - Position[1];
	float dz = context->_listenerParameters.vPosition.z - Position[2];

	float direct = sqrtf(dx * dx + dy * dy + dz * dz);

	// � ������ ���� ��������� �� ��������� ������ ��� ������������ ��������� ���������� ��������� � 0
	if (direct > MaxDist)
		return SQUALL_ERROR_CREATE_CHANNEL;

	// ��������� ��������� �� ������ ������
	SoundData = api_SampleGetFile(SampleID);
	if (!SoundData)
		result = SQUALL_ERROR_SAMPLE_BAD;

	// ����� ���������� ����� ��� ����
	if (IsTrue(result)) {
		channel = context->GetFreeChannel(Priority);
		if (channel < 0)
			result = SQUALL_ERROR_NO_FREE_CHANNEL;
	}

	// �������� ������� ����� � �������� �����
	if (IsTrue(result)) {
		// ���������� �����
		count = context->_channelsArray[channel]._count;
		memset(&context->_channelsArray[channel], 0, sizeof(SSample));
		context->_channelsArray[channel]._count = count;

		// ���������� ������� �������� ���������
		context->_channelsArray[channel].ChannelID = context->GetChannelID(channel);
		context->_channelsArray[channel].Status.SOUND_TYPE = TYPE_POSITIONED;
		context->_channelsArray[channel].GroupID = ChannelGroupID;
		context->_channelsArray[channel].Status.SAMPLE_LOOP = Loop;
		context->_channelsArray[channel].SoundFile = SoundData;
		context->_channelsArray[channel].SampleID = SampleID;
		context->_channelsArray[channel].EndPtr = SoundData->GetSamplesInFile();
		context->_channelsArray[channel].MasterSize = context->_channelsArray[channel].EndPtr;
		context->_channelsArray[channel].SamplesPerSec = SoundData->GetFormat()->nSamplesPerSec;
		context->_channelsArray[channel].Priority = Priority;
		context->_channelsArray[channel].Status.STAGE = PREPARE;

		// �������� �������� �����
		if (!context->_channelsArray[channel].Create3DSoundBuffer(context->_directSound,
											  	SoundData->GetFormat(),
											  	SoundData->GetSamplesInFile(),
											  	context->_bufferSize,
											  	context->_used3DAlgorithm,
											  	context->_useEax,
											  	context->_useHW3D))
			result = SQUALL_ERROR_CREATE_CHANNEL;
	}

	// ��������� ���������� ���������
	if (IsTrue(result))
		if (!context->_channelsArray[channel].Set3DParameters((D3DVECTOR *) Position,
										  	(D3DVECTOR *)Velocity,
										  	0,
										  	0,
										  	0,
										  	0,
										  	MinDist,
										  	MaxDist,
										  	context->_deferred))
			result = SQUALL_ERROR_SET_CHANNEL_PARAM;

	// ���������� ������� ������ �������� ������
	if (IsTrue(result))
		if (!context->_channelsArray[channel].FillSoundBuffer(0))
			result = SQUALL_ERROR_SET_CHANNEL_PARAM;

	// ��������� ������ ��������� ������
	if (IsTrue(result))
		if (!context->_channelsArray[channel].SetVolume(volume_table[Volume]))
			result = SQUALL_ERROR_SET_CHANNEL_PARAM;

	// ��������� �������
	if (IsTrue(result))
		if (Frequency)
			if (!context->_channelsArray[channel].SetFrequency(Frequency))
				result = SQUALL_ERROR_SET_CHANNEL_PARAM;

	// �������� �� ���������������
	if (IsTrue(result))
		if (Start)
			if (!context->_channelsArray[channel].Play())
				result = SQUALL_ERROR_SET_CHANNEL_PARAM;

	// ���� ���� ������ ������ ��� ��������
	if (IsFalse(result)) {
		if (channel != -1) {
			context->_channelsArray[channel].DeleteSoundBuffer();
			context->_channelsArray[channel].Status.STAGE = EMPTY;
		}
	}

	// ���� ������ �� ���� ������ ������������� ������
	if (IsTrue(result))
		result = context->_channelsArray[channel].ChannelID;

	// ������ ��������� ������
	return result;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//  				 ����� ������ ��� ������ � ��������
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// ������ ��������������� ��������������� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_Start(int ChannelID)
#else
DLL_API int SQUALL_Channel_Start(int ChannelID)
#endif
{
	// ����������
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_Start(0x%X)", ChannelID);
#endif

	// ����� ����� �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
	}

	// ������ ���������������
	if (IsTrue(result))
		if (context->_channelsArray[channel].Status.STAGE == PREPARE)
			if (!context->_channelsArray[channel].Play())
				result = SQUALL_ERROR_SET_CHANNEL_PARAM;

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ���������/���������� ����� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//  			  Pause 	  -  ���� ���������/���������� �����, �������� �����
//  							 ��������� ��������� ��������:
//  							 true  - �������� �����
//  							 false - ��������� �����
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_Pause(int ChannelID, int PauseFlag)
#else
DLL_API int SQUALL_Channel_Pause(int ChannelID, int PauseFlag)
#endif
{
	// ����������
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_Pause(0x%X, %d)", ChannelID, PauseFlag);
#endif

	// ����� ������ �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
	}

	// �������� �� ����� �����
	if (IsTrue(result))
		if (!context->_channelsArray[channel].Pause(PauseFlag))
			result = SQUALL_ERROR_SET_CHANNEL_PARAM;

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ��������� ������ �� ��������������
// �� �����    :  ChannelID   -  ������������� ��������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_Stop(int ChannelID)
#else
DLL_API int SQUALL_Channel_Stop(int ChannelID)
#endif
{
	// ����������
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_Stop(0x%X)", ChannelID);
#endif

	// ����� ����� �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
	}

	// ����� ����� �� ��������������
	if (IsTrue(result))
		if (!context->_channelsArray[channel].Stop())
			result = SQUALL_ERROR_SET_CHANNEL_PARAM;

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ������� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//  			  � ������ ��������� ������ ��������� �������� ������ ������,
//  			  ��������� ����� ��������� ��������� ��������:
//  			  SQUALL_CHANNEL_STATUS_NONE	   -  ��������� ������ � �����
//  												  ��������������� ���
//  			  SQUALL_CHANNEL_STATUS_PLAY	   -  �������� �����
//  												  ���������������
//  			  SQUALL_CHANNEL_STATUS_PAUSE      -  �������� ����� ���������
//  												  � ������ �����
//  			  SQUALL_CHANNEL_STATUS_PREPARED   -  �������� �����
//  												  �����������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_Status(int ChannelID)
#else
DLL_API int SQUALL_Channel_Status(int ChannelID)
#endif
{
	// ����������
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_Status(0x%X)", ChannelID);
#endif

	// ����� ����� �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_CHANNEL_STATUS_NONE;
		else if (context->_channelsArray[channel].Status.STAGE == PLAY)
			result = SQUALL_CHANNEL_STATUS_PLAY;
		else if (context->_channelsArray[channel].Status.STAGE == PAUSE)
			result = SQUALL_CHANNEL_STATUS_PAUSE;
		else if (context->_channelsArray[channel].Status.STAGE == PREPARE)
			result = SQUALL_CHANNEL_STATUS_PREPARED;
		else
			result = SQUALL_ERROR_UNKNOWN;
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else
		api_Log("\t\tresult = %d", result);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ������ ������ ��������� ��������� ������ � ���������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//  			  Volume	  -  �������� ������ ��������� � ���������,
//  							 �������� ���������� ������ ���� � ��������
//  							 �� 0 �� 100
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_SetVolume(int ChannelID, int Volume)
#else
DLL_API int SQUALL_Channel_SetVolume(int ChannelID, int Volume)
#endif
{
	// ����������
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_SetVolume(0x%X, %d)", ChannelID, Volume);
#endif

	// �������� ����������
	if (IsTrue(result))
		if ((Volume < 0) || (Volume > 100))
			result = SQUALL_ERROR_INVALID_PARAM;

	// ����� ����� �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
	}

	// ��������� ����� ���������
	if (IsTrue(result))
		if (!context->_channelsArray[channel].SetVolume(volume_table[Volume]))
			result = SQUALL_ERROR_SET_CHANNEL_PARAM;

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� �������� ������ ��������� ��������� ������ � ���������
// �� �����    :  ChannelID   -  ������������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//  			  � ������ ��������� ������ ��������� �������� ������� ��������
//  			  ��������� ������ � ���������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_GetVolume(int ChannelID)
#else
DLL_API int SQUALL_Channel_GetVolume(int ChannelID)
#endif
{
	// ����������
	long DxVolume = 0;
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

#if SQUALL_DEBUG
	// ���������� ����������
	api_LogTime("SQUALL_Channel_GetVolume(0x%X)", ChannelID);
#endif

	// ����� ����� �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
	}

	// ��������� ���������   
	if (IsTrue(result))
		if (!context->_channelsArray[channel].GetVolume(&DxVolume))
			result = SQUALL_ERROR_GET_CHANNEL_PARAM;
		else
			result = dxvolume_to_squallvolume(DxVolume);

		// ���������� ����������
#if SQUALL_DEBUG 
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else
		api_Log("\t\tresult = %d", result);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}
//-----------------------------------------------------------------------------
// �������� ����� ������� ������������� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//  			  Frequency   -  ����� �������� ������� �������������, ��������
//  							 ��������� ������ ���� � �������� �� 100 ����
//  							 �� 1000000 ����
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_SetFrequency(int ChannelID, int Frequency)
#else
DLL_API int SQUALL_Channel_SetFrequency(int ChannelID, int Frequency)
#endif
{
	// ����������
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_SetFrequency(0x%X, %d)", ChannelID, Frequency);
#endif

	// �������� ����������
	if (IsTrue(result))
		if ((Frequency < 100) || (Frequency > 100000))
			result = SQUALL_ERROR_INVALID_PARAM;

	// ����� ����� �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
	}

	// ��������� ����� �������
	if (IsTrue(result))
		if (!context->_channelsArray[channel].SetFrequency(Frequency))
			result = SQUALL_ERROR_SET_CHANNEL_PARAM;

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ������� ������� ������������� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//  			  � ������ ��������� ������ ��������� �������� ������� ��������
//  			  ������� ������������� ��������� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_GetFrequency(int ChannelID)
#else
DLL_API int SQUALL_Channel_GetFrequency(int ChannelID)
#endif
{
	// ����������
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_GetFrequency(0x%X)", ChannelID);
#endif

	// ����� ����� �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
	}

	// ������� ������� �������������
	if (IsTrue(result))
		if (!context->_channelsArray[channel].GetFrequency(&result))
			result = SQUALL_ERROR_GET_CHANNEL_PARAM;

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else
		api_Log("\t\tresult = %d", result);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ����� ������� ��������������� ��������� ������ � �������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//  			  Position    -  ����� �������� ������� ���������������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_SetPlayPosition(int ChannelID, int PlayPosition)
#else
DLL_API int SQUALL_Channel_SetPlayPosition(int ChannelID, int PlayPosition)
#endif
{
	// ����������
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_SetPlayPosition(0x%X, %d)",
		ChannelID,
		PlayPosition);
#endif

	// ����� ����� �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
	}

	// ��������� ����� ���������� ����� � ������������
	if (IsTrue(result))
		if (!context->_channelsArray[channel].SetPlayPosition(PlayPosition))
			result = SQUALL_ERROR_SET_CHANNEL_PARAM;

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}
//-----------------------------------------------------------------------------
// ��������� ������� ������� ��������������� ��������� ������ � �������
// �� �����    :  ChannelID   -  ������������� ��������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//  			  � ������ ��������� ������ ��������� �������� ������� �������
//  			  ���������������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_GetPlayPosition(int ChannelID)
#else
DLL_API int SQUALL_Channel_GetPlayPosition(int ChannelID)
#endif
{
	// ����������
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_GetPlayPosition(0x%X)", ChannelID);
#endif

	// ����� ����� �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
	}

	// ��������� ������� ������� ���������������
	if (IsTrue(result))
		if (!context->_channelsArray[channel].GetPlayPosition(&result))
			result = SQUALL_ERROR_SET_CHANNEL_PARAM;

#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else
		api_Log("\t\tresult = %d", result);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ����� ������� ��������������� ��������� ������ � �������������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//  			  Position    -  ����� �������� ������� ���������������,
//  							 � �������������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_SetPlayPositionMs(int ChannelID, int PlayPosition)
#else
DLL_API int SQUALL_Channel_SetPlayPositionMs(int ChannelID, int PlayPosition)
#endif
{
	// ����������
	int position = 0;   
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_SetPlayPositionMs(0x%X, %d)",
		ChannelID,
		PlayPosition);
#endif

	// ����� ����� �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
	}

	// ��������� ����� ������� ���������������
	if (IsTrue(result)) {
		// ������� �������������� ������� � ������
		position = (int)
			(((__int64)
			PlayPosition * (__int64)
			context->_channelsArray[channel].SamplesPerSec) /
			(__int64)
			1000);
		if (context->_channelsArray[channel].MasterSize < position)
			result = SQUALL_ERROR_INVALID_PARAM;
	}
	// ��������� ����� ������� ���������������
	if (IsTrue(result))
		if (context->_channelsArray[channel].SetPlayPosition(position))
			result = SQUALL_ERROR_SET_CHANNEL_PARAM;

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ������� ������� ��������������� ��������� ������ � �������������
// �� �����    :  ChannelID   -  ������������� ��������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//  			  � ������ ��������� ������ ��������� �������� ������� �������
//  			  ���������������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_GetPlayPositionMs(int ChannelID)
#else
DLL_API int SQUALL_Channel_GetPlayPositionMs(int ChannelID)
#endif
{
	// ����������
	int position = 0;   
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_GetPlayPositionMs(0x%X)", ChannelID);
#endif

	// ����� ����� �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
	}

	// ��������� ������� ������� ���������������
	if (IsTrue(result))
		if (!context->_channelsArray[channel].GetPlayPosition(&position))
			result = SQUALL_ERROR_GET_CHANNEL_PARAM;
		else
			result = (int)
				((__int64) (position * (__int64) 1000) /
				(__int64) context->_channelsArray[channel].SamplesPerSec);

		// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else
		api_Log("\t\tresult = %d", result);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ����������� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//  			  Worker	  -  ��������� �� ���������� ��������� ������
//  			  Param 	  -  ��������� �� ������ ������������, � ������
//  							 ���� ������ ������������ ���, �������� �����
//  							 ��������� 0
//  			  UpdateTime  -  ���������� ������� � ������������� �����
//  							 ������� ����� �������� ����������, ��������
//  							 ��������� ������ ���� � �������� �� 1 �� 5000
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_SetWorker(int ChannelID, squall_callback_channel_t Worker,
	void* Param, unsigned int UpdateTime)
#else
DLL_API int SQUALL_Channel_SetWorker(int ChannelID,
	squall_callback_channel_t Worker, void* Param, unsigned int UpdateTime)
#endif
{
	// ����������
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_SetWorker(0x%X, %0x%X)", ChannelID, Worker);
#endif

	// ����� ������ �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
	}

	// ��������� ����������
	if (IsTrue(result))
		if (!Worker) {
			// �������� �����������
			context->_channelsArray[channel].ChannelWorker = 0;
			context->_channelsArray[channel].UserData = 0;
			context->_channelsArray[channel].ChannelWorkerTime = 0;
		} else {
			if (IsBadCodePtr((FARPROC) Worker) || (UpdateTime <= 0))
				result = SQUALL_ERROR_INVALID_PARAM;
			else {
				// ��������� �����������
				context->_channelsArray[channel].ChannelWorker = Worker;
				context->_channelsArray[channel].UserData = Param;
				context->_channelsArray[channel].ChannelWorkerTime = UpdateTime;
			}
		}

		// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ����������� ��������� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//  			  Worker	  -  ��������� �� ���������� ��������� ������
//  			  Param 	  -  ��������� �� ������ ������������, � ������
//  							 ���� ������ ������������ ���, �������� �����
//  							 ��������� 0
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_SetEndWorker(int ChannelID,
	squall_callback_end_channel_t Worker, void* Param)
#else
DLL_API int SQUALL_Channel_SetEndWorker(int ChannelID,
	squall_callback_end_channel_t Worker, void* Param)
#endif
{
	// ����������
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_SetEndWorker(0x%X, %0x%X)", ChannelID, Worker);
#endif

	// ����� ������ �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
	}

	// ��������� ����������
	if (IsTrue(result))
		if (!Worker) {
			// �������� �����������
			context->_channelsArray[channel].ChannelEndWorker = 0;
			context->_channelsArray[channel].ChannelEndUserData = 0;
		} else {
			if (IsBadCodePtr((FARPROC) Worker))
				result = SQUALL_ERROR_INVALID_PARAM;
			else {
				// ��������� �����������
				context->_channelsArray[channel].ChannelEndWorker = Worker;
				context->_channelsArray[channel].ChannelEndUserData = Param;
			}
		}

		// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ����� ������ ��������� ��������� ������ � �������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//  			  Start 	  -  ��������� ������� ���������, � ��������
//  			  End   	  -  �������� ������� ���������, � ��������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_SetFragment(int ChannelID, int Start, int End)
#else
DLL_API int SQUALL_Channel_SetFragment(int ChannelID, int Start, int End)
#endif
{
	// ����������
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_SetFragment(0x%X, %d, %d)",
		ChannelID,
		Start,
		End);
#endif

	// �������� ����������
	if (IsTrue(result))
		if ((Start < 0) || (End < 0) || (Start == End))
			result = SQUALL_ERROR_INVALID_PARAM;

	// ����� ������ �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
	}

	// ��������� �������
	if (IsTrue(result))
		if (!context->_channelsArray[channel].SetFragment(Start, End))
			result = SQUALL_ERROR_SET_CHANNEL_PARAM;

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ������� ������ ��������� ��������� ������ � �������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//  			  Start 	  -  ��������� �� ���������� � ������� �����
//  							 ��������� ��������� ������� ��������� �
//  							 ��������
//  			  End   	  -  ��������� �� ���������� � ������� �����
//  							 ��������� �������� ������� ���������
//  							 � ��������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_GetFragment(int ChannelID, int* Start, int* End)
#else
DLL_API int SQUALL_Channel_GetFragment(int ChannelID, int* Start, int* End)
#endif
{
	// ����������
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_GetFragment(0x%X, 0x%X, 0x%X)",
		ChannelID,
		Start,
		End);
#endif

	// �������� ����������
	if (IsBadWritePtr(Start, sizeof(int)))
		Start = 0;
	if (IsBadWritePtr(End, sizeof(int)))
		End = 0;

	// �������� ����������
	if (IsTrue(result))
		if ((Start == 0) && (End == 0))
			result = SQUALL_ERROR_INVALID_PARAM;

	// ����� ������ �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
	}

	// ��������� ������
	if (IsTrue(result)) {
		if (Start)
			*Start = context->_channelsArray[channel].StartPtr;
		if (End)
			*End = context->_channelsArray[channel].EndPtr;
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else {
		if (Start)
			api_Log("\t\t[out]*Start = %d", * Start);
		if (End)
			api_Log("\t\t[out]*End = %d", * End);
	}
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ����� ������ ��������� ��������� ������ � �������������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//  			  Start 	  -  ��������� ������� ���������, ������� �
//  							 �������������
//  			  End   	  -  �������� ������� ���������, ������� �
//  							 �������������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_SetFragmentMs(int ChannelID, int Start, int End)
#else
DLL_API int SQUALL_Channel_SetFragmentMs(int ChannelID, int Start, int End)
#endif
{
	// ����������
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_SetFragmentMs(0x%X, %d, %d)",
		ChannelID,
		Start,
		End);
#endif

	// �������� ����������
	if (IsTrue(result))
		if ((Start < 0) || (End < 0) || (Start == End))
			result = SQUALL_ERROR_INVALID_PARAM;

	// ����� ������ �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
	}

	// ��������� �������
	if (IsTrue(result)) {
		// �������������� ����� � ������
		int StartPtr = (int)
			((__int64)
			((__int64) Start * (__int64) context->_channelsArray[channel].SamplesPerSec) /
			(__int64)
			1000);
		int EndPtr = (int)
			(((__int64)
			End * (__int64)
			context->_channelsArray[channel].SamplesPerSec) /
			(__int64)
			1000);
		if (!context->_channelsArray[channel].SetFragment(StartPtr, EndPtr))
			result = SQUALL_ERROR_SET_CHANNEL_PARAM;
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ������� ������ ��������� ��������� ������ � �������������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//  			  Start 	  -  ��������� �� ���������� � ������� �����
//  							 ��������� ��������� ������� ���������
//  							 � �������������
//  			  End   	  -  ��������� �� ���������� � ������� �����
//  							 ��������� �������� ������� ���������
//  							 � �������������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_GetFragmentMs(int ChannelID, int* Start, int* End)
#else
DLL_API int SQUALL_Channel_GetFragmentMs(int ChannelID, int* Start, int* End)
#endif
{
	// ����������
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_GetFragmentMs(0x%X, 0x%X, 0x%X)",
		ChannelID,
		Start,
		End);
#endif

	// �������� ����������
	if (IsBadWritePtr(Start, sizeof(int)))
		Start = 0;
	if (IsBadWritePtr(End, sizeof(int)))
		End = 0;

	// �������� ����������
	if (IsTrue(result))
		if ((Start == 0) && (End == 0))
			result = SQUALL_ERROR_INVALID_PARAM;

	// ����� ������ �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
	}

	// ��������� ������
	if (IsTrue(result)) {
		if (Start)
			*Start = (int)
				((__int64)
				(context->_channelsArray[channel].StartPtr * (__int64) 1000) /
				(__int64)
				context->_channelsArray[channel].SamplesPerSec);
		if (End)
			*End = (int)
				((__int64)
				(context->_channelsArray[channel].EndPtr * (__int64) 1000) /
				(__int64)
				context->_channelsArray[channel].SamplesPerSec);
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else {
		if (Start)
			api_Log("\t\t[out]*Start = %d", * Start);
		if (End)
			api_Log("\t\t[out]*End = %d", * End);
	}
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ����������������� �������� �������� ������ � �������
// �� �����    :  ChannelID   -  ������������� ��������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//  			  � ������ ��������� ������ ��������� �������� �����������������
//  			  �������� ������ � �������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_GetLength(int ChannelID)
#else
DLL_API int SQUALL_Channel_GetLength(int ChannelID)
#endif
{
	// ����������
	int samples = 0;   
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_GetLength(0x%X)", ChannelID);
#endif

	// ����� ����� �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
	}

	// ��������� ���������� �������
	if (IsTrue(result)) {
		samples = context->_channelsArray[channel].SoundFile->GetSamplesInFile();
		if (!samples)
			result = SQUALL_ERROR_SAMPLE_BAD;
		else
			result = samples;
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else
		api_Log("\t\tresult = %d", result);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ����������������� �������� �������� ������ � �������������
// �� �����    :  ChannelID   -  ������������� ��������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//  			  � ������ ��������� ������ ��������� �������� �����������������
//  			  �������� ������ � ������������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_GetLengthMs(int ChannelID)
#else
DLL_API int SQUALL_Channel_GetLengthMs(int ChannelID)
#endif
{
	// ����������
	int samples = 0;   
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_GetLengthMs(0x%X)", ChannelID);
#endif

	// ����� ����� �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
	}

	// ��������� ���������� �������
	if (IsTrue(result)) {
		samples = context->_channelsArray[channel].SoundFile->GetSamplesInFile();
		if (!samples)
			result = SQUALL_ERROR_SAMPLE_BAD;
		else
			result = (int)
				((__int64)
				(samples * (__int64) 1000) /
				(__int64)
				context->_channelsArray[channel].SoundFile->GetFormat()->nSamplesPerSec);
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else
		api_Log("\t\tresult = %d", result);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ������ ���������� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//  			  Priority    -  ����� ��������� ������, �������� ���������
//  							 ������ ���� � �������� �� 0 (����� ������
//  							 ���������) �� 65535 (����� ������ ���������)
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_SetPriority(int ChannelID, int Priority)
#else
DLL_API int SQUALL_Channel_SetPriority(int ChannelID, int Priority)
#endif
{
	// ����������
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_SetPriority(0x%X, %d)", ChannelID, Priority);
#endif

	// �������� ����������
	if (IsTrue(result))
		if (Priority < 0)
			result = SQUALL_ERROR_INVALID_PARAM;

	// ����� ����� �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
		else
			context->_channelsArray[channel].Priority = Priority;
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� �������� ���������� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//  			  � ������ ��������� ������ ��������� �������� ���������
//  			  ��������� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_GetPriority(int ChannelID)
#else
DLL_API int SQUALL_Channel_GetPriority(int ChannelID)
#endif
{
	// ����������
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_GetPriority(0x%X)", ChannelID);
#endif

	// ����� ����� �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
		else
			result = context->_channelsArray[channel].Priority;
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else
		api_Log("\t\tresult = %d", result);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� �������� �������� ����� ������������� ��������������� ���������
// ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//  			  � ������ ��������� ������ ��������� �������� ������� ��������
//  			  ����� ������������� ��������������� ������, ��������� �����
//  			  ��������� ��������� ��������:
//  			  true  -  �������� ����� ��������������� ����������
//  			  false -  �������� ����� ��������������� ���� ���
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_SetLoop(int ChannelID, int Loop)
#else
DLL_API int SQUALL_Channel_SetLoop(int ChannelID, int Loop)
#endif
{
	// ����������
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_SetLoop(0x%X, %d)", ChannelID, Loop);
#endif

	// ����� ����� �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
		else {
			context->_channelsArray[channel].Pause(true);
			context->_channelsArray[channel].Status.SAMPLE_LOOP = Loop;
			// ���� ���� ��������� � ������ �������� ������������ ������
			if (context->_channelsArray[channel].Status.DOUBLE_BUFFERING == 0)
				context->_channelsArray[channel].Status.BUFFER_LOOP = Loop;
			context->_channelsArray[channel].Pause(false);
		}
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ������ �������� ����� ������������� ��������������� ���������
// ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//  			  Loop  	  -  ���� ������������� ������, �������� ��������
//  							 ����� ��������� ��������� ��������:
//  							 true  -  ����������� ��������������� ���������
//  									  ������
//  							 false -  ��������������� ��������� ������ ����
//  									  ���
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_GetLoop(int ChannelID)
#else
DLL_API int SQUALL_Channel_GetLoop(int ChannelID)
#endif
{
	// ����������
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_GetLoop(0x%X)", ChannelID);
#endif

	// ����� ����� �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
		else
			result = context->_channelsArray[channel].Status.SAMPLE_LOOP;
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else
		api_Log("\t\tresult = %d", result);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//  			  ������ ��� ������ � ����������� ��������
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// ��������� ����� �������� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//  			  Pan   	  -  ����� �������� ��������, �������� ���������
//  							 ������� ���� � �������� �� 0 (������������
//  							 �������� ������ ������� �����) �� 100
//  							 (������������ �������� ������ ������� ������)
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
// ����������  :  ������ ����� �� �������� � ������������ ��������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_SetPan(int ChannelID, int Pan)
#else
DLL_API int SQUALL_Channel_SetPan(int ChannelID, int Pan)
#endif
{
	// ����������
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_SetPan(0x%X, %d)", ChannelID, Pan);
#endif

	// �������� ����������
	if (IsTrue(result))
		if ((Pan < 0) || (Pan > 100))
			result = SQUALL_ERROR_INVALID_PARAM;

	// ����� ����� �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
	}

	// �������� ����������� ������
	if (IsTrue(result))
		if (context->_channelsArray[channel].Status.SOUND_TYPE != TYPE_AMBIENT)
			result = SQUALL_ERROR_METHOD;

	// ��������� ����� ��������
	if (IsTrue(result))
		if (!context->_channelsArray[channel].SetPan(Pan))
			result = SQUALL_ERROR_SET_CHANNEL_PARAM;

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ������� �������� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//  			  � ������ ��������� ������ ��������� �������� ������� ��������
//  			  �������� ������
// ����������  :  ������ ����� �� �������� � ������������ ��������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_GetPan(int ChannelID)
#else
DLL_API int SQUALL_Channel_GetPan(int ChannelID)
#endif
{
	// ����������
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_GetPan(0x%X)", ChannelID);
#endif

	// ����� ����� �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
	}

	// �������� ����������� ������
	if (IsTrue(result))
		if (context->_channelsArray[channel].Status.SOUND_TYPE != TYPE_AMBIENT)
			result = SQUALL_ERROR_METHOD;

	// ������� ������� ��������
	if (IsTrue(result))
		if (!context->_channelsArray[channel].GetPan(&result))
			result = SQUALL_ERROR_SET_CHANNEL_PARAM;

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else
		api_Log("\t\tresult = %d", result);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//  			  ������ ��� ������ � ������������ ��������
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// ��������� ����� ���������� ������� ��������� ������ � ������������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//  			  Position    -  ��������� �� ��������� � ������ ������������
//  							 ������ � ������������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
// ����������  :  ������ ����� �� �������� � ����������� ��������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_Set3DPosition(int ChannelID, float* Position)
#else
DLL_API int SQUALL_Channel_Set3DPosition(int ChannelID, float* Position)
#endif
{
	// ����������
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_Set3DPosition(0x%X, 0x%X)",
		ChannelID,
		Position);
#endif

	// �������� ����������
	if (IsBadReadPtr(Position, sizeof(float) * 3))
		Position = 0;

	// ���������� ����������
#if SQUALL_DEBUG
	// ������� �����
	if (Position) {
		api_Log("\t\t[in]Position->x = %f", Position[0]);
		api_Log("\t\t[in]Position->y = %f", Position[1]);
		api_Log("\t\t[in]Position->z = %f", Position[2]);
	}
#endif

	// �������� ����������
	if (IsTrue(result))
		if (!Position)
			result = SQUALL_ERROR_INVALID_PARAM;

	// ����� ����� �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
	}

	// �������� ����������� ������
	if (IsTrue(result))
		if (context->_channelsArray[channel].Status.SOUND_TYPE !=
			TYPE_POSITIONED)
			result = SQUALL_ERROR_METHOD;

	// ��������� ����� ���������� ����� � ������������
	if (IsTrue(result))
		if (!context->_channelsArray[channel].Set3DParameters((D3DVECTOR *)
											  	Position,
											  	0,
											  	0,
											  	0,
											  	0,
											  	0,
											  	0,
											  	0,
											  	context->_deferred))
			result = SQUALL_ERROR_SET_CHANNEL_PARAM;

	// ���������� ����������
#if SQUALL_DEBUG 
	if (IsFalse(result))
		api_Log("error = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ������� ���������� ������� ��������� ������ � ������������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//  			  Position    -  ��������� �� ��������� � ������� �����
//  							 ��������� ������� ���������� ������� ���������
//  							 ������ � ������������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
// ����������  :  ������ ����� �� �������� � ����������� ��������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_Get3DPosition(int ChannelID, float* Position)
#else
DLL_API int SQUALL_Channel_Get3DPosition(int ChannelID, float* Position)
#endif
{
	// ����������
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_Get3DPosition(0x%X, 0x%X)",
		ChannelID,
		Position);
#endif

	// �������� ����������
	if (IsTrue(result))
		if (IsBadWritePtr(Position, sizeof(float) * 3))
			result = SQUALL_ERROR_INVALID_PARAM;

	// ����� ����� �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
	}

	// �������� ����������� ������
	if (IsTrue(result))
		if (context->_channelsArray[channel].Status.SOUND_TYPE !=
			TYPE_POSITIONED)
			result = SQUALL_ERROR_METHOD;

	// ��������� ����� ���������� ����� � ������������
	if (IsTrue(result))
		if (!context->_channelsArray[channel].Get3DParameters((D3DVECTOR *)
											  	Position,
											  	0,
											  	0,
											  	0,
											  	0,
											  	0,
											  	0,
											  	0))
			result = SQUALL_ERROR_SET_CHANNEL_PARAM;

	// ���������� ����������
#if SQUALL_DEBUG 
	if (IsFalse(result))
		api_Log("error = %s", ErrorTable[-result]);
	else {
		api_Log("\t\t[in]Position->x = %f", Position[0]);
		api_Log("\t\t[in]Position->y = %f", Position[1]);
		api_Log("\t\t[in]Position->z = %f", Position[2]);
	}
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ����� �������� ����������� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//  			  Velocity    -  ��������� �� ��������� � ����� ��������
//  							 �������� ����������� ��������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
// ����������  :  ������ ����� �� �������� � ����������� ��������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_SetVelocity(int ChannelID, float* Velocity)
#else
DLL_API int SQUALL_Channel_SetVelocity(int ChannelID, float* Velocity)
#endif
{
	// ����������
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_SetVelocity(0x%X, 0x%X)", ChannelID, Velocity);
#endif

	// �������� ����������
	if (IsBadReadPtr(Velocity, sizeof(float) * 3))
		Velocity = 0;

	// ���������� ����������
#if SQUALL_DEBUG
	// �������� ����������� ��������� �����
	if (Velocity) {
		api_Log("\t\t[in]Velocity->x = %f", Velocity[0]);
		api_Log("\t\t[in]Velocity->y = %f", Velocity[1]);
		api_Log("\t\t[in]Velocity->z = %f", Velocity[2]);
	}
#endif

	// �������� ����������
	if (IsTrue(result))
		if (!Velocity)
			result = SQUALL_ERROR_INVALID_PARAM;

	// ����� ������ �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
	}

	// �������� ����������� ��������� ����������
	if (IsTrue(result))
		if (context->_channelsArray[channel].Status.SOUND_TYPE !=
			TYPE_POSITIONED)
			result = SQUALL_ERROR_METHOD;

	// ��������� ����������
	if (IsTrue(result))
		if (!context->_channelsArray[channel].Set3DParameters(0,
											  	(D3DVECTOR *) Velocity,
											  	0,
											  	0,
											  	0,
											  	0,
											  	0,
											  	0,
											  	context->_deferred))
			result = SQUALL_ERROR_SET_CHANNEL_PARAM;

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ������� �������� ����������� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//  			  Velocity    -  ��������� �� ��������� � ������� �����
//  							 ��������� ������� �������� ������� ��������
//  							 ��������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
// ����������  :  ������ ����� �� �������� � ����������� ��������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_GetVelocity(int ChannelID, float* Velocity)
#else
DLL_API int SQUALL_Channel_GetVelocity(int ChannelID, float* Velocity)
#endif
{
	// ����������
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_GetVelocity(0x%X, 0x%X)", ChannelID, Velocity);
#endif

	// �������� ����������
	if (IsTrue(result))
		if (IsBadWritePtr(Velocity, sizeof(float) * 3))
			result = SQUALL_ERROR_INVALID_PARAM;

	// ����� ������ �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
	}

	// �������� ����������� ��������� ����������
	if (IsTrue(result))
		if (context->_channelsArray[channel].Status.SOUND_TYPE !=
			TYPE_POSITIONED)
			result = SQUALL_ERROR_METHOD;

	// ��������� ����������
	if (IsTrue(result))
		if (!context->_channelsArray[channel].Get3DParameters(0,
											  	(D3DVECTOR *) Velocity,
											  	0,
											  	0,
											  	0,
											  	0,
											  	0,
											  	0))
			result = SQUALL_ERROR_GET_CHANNEL_PARAM;

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else {
		api_Log("\t\t[out]Velocity->x = %f", Velocity[0]);
		api_Log("\t\t[out]Velocity->y = %f", Velocity[1]);
		api_Log("\t\t[out]Velocity->z = %f", Velocity[2]);
	}
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ������ ������������ � ������������� ���������� ����������
// ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//  			  MinDist     -  ����� ����������� ���������� ����������
//  							 �������� ��������� ������ ���� � ��������
//  							 �� 0.01f �� 1000000000.0f
//  			  MaxDist     -  ����� ������������ ���������� ����������
//  							 �������� ��������� ������ ���� � ��������
//  							 �� 0.01f �� 1000000000.0f
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
// ����������  :  ������ ����� �� �������� � ����������� ��������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_SetMinMaxDistance(int ChannelID, float MinDist,
	float MaxDist)
#else
DLL_API int SQUALL_Channel_SetMinMaxDistance(int ChannelID, float MinDist,
	float MaxDist)
#endif
{
	// ����������
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_SetMinMaxDistance(0x%X, %f, %f)",
		ChannelID,
		MinDist,
		MaxDist);
#endif

	// ����� ����� �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
		else if (!context->_channelsArray[channel].Set3DParameters(0,
												   	0,
												   	0,
												   	0,
												   	0,
												   	0,
												   	MinDist,
												   	MaxDist,
												   	context->_deferred))
			result = SQUALL_ERROR_SET_CHANNEL_PARAM;
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� �������� ������������ ��������� ���������� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//  			  MinDist     -  ��������� �� ���������� � ������� �����
//  							 ��������� ������� ����������� ���������
//  							 ����������
//  			  MinDist     -  ��������� �� ���������� � ������� �����
//  							 ��������� ������� ������������ ���������
//  							 ����������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
// ����������  :  ������ ����� �� �������� � ����������� ��������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_GetMinMaxDistance(int ChannelID, float* MinDist,
	float* MaxDist)
#else
DLL_API int SQUALL_Channel_GetMinMaxDistance(int ChannelID, float* MinDist,
	float* MaxDist)
#endif
{
	// ����������
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_GetMinMaxDistance(0x%X, %d, %d)",
		ChannelID,
		MinDist,
		MaxDist);
#endif

	// �������� �������
	if (IsBadWritePtr(MinDist, sizeof(float)))
		MinDist = 0;
	if (IsBadWritePtr(MaxDist, sizeof(float)))
		MaxDist = 0;

	// �������� ����������
	if (IsTrue(result))
		if ((MinDist == 0) && (MaxDist == 0))
			result = SQUALL_ERROR_INVALID_PARAM;

	// ����� ����� �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
		else {
			// ����������� ���������
			if (MinDist)
				*MinDist = context->_channelsArray[channel].Param.ds3d.flMinDistance;
			// ������������ ���������
			if (MaxDist)
				*MaxDist = context->_channelsArray[channel].Param.ds3d.flMaxDistance;
		}
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else {
		// ����� ����������
		if (MinDist)
			api_Log("\t\t*MinDist = %d", * MinDist);
		if (MaxDist)
			api_Log("\t\t*MaxDist = %d", * MinDist);
	}
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}
//-----------------------------------------------------------------------------
// ��������� ���������� ������ ��������������� ��������� ������
// �� �����    :  ChannelID 		-  ������������� ��������� ������
//  			  Orientation   	-  ��������� �� ��������� � ��������
//  								   ����������� ����������� � �������� ������,
//  								   � ������ ���� �������� ������� �����������
//  								   �������� � ����������� ������ ��������
//  								   �� �����, �� ������ �������� ������
//  								   ��������� 0
//  			  InsideConeAngle   -  ���� ����������� ��������� ������, ��������
//  								   ��������� ������ ���� � �������� �� 1 ��
//  								   360 ��������, � ������ ���� ��������
//  								   ���� ����������� ��������� ������ ��������
//  								   �� �����, �� ������ �������� ������
//  								   ��������� 0
//  			  OutsideConeAngle  -  ���� �������� ��������� ������, ��������
//  								   ��������� ������ ���� � �������� �� 1 ��
//  								   360 ��������, � ������ ���� ��������
//  								   ���� �������� ��������� ������ ��������
//  								   �� �����, �� ������ �������� ������
//  								   ��������� 0
//  			  OutsideVolume 	-  ������� ��������� ��������� �� ���������
//  								   �������� ������, � ��������� ��������
//  								   �������� ������ ���� � �������� �� 0
//  								   �� 100
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
// ����������  :  ������ ����� �� �������� � ����������� ��������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_SetConeParameters(int ChannelID, float* Orientation,
	int InsideConeAngle, int OutsideConeAngle, int OutsideVolume)
#else
DLL_API int SQUALL_Channel_SetConeParameters(int ChannelID,
	float* Orientation, int InsideConeAngle, int OutsideConeAngle,
	int OutsideVolume)
#endif
{
	// ����������
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_SetConeParameters(%X, %X, %d, %d, %d)",
		ChannelID,
		Orientation,
		InsideConeAngle,
		OutsideConeAngle,
		OutsideVolume);
#endif

	// �������� ����������
	if (IsBadWritePtr(Orientation, sizeof(float) * 3))
		Orientation = 0;

#if SQUALL_DEBUG
	if (Orientation) {
		api_Log("\t\t[in]Orientation->x = %f", Orientation[0]);
		api_Log("\t\t[in]Orientation->y = %f", Orientation[1]);
		api_Log("\t\t[in]Orientation->z = %f", Orientation[2]);
	}
#endif
	// �������� ����������
	if (IsTrue(result))
		if ((OutsideVolume < 0) ||
			(OutsideVolume > 100) ||
			(InsideConeAngle < 0) ||
			(InsideConeAngle > 360) ||
			(OutsideConeAngle < 0) ||
			(OutsideConeAngle > 360) ||
			(!Orientation))
			result = SQUALL_ERROR_INVALID_PARAM;

	// ����� ����� �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
		else if (!context->_channelsArray[channel].Set3DParameters(0,
									0,
									(D3DVECTOR *)
									Orientation,
									InsideConeAngle,
									OutsideConeAngle,
									volume_table[OutsideVolume],
									0,
									0,
									context->_deferred))
			result = SQUALL_ERROR_SET_CHANNEL_PARAM;
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ���������� ������ ��������������� ��������� ������
// �� �����    :  ChannelID 		-  ������������� ��������� ������
//  			  Orientation   	-  ��������� �� ��������� � ������� �����
//  								   ��������� ������� ������ �����������
//  								   �������� � ����������� ������, � ������
//  								   ���� �������� ������� �����������
//  								   � �������� ������, �������� �� �����,
//  								   �� ������ �������� ������ ��������� 0
//  			  InsideConeAngle   -  ��������� �� ���������� � ������� �����
//  								   ��������� ������� �������� ����� �����������
//  								   ������ � ��������, � ������ ���� ��������
//  								   ���� ����������� ������ �������� �� �����,
//  								   �� ������ �������� ������ ��������� 0
//  			  OutsideConeAngle  -  ��������� �� ���������� � ������� �����
//  								   ��������� ������� �������� ����� ��������
//  								   ������ � ��������, � ������ ���� ��������
//  								   ���� �������� ������ �������� �� �����,
//  								   �� ������ �������� ������ ��������� 0
//  			  OutsideVolume 	-  ��������� �� ���������� � ������� �����
//  								   ��������� ������� �������� ������� ���������
//  								   ��������� �� ��������� �������� ������, �
//  								   ���������, � ������ ���� �������� ������
//  								   ��������� �� ��������� ������� ������
//  								   �������� �� �����, �� ������ ��������
//  								   ������ ��������� 0
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
// ����������  :  ������ ����� �� �������� � ����������� ��������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_GetConeParameters(int ChannelID, float* Orientation,
	int* InsideConeAngle, int* OutsideConeAngle, int* OutsideVolume)
#else
DLL_API int SQUALL_Channel_GetConeParameters(int ChannelID,
	float* Orientation, int* InsideConeAngle, int* OutsideConeAngle,
	int* OutsideVolume)
#endif
{
	// ����������
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_GetConeParameters(0x%X, 0x%X, 0x%X, 0x%X, 0x%X)",
		ChannelID,
		Orientation,
		InsideConeAngle,
		OutsideConeAngle,
		OutsideVolume);
#endif

	// �������� ����������
	if (IsBadWritePtr(Orientation, sizeof(float) * 3))
		Orientation = 0;
	if (IsBadWritePtr(InsideConeAngle, sizeof(int)))
		InsideConeAngle = 0;
	if (IsBadWritePtr(OutsideConeAngle, sizeof(int)))
		OutsideConeAngle = 0;
	if (IsBadWritePtr(OutsideVolume, sizeof(int)))
		OutsideVolume = 0;

	// ����� ����� �� ��������������
	if (IsTrue(result)) {
		long ocv = 0;
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
		else 
		if (!context->_channelsArray[channel].Get3DParameters(0,
								   	0,
								   	(D3DVECTOR *) Orientation,
								   	InsideConeAngle,
								   	OutsideConeAngle,
								   	& ocv,
								   	0,
								   	0))
			result = SQUALL_ERROR_SET_CHANNEL_PARAM;
		else
			*OutsideVolume = dxvolume_to_squallvolume(ocv);
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else {
		if (Orientation) {
			api_Log("\t\t[out]Orientation->x    = %f", Orientation[0]);
			api_Log("\t\t[out]Orientation->y    = %f", Orientation[1]);
			api_Log("\t\t[out]Orientation->z    = %f", Orientation[2]);
		}
		if (InsideConeAngle)
			api_Log("\t\t[out]*InsideConeAngle  = %d", * InsideConeAngle);
		if (OutsideConeAngle)
			api_Log("\t\t[out]*OutsideConeAngle = %d", * OutsideConeAngle);
		if (OutsideVolume)
			api_Log("\t\t[out]*OutsideVolume    = %d", * OutsideVolume);
	}
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ����� EAX ���������� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//  			  Version     -  ����� ������ EAX, �������� ���������� � �����
//  							 ������� ���������� EAX ��������� ������.
//  			  Properties  -  ��������� �� ��������� ����������� ���������
//  							 EAX ������, ��������� ������ ���� � �������
//  							 ��������� ���������� Version
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
// ����������  :  ������ ����� �� �������� � ����������� ��������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_EAX_SetProperties(int ChannelID, int Version,
	squall_eax_channel_t* Properties)
#else
DLL_API int SQUALL_Channel_EAX_SetProperties(int ChannelID, int Version,
	squall_eax_channel_t* Properties)
#endif
{
	// ����������
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_EAX_SetProperties(0x%X, %d, 0x%X)",
		ChannelID,
		Version,
		Properties);
#endif

	// �������� ����������
	if (IsBadReadPtr(Properties, sizeof(squall_eax_channel_t)))
		Properties = 0;

	// ���������� ����������
#if SQUALL_DEBUG
	// ������� ���������
	if (Properties) {
		switch (Version) {
			// EAX 1.0
		case 1:
			api_Log("\t\t[in]Properties->Mix                 = %d",
				Properties->eax1.Mix);
			break;
			// EAX 2.0
		case 2:
			api_Log("\t\t[in]Properties->Direct              = %d",
				Properties->eax2.Direct);
			api_Log("\t\t[in]Properties->DirectHF            = %d",
				Properties->eax2.DirectHF);
			api_Log("\t\t[in]Properties->Room                = %d",
				Properties->eax2.Room);
			api_Log("\t\t[in]Properties->RoomHF              = %d",
				Properties->eax2.RoomHF);
			api_Log("\t\t[in]Properties->RoomRolloffFactor   = %f",
				Properties->eax2.RoomRolloffFactor);
			api_Log("\t\t[in]Properties->Obstruction         = %d",
				Properties->eax2.Obstruction);
			api_Log("\t\t[in]Properties->ObstructionLFRatio  = %f",
				Properties->eax2.ObstructionLFRatio);
			api_Log("\t\t[in]Properties->Occlusion           = %d",
				Properties->eax2.Occlusion);
			api_Log("\t\t[in]Properties->OcclusionLFRatio    = %f",
				Properties->eax2.OcclusionLFRatio);
			api_Log("\t\t[in]Properties->OcclusionRoomRatio  = %f",
				Properties->eax2.OcclusionRoomRatio);
			api_Log("\t\t[in]Properties->OutsideVolumeHF     = %d",
				Properties->eax2.OutsideVolumeHF);
			api_Log("\t\t[in]Properties->AirAbsorptionFactor = %f",
				Properties->eax2.AirAbsorptionFactor);
			api_Log("\t\t[in]Properties->Flags               = %d",
				Properties->eax2.Flags);
			break;
			// EAX 3.0
		case 3:
			api_Log("\t\t[in]Properties->Direct               = %d",
				Properties->eax3.Direct);
			api_Log("\t\t[in]Properties->DirectHF             = %d",
				Properties->eax3.DirectHF);
			api_Log("\t\t[in]Properties->Room                 = %d",
				Properties->eax3.Room);
			api_Log("\t\t[in]Properties->RoomHF               = %d",
				Properties->eax3.RoomHF);
			api_Log("\t\t[in]Properties->Obstruction          = %d",
				Properties->eax3.Obstruction);
			api_Log("\t\t[in]Properties->ObstructionLFRatio   = %f",
				Properties->eax3.ObstructionLFRatio);
			api_Log("\t\t[in]Properties->Occlusion            = %d",
				Properties->eax3.Occlusion);
			api_Log("\t\t[in]Properties->OcclusionLFRatio     = %f",
				Properties->eax3.OcclusionLFRatio);
			api_Log("\t\t[in]Properties->OcclusionRoomRatio   = %f",
				Properties->eax3.OcclusionRoomRatio);
			api_Log("\t\t[in]Properties->OcclusionDirectRatio = %f",
				Properties->eax3.OcclusionDirectRatio);
			api_Log("\t\t[in]Properties->Exclusion            = %d",
				Properties->eax3.Exclusion);
			api_Log("\t\t[in]Properties->ExclusionLFRatio     = %f",
				Properties->eax3.ExclusionLFRatio);
			api_Log("\t\t[in]Properties->OutsideVolumeHF      = %d",
				Properties->eax3.OutsideVolumeHF);
			api_Log("\t\t[in]Properties->DopplerFactor        = %f",
				Properties->eax3.DopplerFactor);
			api_Log("\t\t[in]Properties->RolloffFactor        = %f",
				Properties->eax3.RolloffFactor);
			api_Log("\t\t[in]Properties->RoomRolloffFactor    = %f",
				Properties->eax3.RoomRolloffFactor);
			api_Log("\t\t[in]Properties->AirAbsorptionFactor  = %f",
				Properties->eax3.AirAbsorptionFactor);
			api_Log("\t\t[in]Properties->Flags                = %d",
				Properties->eax3.Flags);
			break;
		}
	}
#endif

	// �������� ����������
	if (IsTrue(result))
		if ((!Properties) || (Version < 0) || (Version > EAX_NUM))
			result = SQUALL_ERROR_INVALID_PARAM;

	// �������� ���������� ������
	if (IsTrue(result))
		if (!context->_eaxSupport[Version])
			result = SQUALL_ERROR_EAX_VERSION;

	// ����� ����� �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
	}

	// ���������� � ������� ������   
	if (IsTrue(result)) {
		memcpy(&context->_channelsArray[channel].Param.EAXBP,
			Properties,
			sizeof(squall_eax_channel_t));
		if (!eax_Set(context->_channelsArray[channel].DS3D_PropSet,
			 	EAX_BUFFER,
			 	Version,
			 	& context->_channelsArray[channel].Param.EAXBP))
			result = SQUALL_ERROR_SET_EAX_PARAM;
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ������� EAX ���������� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//  			  Version     -  ����� ������ EAX, �������� ���������� � �����
//  							 ������� �������� EAX ��������� ������.
//  			  Properties  -  ��������� �� ��������� ���� ����� ���������
//  							 ������� ��������� EAX ������, ��������� �����
//  							 ��������� ����������� � ������� ���������
//  							 ���������� Version
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
// ����������  :  ������ ����� �� �������� � ����������� ��������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_EAX_GetProperties(int ChannelID, int Version,
	squall_eax_channel_t* Properties)
#else
DLL_API int SQUALL_Channel_EAX_GetProperties(int ChannelID, int Version,
	squall_eax_channel_t* Properties)
#endif
{
	// ����������
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_EAX_GetProperties(0x%X, %d, 0x%X)",
		ChannelID,
		Version,
		Properties);
#endif

	// �������� ����������
	if (IsTrue(result))
		if ((Version < 0) ||
			(Version > EAX_NUM) ||
			IsBadWritePtr(Properties,
				sizeof(squall_eax_channel_t)))
			result = SQUALL_ERROR_INVALID_PARAM;

	// �������� ���������� ������
	if (IsTrue(result))
		if (!context->_eaxSupport[Version])
			result = SQUALL_ERROR_EAX_VERSION;

	// ����� ����� �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
	}

	// ������� ������
	if (IsTrue(result))
		if (!eax_Get(context->_channelsArray[channel].DS3D_PropSet,
			 	EAX_BUFFER,
			 	Version,
			 	& context->_channelsArray[channel].Param.EAXBP))
			result = SQUALL_ERROR_GET_EAX_PARAM;
		else
			memcpy(Properties,
				& context->_channelsArray[channel].Param.EAXBP,
				sizeof(squall_eax_channel_t));

		// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else {
		switch (Version) {
			// EAX 1.0
		case 1:
			api_Log("\t\t[out]Properties->Mix                 = %d",
				Properties->eax1.Mix);
			break;
			// EAX 2.0
		case 2:
			api_Log("\t\t[out]Properties->Direct              = %d",
				Properties->eax2.Direct);
			api_Log("\t\t[out]Properties->DirectHF            = %d",
				Properties->eax2.DirectHF);
			api_Log("\t\t[out]Properties->Room                = %d",
				Properties->eax2.Room);
			api_Log("\t\t[out]Properties->RoomHF              = %d",
				Properties->eax2.RoomHF);
			api_Log("\t\t[out]Properties->RoomRolloffFactor   = %f",
				Properties->eax2.RoomRolloffFactor);
			api_Log("\t\t[out]Properties->Obstruction         = %d",
				Properties->eax2.Obstruction);
			api_Log("\t\t[out]Properties->ObstructionLFRatio  = %f",
				Properties->eax2.ObstructionLFRatio);
			api_Log("\t\t[out]Properties->Occlusion           = %d",
				Properties->eax2.Occlusion);
			api_Log("\t\t[out]Properties->OcclusionLFRatio    = %f",
				Properties->eax2.OcclusionLFRatio);
			api_Log("\t\t[out]Properties->OcclusionRoomRatio  = %f",
				Properties->eax2.OcclusionRoomRatio);
			api_Log("\t\t[out]Properties->OutsideVolumeHF     = %d",
				Properties->eax2.OutsideVolumeHF);
			api_Log("\t\t[out]Properties->AirAbsorptionFactor = %f",
				Properties->eax2.AirAbsorptionFactor);
			api_Log("\t\t[out]Properties->Flags               = %d",
				Properties->eax2.Flags);
			break;
			// EAX 3.0
		case 3:
			api_Log("\t\t[out]Properties->Direct               = %d",
				Properties->eax3.Direct);
			api_Log("\t\t[out]Properties->DirectHF             = %d",
				Properties->eax3.DirectHF);
			api_Log("\t\t[out]Properties->Room                 = %d",
				Properties->eax3.Room);
			api_Log("\t\t[out]Properties->RoomHF               = %d",
				Properties->eax3.RoomHF);
			api_Log("\t\t[out]Properties->Obstruction          = %d",
				Properties->eax3.Obstruction);
			api_Log("\t\t[out]Properties->ObstructionLFRatio   = %f",
				Properties->eax3.ObstructionLFRatio);
			api_Log("\t\t[out]Properties->Occlusion            = %d",
				Properties->eax3.Occlusion);
			api_Log("\t\t[out]Properties->OcclusionLFRatio     = %f",
				Properties->eax3.OcclusionLFRatio);
			api_Log("\t\t[out]Properties->OcclusionRoomRatio   = %f",
				Properties->eax3.OcclusionRoomRatio);
			api_Log("\t\t[out]Properties->OcclusionDirectRatio = %f",
				Properties->eax3.OcclusionDirectRatio);
			api_Log("\t\t[out]Properties->Exclusion            = %d",
				Properties->eax3.Exclusion);
			api_Log("\t\t[out]Properties->ExclusionLFRatio     = %f",
				Properties->eax3.ExclusionLFRatio);
			api_Log("\t\t[out]Properties->OutsideVolumeHF      = %d",
				Properties->eax3.OutsideVolumeHF);
			api_Log("\t\t[out]Properties->DopplerFactor        = %f",
				Properties->eax3.DopplerFactor);
			api_Log("\t\t[out]Properties->RolloffFactor        = %f",
				Properties->eax3.RolloffFactor);
			api_Log("\t\t[out]Properties->RoomRolloffFactor    = %f",
				Properties->eax3.RoomRolloffFactor);
			api_Log("\t\t[out]Properties->AirAbsorptionFactor  = %f",
				Properties->eax3.AirAbsorptionFactor);
			api_Log("\t\t[out]Properties->Flags                = %d",
				Properties->eax3.Flags);
			break;
		}
	}
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ����� ZOOMFX ���������� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//  			  Properties  -  ��������� �� ��������� ����������� ���������
//  							 ZOOMFX ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
// ����������  :  ������ ����� �� �������� � ����������� ��������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_ZOOMFX_SetProperties(int ChannelID,
	squall_zoomfx_channel_t* Properties)
#else
DLL_API int SQUALL_Channel_ZOOMFX_SetProperties(int ChannelID,
	squall_zoomfx_channel_t* Properties)
#endif
{
	// ����������
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_ZOOMFX_SetProperties(0x%X, 0x%X)",
		ChannelID,
		Properties);
#endif
	// �������� ����������
	if (IsBadReadPtr(Properties, sizeof(squall_zoomfx_channel_t)))
		Properties = 0;

// ���������� ����������
#if SQUALL_DEBUG
	// ������� ���������
	if (Properties) {
		api_Log("\t\t[in]Properties->Min     = [%f, %f, %f]",
			Properties->Min[0],
			Properties->Min[1],
			Properties->Min[2]);
		api_Log("\t\t[in]Properties->Max     = [%f, %f, %f]",
			Properties->Max[0],
			Properties->Max[1],
			Properties->Max[2]);
		api_Log("\t\t[in]Properties->Front   = [%f, %f, %f]",
			Properties->Front[0],
			Properties->Front[1],
			Properties->Front[2]);
		api_Log("\t\t[in]Properties->Top     = [%f, %f, %f]",
			Properties->Top[0],
			Properties->Top[1],
			Properties->Top[2]);
		api_Log("\t\t[in]Properties->MacroFX = %d", Properties->MacroFX);
	}
#endif

	// �������� ����������
	if (IsTrue(result))
		if (!Properties)
			result = SQUALL_ERROR_INVALID_PARAM;

	// �������� ���������� ������
	if (IsTrue(result))
		if (!context->_zoomfxSupport)
			result = SQUALL_ERROR_NO_ZOOMFX;

	// ����� ����� �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
	}

	// ������� ������
	if (IsTrue(result)) {
		memcpy(&context->_channelsArray[channel].Param.ZOOMFXBP,
			Properties,
			sizeof(squall_zoomfx_channel_t));
		if (!zoomfx_Set(context->_channelsArray[channel].DS_PropSet,
			 	& context->_channelsArray[channel].Param.ZOOMFXBP))
			result = SQUALL_ERROR_SET_ZOOMFX_PARAM;
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ������� ZOOMFX ���������� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//  			  Properties  -  ��������� �� ��������� ���� ����� ���������
//  							 ������� ��������� ZOOMFX ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
// ����������  :  ������ ����� �� �������� � ����������� ��������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Channel_ZOOMFX_GetProperties(int ChannelID,
	squall_zoomfx_channel_t* Properties)
#else
DLL_API int SQUALL_Channel_ZOOMFX_GetProperties(int ChannelID,
	squall_zoomfx_channel_t* Properties)
#endif
{
	// ����������
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Channel_ZOOMFX_GetProperties(0x%X, 0x%X)",
		ChannelID,
		Properties);
#endif

	// �������� ����������
	if (IsTrue(result))
		if (IsBadWritePtr(Properties, sizeof(squall_zoomfx_channel_t)))
			result = SQUALL_ERROR_INVALID_PARAM;

	// �������� ���������� ������
	if (IsTrue(result))
		if (!context->_zoomfxSupport)
			result = SQUALL_ERROR_NO_ZOOMFX;

	// ����� ����� �� ��������������
	if (IsTrue(result)) {
		channel = context->GetChannelIndex(ChannelID);
		if (channel < 0)
			result = SQUALL_ERROR_CHANNEL_NOT_FOUND;
	}

	// ������� ������
	if (IsTrue(result))
		if (!zoomfx_Get(context->_channelsArray[channel].DS_PropSet,
			 	& context->_channelsArray[channel].Param.ZOOMFXBP))
			result = SQUALL_ERROR_GET_ZOOMFX_PARAM;
		else
			memcpy(Properties,
				& context->_channelsArray[channel].Param.ZOOMFXBP,
				sizeof(squall_zoomfx_channel_t));

		// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else {
		api_Log("\t\t[out]Properties->Min     = [%f, %f, %f]",
			Properties->Min[0],
			Properties->Min[1],
			Properties->Min[2]);
		api_Log("\t\t[out]Properties->Max     = [%f, %f, %f]",
			Properties->Max[0],
			Properties->Max[1],
			Properties->Max[2]);
		api_Log("\t\t[out]Properties->Front   = [%f, %f, %f]",
			Properties->Front[0],
			Properties->Front[1],
			Properties->Front[2]);
		api_Log("\t\t[out]Properties->Top     = [%f, %f, %f]",
			Properties->Top[0],
			Properties->Top[1],
			Properties->Top[2]);
		api_Log("\t\t[out]Properties->MacroFX = %d", Properties->MacroFX);
	}
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//  			  ������ ��� ������ � �������� �������
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// ���������/���������� ����� ������ �������
// �� �����    :  ChannelGroupID -  ������������� ������ �������
//  			  Pause 		 -  ���� ���������/���������� �����, ��������
//  								����� ��������� ��������� ��������:
//  								true  -  �������� �����
//  								false -  ��������� �����
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::ChannelGroup_Pause(int GroupID, int Pause)
#else
DLL_API int SQUALL_ChannelGroup_Pause(int GroupID, int Pause)
#endif
{
	// ����������
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_ChannelGroup_Pause(0x%X, %d)", GroupID, Pause);
#endif

	// ��������� ��� ����� ������������� �������� ������
	if (IsTrue(result))
		for (int i = 0; i < context->_channels; i++)
			if (context->_channelsArray[i].GroupID == GroupID)
				if (context->_channelsArray[i].Status.STAGE != EMPTY)
					context->_channelsArray[i].Pause(Pause);

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ������ �������
// �� �����    :  ChannelGroupID -  ������������� ������ �������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::ChannelGroup_Stop(int GroupID)
#else
DLL_API int SQUALL_ChannelGroup_Stop(int GroupID)
#endif
{
	// ����������
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_ChannelGroup_Stop(0x%X)", GroupID);
#endif

	// ��������� ���� ������ ������
	if (IsTrue(result))
		for (int i = 0; i < context->_channels; i++)
			if (context->_channelsArray[i].GroupID == GroupID)
				if (context->_channelsArray[i].Status.STAGE != EMPTY)
					context->_channelsArray[i].Stop();

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ������ ��������� ������ ������� � ���������
// �� �����    :  ChannelGroupID -  ������������� ������ �������
//  			  Volume		 -  �������� ������ ���������, �������� ������
//  								������ � �������� �� 0 �� 100
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::ChannelGroup_SetVolume(int GroupID, int Volume)
#else
DLL_API int SQUALL_ChannelGroup_SetVolume(int GroupID, int Volume)
#endif
{
	// ����������
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_ChannelGroup_SetVolume(0x%X, %d)", GroupID, Volume);
#endif

	// ��������� ��������� ���� ������� ������������� � �������� ������
	if (IsTrue(result))
		for (int i = 0; i < context->_channels; i++)
			if (context->_channelsArray[i].GroupID == GroupID)
				if (context->_channelsArray[i].Status.STAGE != EMPTY)
					context->_channelsArray[i].SetVolume(volume_table[Volume]);

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ����� ������� ������������� ������ �������
// �� �����    :  ChannelGroupID -  ����� ������ �������
//  			  Frequency 	 -  ����� �������� ������� �������������,
//  								�������� ��������� ������ ���� � ��������
//  								�� 100 �� 1000000 ����
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::ChannelGroup_SetFrequency(int GroupID, int Frequency)
#else
DLL_API int SQUALL_ChannelGroup_SetFrequency(int GroupID, int Frequency)
#endif
{
	// ����������
	context_t* context = 0;
	int channel = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_ChannelGroup_SetFrequency(0x%X, %d)",
		GroupID,
		Frequency);
#endif

	// �������� ����������
	if (IsTrue(result))
		if ((Frequency < 100) || (Frequency > 100000))
			result = SQUALL_ERROR_INVALID_PARAM;

	// ��������� ���� ������ ������
	if (IsTrue(result))
		for (int i = 0; i < context->_channels; i++)
			if (context->_channelsArray[i].GroupID == GroupID)
				if (context->_channelsArray[i].Status.STAGE != EMPTY)
					context->_channelsArray[i].SetFrequency(Frequency);

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//  			  ������ ��� ������ � ��������
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// �������� ������ �� �����
// �� �����    :  FileName - ��������� �� ��� �����
//  			  MemFlag  - ���� ������������ ������������ �����, ��������
//  						 ����� ��������� ��������� ��������:
//  						 true  -   ��������� ������ ����� � ������
//  						 false -   ���������� ������ ����� �� �����
//  			  Default  - ��������� �� ��������� ���������� ������ ��
//  						 ���������, ���� �������� ����� 0, ���������
//  						 ��������� ��������� ��������� ������ �� ���������:
//  						 SampleGroupID - 0
//  						 Priority      - 0
//  						 Frequency     - 0
//  						 Volume 	   - 100
//  						 Pan		   - 50
//  						 MinDist	   - 1.0f
//  						 MaxDist	   - 1000000000.0f
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//  			  � ������ ��������� ������ ��������� �������� �������������
//  			  ���������� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Sample_LoadFile(char* FileName, int MemFlag,
	squall_sample_default_t* Default)
#else
DLL_API int SQUALL_Sample_LoadFile(char* FileName, int MemFlag,
	squall_sample_default_t* Default)
#endif
{
	// ����������
	int result = true;

	// �������� ����������
	if (IsBadReadPtr(FileName, sizeof(char)))
		FileName = 0;
	if (IsBadReadPtr(Default, sizeof(squall_sample_default_t)))
		Default = 0;

	// ���������� ����������
#if SQUALL_DEBUG
	if (FileName)
		api_LogTime("SQUALL_Sample_LoadFile(%s, %d, 0x%X)",
			FileName,
			MemFlag,
			Default);
	else
		api_LogTime("SQUALL_Sample_LoadFile(%s, %d, 0x%X)",
			"error FileName",
			MemFlag,
			Default);

	// ��������� �� ���������
	if (Default) {
		api_Log("\t\t[in]Default->SampleGroupID = %d", Default->SampleGroupID);
		api_Log("\t\t[in]Default->Frequency     = %d", Default->Frequency);
		api_Log("\t\t[in]Default->Volume        = %d", Default->Volume);
		api_Log("\t\t[in]Default->Pan           = %d", Default->Pan);
		api_Log("\t\t[in]Default->Priority      = %d", Default->Priority);
		api_Log("\t\t[in]Default->MinDist       = %f", Default->MinDist);
		api_Log("\t\t[in]Default->MaxDist       = %f", Default->MaxDist);
	}
#endif

	// �������� ����������
	if (!FileName)
		result = SQUALL_ERROR_INVALID_PARAM;

	// �������� ���� � ����
	if (IsTrue(result))
		result = api_SampleLoadFile(FileName, MemFlag, Default);

	// �������� ���������� ��������
	if (result <= 0)
		result = SQUALL_ERROR_SAMPLE_BAD;

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else
		api_Log("\t\tresult = 0x%X", result);
#endif

	return result;
}
//-----------------------------------------------------------------------------
// �������� ������ �� ������
// �� �����    :  FileName - ��������� �� ��� �����
//  			  MemFlag  - ���� ������������ ������������ �����, ��������
//  						 ����� ��������� ��������� ��������:
//  						 true  -   ��������� ������ ����� � ������
//  						 false -   ���������� ������ ����� �� �����
//  			  Default  - ��������� �� ��������� ���������� ������ ��
//  						 ���������, ���� �������� ����� 0, ���������
//  						 ��������� ��������� ��������� ������ �� ���������:
//  						 SampleGroupID - 0
//  						 Priority      - 0
//  						 Frequency     - 0
//  						 Volume 	   - 100
//  						 Pan		   - 50
//  						 MinDist	   - 1.0f
//  						 MaxDist	   - 1000000000.0f
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//  			  � ������ ��������� ������ ��������� �������� �������������
//  			  ���������� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Sample_LoadFromMemory(void* Ptr, unsigned int Size,
	int NewMemFlag, squall_sample_default_t* Default)
#else
DLL_API int SQUALL_Sample_LoadFromMemory(void* Ptr, unsigned int Size,
	int NewMemFlag, squall_sample_default_t* Default)
#endif
{
	// ����������
	int result = true;

	// �������� ����������
	if (IsBadReadPtr(Ptr, Size))
		Ptr = 0;
	if (IsBadReadPtr(Default, sizeof(squall_sample_default_t)))
		Default = 0;

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Sample_LoadFromMemory(0x%X, %d, %d, 0x%X)",
		Ptr,
		Size,
		NewMemFlag,
		Default);

	// ��������� �� ���������
	if (Default) {
		api_Log("\t\t[in]Default->SampleGroupID = %d", Default->SampleGroupID);
		api_Log("\t\t[in]Default->Frequency     = %d", Default->Frequency);
		api_Log("\t\t[in]Default->Volume        = %d", Default->Volume);
		api_Log("\t\t[in]Default->Pan           = %d", Default->Pan);
		api_Log("\t\t[in]Default->Priority      = %d", Default->Priority);
		api_Log("\t\t[in]Default->MinDist       = %f", Default->MinDist);
		api_Log("\t\t[in]Default->MaxDist       = %f", Default->MaxDist);
	}
#endif

	// �������� ����������
	if (!Ptr)
		result = SQUALL_ERROR_INVALID_PARAM;

	// �������� ���� � ����
	if (IsTrue(result))
		result = api_CreateSampleFromMemory(Ptr, Size, NewMemFlag, Default);

	// �������� ���������� ��������
	if (result <= 0)
		result = SQUALL_ERROR_SAMPLE_BAD;

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else
		api_Log("\t\tresult = 0x%X", result);
#endif

	return result;
}

//-----------------------------------------------------------------------------
// ������������ ���� �������
// �� �����    :  *
// �� ������   :  *
//-----------------------------------------------------------------------------
#ifndef _USRDLL
void Squall::Sample_UnloadAll(void)
#else
DLL_API void SQUALL_Sample_UnloadAll(void)
#endif
{
	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Sample_UnloadAll()");
#endif

	// �������� ���� ������
	api_SampleUnloadAll();
}

//-----------------------------------------------------------------------------
// ������������ ���������� ������
// �� �����    :  SampleID -  ������������� ������
// �� ������   :  *
//-----------------------------------------------------------------------------
#ifndef _USRDLL
void Squall::Sample_Unload(int SampleID)
#else
DLL_API void SQUALL_Sample_Unload(int SampleID)
#endif
{
	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Sample_Unload(0x%X)", SampleID);
#endif

	// �������� ������
	api_SampleUnload(SampleID);
}

//-----------------------------------------------------------------------------
// ��������� ����������������� ������ ��������� ����� � ��������
// �� �����    :  SampleID -  ������������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//  			  � ������ ��������� ������ ��������� �������� �����������������
//  			  ������ � ��������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Sample_GetFileLength(int SampleID)
#else
DLL_API int SQUALL_Sample_GetFileLength(int SampleID)
#endif
{
	CSoundFile* file = 0;
	int result = true;

#if SQUALL_DEBUG
	api_LogTime("SQUALL_Sample_GetFileLength(0x%X)", SampleID);
#endif

	// ��������� ��������� �� �����
	if (IsTrue(result)) {
		file = api_SampleGetFile(SampleID);
		if (!file)
			result = SQUALL_ERROR_INVALID_PARAM;
	}

	// ������� ���������� ������� � �����
	if (IsTrue(result)) {
		result = file->GetSamplesInFile();
		if (!result)
			result = SQUALL_ERROR_SAMPLE_BAD;
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else
		api_Log("\t\tresult = %d", result);
#endif

	// ������ ��������� ������
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ����������������� ������ ��������� ����� � �������������
// �� �����    :  SampleID -  ������������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//  			  � ������ ��������� ������ ��������� �������� �����������������
//  			  ������ � ������������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Sample_GetFileLengthMs(int SampleID)
#else
DLL_API int SQUALL_Sample_GetFileLengthMs(int SampleID)
#endif
{
	CSoundFile* file = 0;
	int result = true;

#if SQUALL_DEBUG
	api_LogTime("SQUALL_Sample_GetFileLengthMs(0x%X)", SampleID);
#endif

	// ��������� ��������� �� �����
	if (IsTrue(result)) {
		file = api_SampleGetFile(SampleID);
		if (!file)
			result = SQUALL_ERROR_INVALID_PARAM;
	}

	// ������� ���������� ������� � �����
	if (IsTrue(result)) {
		result = file->GetSamplesInFile();
		if (!result)
			result = SQUALL_ERROR_SAMPLE_BAD;
		else
			result = (int)
				((__int64) (result * (__int64) 1000) /
				(__int64) file->GetFormat()->nSamplesPerSec);
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else
		api_Log("\t\tresult = %d", result);
#endif

	// ������ ��������� ������
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ������� ������������� ������ ��������� �����
// �� �����    :  SampleID -  ������������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//  			  � ������ ��������� ������ ��������� �������� �������
//  			  �������������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Sample_GetFileFrequency(int SampleID)
#else
DLL_API int SQUALL_Sample_GetFileFrequency(int SampleID)
#endif
{
	CSoundFile* file = 0;
	int result = true;

#if SQUALL_DEBUG
	api_LogTime("SQUALL_Sample_GetFileFrequency(0x%X)", SampleID);
#endif

	// ��������� ��������� �� �����
	if (IsTrue(result)) {
		file = api_SampleGetFile(SampleID);
		if (!file)
			result = SQUALL_ERROR_INVALID_PARAM;
	}

	// ������� ���������� ������� � �����
	if (IsTrue(result)) {
		result = file->GetFormat()->nSamplesPerSec;
		if (!result)
			result = SQUALL_ERROR_SAMPLE_BAD;
	}

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else
		api_Log("\t\tresult = %d", result);
#endif

	// ������ ��������� ������
	return result;
}
//-----------------------------------------------------------------------------
// ��������� ����� ���������� ������ �� ���������
// �� �����    :  SampleID -  ������������� ������
//  			  Default  -  ��������� �� ��������� � ������ ����������� ������
//  						  �� ���������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Sample_SetDefault(int SampleID, squall_sample_default_t* Default)
#else
DLL_API int SQUALL_Sample_SetDefault(int SampleID,
	squall_sample_default_t* Default)
#endif
{
	int result = true;

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Sample_SetDefault(0x%X, 0x%X)", SampleID, Default);
#endif

	// �������� ����������
	if (IsBadWritePtr(Default, sizeof(squall_sample_default_t)))
		Default = 0;

	// ���������� ����������
#if SQUALL_DEBUG
	if (Default) {
		api_Log("\t\t[in]Default->SampleGroupID = %d", Default->SampleGroupID);
		api_Log("\t\t[in]Default->Frequency     = %d", Default->Frequency);
		api_Log("\t\t[in]Default->Volume        = %d", Default->Volume);
		api_Log("\t\t[in]Default->Pan           = %d", Default->Pan);
		api_Log("\t\t[in]Default->Priority      = %d", Default->Priority);
		api_Log("\t\t[in]Default->MinDist       = %f", Default->MinDist);
		api_Log("\t\t[in]Default->MaxDist       = %f", Default->MaxDist);
	}
#endif

	// �������� ����������
	if (!Default)
		result = SQUALL_ERROR_INVALID_PARAM;

	// ��������� ����������
	if (IsTrue(result))
		if (!api_SampleSetDefault(SampleID, Default))
			result = SQUALL_ERROR_INVALID_PARAM;

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������ ��������� ������
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ������� ���������� ������ �� ���������
// �� �����    :  SampleID -  ������������� ������
//  			  Default  -  ��������� �� ��������� � ������� ����� ���������
//  						  ������� ��������� ������ �� ���������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Sample_GetDefault(int SampleID, squall_sample_default_t* Default)
#else
DLL_API int SQUALL_Sample_GetDefault(int SampleID,
	squall_sample_default_t* Default)
#endif
{
	// ����������
	int result = true;

#if SQUALL_DEBUG
	api_LogTime("SQUALL_Sample_GetDefault(0x%X, 0x%X)", SampleID, Default);
#endif

	// �������� ����������
	if (IsBadWritePtr(Default, sizeof(squall_sample_default_t)))
		result = SQUALL_ERROR_INVALID_PARAM;

	// ��������� ����������
	if (IsTrue(result))
		if (!api_SampleGetDefault(SampleID, Default))
			result = SQUALL_ERROR_INVALID_PARAM;

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else {
		api_Log("\t\t[out]Default->SampleGroupID = %d", Default->SampleGroupID);
		api_Log("\t\t[out]Default->Frequency     = %d", Default->Frequency);
		api_Log("\t\t[out]Default->Volume        = %d", Default->Volume);
		api_Log("\t\t[out]Default->Pan           = %d", Default->Pan);
		api_Log("\t\t[out]Default->Priority      = %d", Default->Priority);
		api_Log("\t\t[out]Default->MinDist       = %f", Default->MinDist);
		api_Log("\t\t[out]Default->MaxDist       = %f", Default->MaxDist);
	}
#endif

	// ������ ���������  
	return result;
}
//-----------------------------------------------------------------------------
// ��������� ��������������� ���������� �����
// �� ����� :  SampleID  - ������������� ����������� �����
//  		   Loop  - ���� ������������ ���������������
//  				   true   - �������������� ���� � ����� ����������
//  				   false  - ������������� ���� ���� ���
//  		   Group - �������������� ������������ ������ � ������
//  		   Start - ���� ������� ����� �� ��������� �������� ������
//  				   true   - ����� ������ ������������� ����� ��
//  				   false  - ����� ����� ������ �����������, ��� ����
//  						 ����� ������ ��������������� �����
//  						 ������� ����� CHANNEL_Start()
// �� ������   :  ������������� ��������� ������, ���� �������� �������� �����
//  		   0, ������ ��������� ������, ����� ������ ����� ������
//  		   ������ ����� SYSTEM_GetError()
// ����������  :  1. ��������� ��������� ��� ���������, ��������, �������,
//  		   ��������� ������� �� ���������� ����� �� ���������
//  		   2. ��������������� ������������� � ��������������� ����� � 
//  		   ������ �����. �� ���� ����� ������������ ������� ������
//  		   ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Sample_Play(int SampleID, int Loop, int ChannelGroupID, int Start)
#else
DLL_API int SQUALL_Sample_Play(int SampleID, int Loop, int ChannelGroupID,
	int Start)
#endif
{
	// ����������
	squall_sample_default_t def;
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Sample_Play(0x%X, %d, %d, %d)",
		SampleID,
		Loop,
		ChannelGroupID,
		Start);
#endif

	// ��������� ���������� ����� �� ���������
	if (IsTrue(result))
		if (!api_SampleGetDefault(SampleID, & def))
			result = SQUALL_ERROR_SAMPLE_BAD;

	// �������� ������
	result = CreateChannel(context,
			 	SampleID,
			 	Loop,
			 	ChannelGroupID,
			 	Start,
			 	def.Priority,
			 	def.Volume,
			 	def.Frequency,
			 	def.Pan);

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else
		api_Log("\t\tresult = 0x%X", result);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ��������������� ���������� �����, ����������� ������
// �� ����� :  SampleID 	- ������������� ����������� �����
//  		   Loop 	- ���� ������������ ���������������
//  					  true   - �������������� ���� � ����� ����������
//  					  false  - ������������� ���� ���� ���
//  		   Group	- �������������� ������������ ������ � ������
//  		   Start	- ���� ������� ����� �� ��������� �������� ������
//  					  true   - ����� ������ ������������� ����� ��
//  					  false  - ����� ����� ������ �����������, ��� ����
//  							����� ������ ��������������� �����
//  							������� ����� CHANNEL_Start()
//  		   Priority - ��������� ������������ ��������� ������,
//  					  �������� ������ ������ � �������� �� 0 �� 255
//  		   Volume      - ��������� ������������ ��������� ������,
//  					  �������� ������ ������ � �������� �� 0 �� 100
//  		   Frequency   - ������� ������������ ��������� ������
//  					  �������� ������ ������ � �������� �� 100 �� 100000
//  		   Pan  	   - �������� ������������ ��������� ������
//  					  �������� ������ ������ � �������� �� 0 �� 100
// �� ������   :  ������������� ��������� ������, ���� �������� �������� �����
//  		   0, ������ ��������� ������, ����� ������ ����� ������
//  		   ������ ����� SYSTEM_GetError()
// ����������  :  1. ��������������� ������������� � ��������������� ����� � 
//  		   ������ �����. �� ���� ����� ������������ ������� ������
//  		   ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Sample_PlayEx(int SampleID, int Loop, int ChannelGroupID,
	int Start, int Priority, int Volume, int Frequency, int Pan)
#else
DLL_API int SQUALL_Sample_PlayEx(int SampleID, int Loop, int ChannelGroupID,
	int Start, int Priority, int Volume, int Frequency, int Pan)
#endif
{
	// ����������
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Sample_PlayEx(0x%X, %d, %d, %d, %d, %d, %d, %d)",
		SampleID,
		Loop,
		ChannelGroupID,
		Start,
		Priority,
		Volume,
		Frequency,
		Pan);
#endif

	// �������� ������
	result = CreateChannel(context,
			 	SampleID,
			 	Loop,
			 	ChannelGroupID,
			 	Start,
			 	Priority,
			 	Volume,
			 	Frequency,
			 	Pan);

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\tresult = %s", ErrorTable[-result]);
	else
		api_Log("\t\tresult = 0x%X", result);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ��������������� ��������� �����
// �� ����� :  SampleID 	- ������������� ����������� �����
//  		   Loop 	- ���� ������������ ���������������
//  					  true   - �������������� ���� � ����� ����������
//  					  false  - ������������� ���� ���� ���
//  		   Group	- �������������� ������������ ������ � ������
//  		   Start	- ���� ������� ����� �� ��������� �������� ������
//  					  true   - ����� ������ ������������� ����� ��
//  					  false  - ����� ����� ������ �����������, ��� ����
//  							����� ������ ��������������� �����
//  							������� ����� CHANNEL_Start()
//  		   Position - ��������� �� ��������� ��������� ���������
//  					  ���������
//  		   Velocity - ��������� �� ������ �������� ��������� �����,
//  					  ���� �������� �������� �� �����, �� ������
//  					  �������� ����� ���� ����� 0
// �� ������   :  ������������� ��������� ������, ���� �������� �������� �����
//  		   0, ������ ��������� ������, ����� ������ ����� ������
//  		   ������ ����� SYSTEM_GetError()
// ����������  :  1. ��������� ��������� ��� ���������, �������, ���������,
//  		   ����������� � ������������ ��������� ����������, �������
//  		   �� ���������� ����� �� ���������
//  		   2. ��������������� ������������� � ��������������� ����� � 
//  		   ���� �����. �� ���� ����� ������������ ������� ���� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Sample_Play3D(int SampleID, int Loop, int ChannelGroupID,
	int Start, float* Position, float* Velocity)
#else
DLL_API int SQUALL_Sample_Play3D(int SampleID, int Loop, int ChannelGroupID,
	int Start, float* Position, float* Velocity)
#endif
{
	// ����������
	squall_sample_default_t def;
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Sample_Play3D(0x%X, %d, %d, %d, 0x%X, 0x%X)",
		SampleID,
		Loop,
		ChannelGroupID,
		Start,
		Position,
		Velocity);
#endif

	// �������� ����������
	if (IsBadReadPtr(Position, sizeof(float) * 3))
		Position = 0;
	if (IsBadReadPtr(Velocity, sizeof(float) * 3))
		Velocity = 0;

	// ���������� ����������
#if SQUALL_DEBUG
	// ������� �����
	if (Position) {
		api_Log("\t\t[in]Position->x = %f", Position[0]);
		api_Log("\t\t[in]Position->y = %f", Position[1]);
		api_Log("\t\t[in]Position->z = %f", Position[2]);
	}
	// �������� �����
	if (Velocity) {
		api_Log("\t\t[in]Velocity->x = %f", Velocity[0]);
		api_Log("\t\t[in]Velocity->y = %f", Velocity[1]);
		api_Log("\t\t[in]Velocity->z = %f", Velocity[2]);
	}
#endif

	// �������� ����������
	if (IsTrue(result))
		if (!Position)
			result = SQUALL_ERROR_INVALID_PARAM;

	// ��������� ���������� ����� �� ���������
	if (IsTrue(result))
		if (!api_SampleGetDefault(SampleID, & def))
			result = SQUALL_ERROR_SAMPLE_BAD;

	// �������� ������
	result = CreateChannel3D(context,
			 	SampleID,
			 	Loop,
			 	ChannelGroupID,
			 	Start,
			 	Position,
			 	Velocity,
			 	def.Priority,
			 	def.Volume,
			 	def.Frequency,
			 	def.MinDist,
			 	def.MaxDist);

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else
		api_Log("\t\tresult = 0x%X", result);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ��������������� ��������� �����, ����������� ������
// �� ����� :  SampleID 	- ������������� ����������� �����
//  		   Loop 	- ���� ������������ ���������������
//  					  true   - �������������� ���� � ����� ����������
//  					  false  - ������������� ���� ���� ���
//  		   Group	- �������������� ������������ ������ � ������
//  		   Start	- ���� ������� ����� �� ��������� �������� ������
//  					  true   - ����� ������ ������������� ����� ��
//  					  false  - ����� ����� ������ �����������, ��� ����
//  							����� ������ ��������������� �����
//  							������� ����� CHANNEL_Start()
//  		   Position - ��������� �� ��������� ��������� ���������
//  					  ���������
//  		   Velocity - ��������� �� ������ �������� ��������� �����,
//  					  ���� �������� �������� �� �����, �� ������
//  					  �������� ����� ���� ����� 0
//  		   Priority - ��������� ������������ ��������� ������,
//  					  �������� ������ ������ � �������� �� 0 �� 255
//  		   Volume      - ��������� ������������ ��������� ������,
//  					  �������� ������ ������ � �������� �� 0 �� 100
//  		   Frequency   - ������� ������������ ��������� ������
//  					  �������� ������ ������ � �������� �� 100 �� 100000
//  		   MinDist     - ����������� ��������� ����������
//  		   MaxDist     - ������������ ��������� ����������
// �� ������   :  ������������� ��������� ������, ���� �������� �������� �����
//  		   0, ������ ��������� ������, ����� ������ ����� ������
//  		   ������ ����� SYSTEM_GetError()
// ����������  :  1. ��������������� ������������� � ��������������� ����� � 
//  		   ���� �����. �� ���� ����� ������������ ������� ���� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Sample_Play3DEx(int SampleID, int Loop, int ChannelGroupID,
	int Start, float* Position, float* Velocity, int Priority, int Volume,
	int Frequency, float MinDist, float MaxDist)
#else
DLL_API int SQUALL_Sample_Play3DEx(int SampleID, int Loop, int ChannelGroupID,
	int Start, float* Position, float* Velocity, int Priority, int Volume,
	int Frequency, float MinDist, float MaxDist)
#endif
{
	// ����������
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Sample_Play3DEx(0x%X, %d, %d, %d, 0x%X, 0x%X, %d, %d, %d, %f, %f)",
		SampleID,
		Loop,
		ChannelGroupID,
		Start,
		Position,
		Velocity,
		Priority,
		Volume,
		Frequency,
		MinDist,
		MaxDist);
#endif

	// �������� ����������
	if (IsBadReadPtr(Position, sizeof(float) * 3))
		Position = 0;
	if (IsBadReadPtr(Velocity, sizeof(float) * 3))
		Velocity = 0;

	// ���������� ����������
#if SQUALL_DEBUG
	// ������� �����
	if (Position) {
		api_Log("\t\t[in]Position->x = %f", Position[0]);
		api_Log("\t\t[in]Position->y = %f", Position[1]);
		api_Log("\t\t[in]Position->z = %f", Position[2]);
	}
	// �������� �����
	if (Velocity) {
		api_Log("\t\t[in]Velocity->x = %f", Velocity[0]);
		api_Log("\t\t[in]Velocity->y = %f", Velocity[1]);
		api_Log("\t\t[in]Velocity->z = %f", Velocity[2]);
	}
#endif

	// �������� ����������
	if (IsTrue(result))
		if (!Position)
			result = SQUALL_ERROR_INVALID_PARAM;

	// �������� ������
	result = CreateChannel3D(context,
			 	SampleID,
			 	Loop,
			 	ChannelGroupID,
			 	Start,
			 	Position,
			 	Velocity,
			 	Priority,
			 	Volume,
			 	Frequency,
			 	MinDist,
			 	MaxDist);

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else
		api_Log("\t\tresult = 0x%X", result);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ���������/���������� ����� ���� ������� ������������ �������� �����
// �� �����    :  SampleID -  ��������� �� ������ �����
//  			  Pause    -  ���� ���������/���������� �����, �������� �����
//  						  ��������� ��������� ��������:
//  						  true   - �������� �����
//  						  false  - ��������� �����
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Sample_Pause(int SampleID, int Pause)
#else
DLL_API int SQUALL_Sample_Pause(int SampleID, int Pause)
#endif
{
	// ����������
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Sample_Pause(0x%X, %d)", SampleID, Pause);
#endif

	if (IsTrue(result))
		for (int i = 0; i < context->_channels; i++)
			if (context->_channelsArray[i].Status.STAGE != EMPTY)
				if (context->_channelsArray[i].SampleID == SampleID)
					context->_channelsArray[i].Pause(Pause);

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ���� �������� ������� ������������ ��������� �����
// �� �����    :  SampleID -  ������������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::Sample_Stop(int SampleID)
#else
DLL_API int SQUALL_Sample_Stop(int SampleID)
#endif
{
	// ����������
	context_t* context = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_Sample_Stop(0x%X)", SampleID);
#endif

	if (IsTrue(result))
		for (int i = 0; i < context->_channels; i++)
			if (context->_channelsArray[i].Status.STAGE != EMPTY)
				if (context->_channelsArray[i].SampleID == SampleID)
					context->_channelsArray[i].Stop();

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//  			  ������ ��� ������ � �������� �������
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// ��������� ��������������� ���������� ����� �� ������
// �� ����� :  SoundGroupID   - ������������� ���������� ������
//  		   Loop 	   - ���� ������������ ���������������
//  						 true   - �������������� ���� � ����� ����������
//  						 false  - ������������� ���� ���� ���
//  		   Group	   - �������������� ������������ ������ � ������
//  		   Start	   - ���� ������� ����� �� ��������� �������� ������
//  						 true   - ����� ������ ������������� ����� ��
//  						 false  - ����� ����� ������ �����������, ��� ����
//  							   ����� ������ ��������������� �����
//  							   ������� ����� CHANNEL_Start()
// �� ������   :  ������������� ��������� ������, ���� �������� �������� �����
//  		   0, ������ ��������� ������, ����� ������ ����� ������
//  		   ������ ����� SYSTEM_GetError()
// ����������  :  1. ��������� ��������� ��� ���������, ��������, �������,
//  		   ��������� ������� �� ���������� ����� �� ���������
//  		   2. ��������������� ������������� � ��������������� ����� � 
//  		   ������ �����. �� ���� ����� ������������ ������� ������
//  		   ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::SampleGroup_Play(int SampleGroupID, int Loop, int ChannelGroupID,
	int Start)
#else
DLL_API int SQUALL_SampleGroup_Play(int SampleGroupID, int Loop,
	int ChannelGroupID, int Start)
#endif
{
	// ����������
	squall_sample_default_t def;
	context_t* context = 0;
	int SampleID = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_SampleGroup_Play(0x%X, %d, %d, %d)",
		SampleGroupID,
		Loop,
		ChannelGroupID,
		Start);
#endif

	// ������� ��������� �� ������
	if (IsTrue(result)) {
		SampleID = api_SampleGetFileGroup(SampleGroupID, 0);
		if (SampleID == 0)
			result = SQUALL_ERROR_SAMPLE_BAD;
	}

	// ��������� ���������� ����� �� ���������
	if (IsTrue(result))
		if (!api_SampleGetDefault(SampleID, & def))
			result = SQUALL_ERROR_SAMPLE_BAD;

	// �������� ������
	result = CreateChannel(context,
			 	SampleID,
			 	Loop,
			 	ChannelGroupID,
			 	Start,
			 	def.Priority,
			 	def.Volume,
			 	def.Frequency,
			 	def.Pan);

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else
		api_Log("\t\tresult = 0x%X", result);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ��������������� ���������� ����� �� ������, ����������� ������
// �� ����� :  SoundGroupID   - ������������� ���������� ������
//  		   Loop 	   - ���� ������������ ���������������
//  						 true   - �������������� ���� � ����� ����������
//  						 false  - ������������� ���� ���� ���
//  		   Group	   - �������������� � ������
//  		   Start	   - ���� ������� ����� �� ��������� �������� ������
//  						 true   - ����� ������ ������������� ����� ��
//  						 false  - ����� ����� ������ �����������, ��� ����
//  							   ����� ������ ��������������� �����
//  							   ������� ����� CHANNEL_Start()
//  		   Priority    - ��������� ������������ ��������� ������,
//  						 �������� ������ ������ � �������� �� 0 �� 255
//  		   Volume   	  - ��������� ������������ ��������� ������,
//  						 �������� ������ ������ � �������� �� 0 �� 100
//  		   Frequency	  - ������� ������������ ��������� ������
//  						 �������� ������ ������ � �������� �� 100 �� 100000
//  		   Pan  		  - �������� ������������ ��������� ������
//  						 �������� ������ ������ � �������� �� 0 �� 100
// �� ������   :  ������������� ��������� ������, ���� �������� �������� �����
//  		   0, ������ ��������� ������, ����� ������ ����� ������
//  		   ������ ����� SYSTEM_GetError()
// ����������  :  1. ��������������� ������������� � ��������������� ����� �
//  		   ������ �����. �� ���� ����� ������������ ������� ������
//  		   ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::SampleGroup_PlayEx(int SampleGroupID, int Loop,
	int ChannelGroupID, int Start, int Priority, int Volume, int Frequency,
	int Pan)
#else
DLL_API int SQUALL_SampleGroup_PlayEx(int SampleGroupID, int Loop,
	int ChannelGroupID, int Start, int Priority, int Volume, int Frequency,
	int Pan)
#endif
{
	// ����������
	context_t* context = 0;
	int SampleID = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_SampleGroup_PlayEx(0x%X, %d, %d, %d, %d, %d, %d, %d)",
		SampleGroupID,
		Loop,
		ChannelGroupID,
		Priority,
		Start,
		Volume,
		Frequency,
		Pan);
#endif

	// ������� ��������� �� ������
	if (IsTrue(result)) {
		SampleID = api_SampleGetFileGroup(SampleGroupID, 0);
		if (SampleID == 0)
			result = SQUALL_ERROR_SAMPLE_BAD;
	}

	// �������� ������
	result = CreateChannel(context,
			 	SampleID,
			 	Loop,
			 	ChannelGroupID,
			 	Start,
			 	Priority,
			 	Volume,
			 	Frequency,
			 	Pan);

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else
		api_Log("\t\tresult = 0x%X", result);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// ��������� ��������������� ��������� ����� �� ������
// �� ����� :  SoundGroupID   - ������������� ����������� �����
//  		   Loop 	   - ���� ������������ ���������������
//  						 true   - �������������� ���� � ����� ����������
//  						 false  - ������������� ���� ���� ���
//  		   Group	   - �������������� ������������ ������ � ������
//  		   Start	   - ���� ������� ����� �� ��������� �������� ������
//  						 true   - ����� ������ ������������� ����� ��
//  						 false  - ����� ����� ������ �����������, ��� ����
//  							   ����� ������ ��������������� �����
//  							   ������� ����� CHANNEL_Start()
//  		   Position    - ��������� �� ��������� ��������� ���������
//  						 ���������
//  		   Velocity    - ��������� �� ������ �������� ��������� �����,
//  						 ���� �������� �������� �� �����, �� ������
//  						 �������� ����� ���� ����� 0
// �� ������   :  ������������� ��������� ������, ���� �������� �������� �����
//  		   0, ������ ��������� ������, ����� ������ ����� ������
//  		   ������ ����� SYSTEM_GetError()
// ����������  :  1. ��������� ��������� ��� ���������, �������, ���������,
//  		   ����������� � ������������ ��������� ����������, �������
//  		   �� ���������� ����� �� ���������
//  		   2. ��������������� ������������� � ��������������� ����� � 
//  		   ���� �����. �� ���� ����� ������������ ������� ���� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::SampleGroup_Play3D(int SampleGroupID, int Loop,
	int ChannelGroupID, int Start, float* Position, float* Velocity)
#else
DLL_API int SQUALL_SampleGroup_Play3D(int SampleGroupID, int Loop,
	int ChannelGroupID, int Start, float* Position, float* Velocity)
#endif
{
	// ����������
	squall_sample_default_t def;
	context_t* context = 0;
	int SampleID = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_SampleGroup_Play3D(0x%X, %d, %d, %d, 0x%X, 0x%X)",
		SampleGroupID,
		Loop,
		ChannelGroupID,
		Start,
		Position,
		Velocity);
#endif

	// �������� ����������
	if (IsBadReadPtr(Position, sizeof(float) * 3))
		Position = 0;
	if (IsBadReadPtr(Velocity, sizeof(float) * 3))
		Velocity = 0;

	// ���������� ����������
#if SQUALL_DEBUG
	// ������� �����
	if (Position) {
		api_Log("\t\t[in]Position->x = %f", Position[0]);
		api_Log("\t\t[in]Position->y = %f", Position[1]);
		api_Log("\t\t[in]Position->z = %f", Position[2]);
	}
	// �������� �����
	if (Velocity) {
		api_Log("\t\t[in]Velocity->x = %f", Velocity[0]);
		api_Log("\t\t[in]Velocity->y = %f", Velocity[1]);
		api_Log("\t\t[in]Velocity->z = %f", Velocity[2]);
	}
#endif

	// �������� ����������
	if (IsTrue(result))
		if (!Position)
			result = SQUALL_ERROR_INVALID_PARAM;

	// ������� ��������� �� ������
	if (IsTrue(result)) {
		SampleID = api_SampleGetFileGroup(SampleGroupID, 0);
		if (SampleID == 0)
			result = SQUALL_ERROR_SAMPLE_BAD;
	}

	// ��������� ���������� ����� �� ���������
	if (IsTrue(result))
		if (!api_SampleGetDefault(SampleID, & def))
			result = SQUALL_ERROR_SAMPLE_BAD;

	// �������� ������
	result = CreateChannel3D(context,
			 	SampleID,
			 	Loop,
			 	ChannelGroupID,
			 	Start,
			 	Position,
			 	Velocity,
			 	def.Priority,
			 	def.Volume,
			 	def.Frequency,
			 	def.MinDist,
			 	def.MaxDist);

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else
		api_Log("\t\tresult = 0x%X", result);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}

//-----------------------------------------------------------------------------
// �������� � ��������������� ������������ (�����������) ��������� ������ ��
// �������� ������ �������
// �� �����    :  SampleGroupID  -  ������������� ������ �������
//  			  Loop  		 -  ���� ������������� ���������������, ��������
//  								����� ��������� ��������� ��������:
//  								true  -  �������������� ����� � �����
//  										 ����������
//  								false -  ������������� ����� ���� ���
//  			  ChannelGroupID -  �������������� ������������ ������ � ������
//  								�������, ���� �������� ��������� ����� 0
//  								������ �������� ����� �� ����������� ������
//  								�������.
//  			  Start 		 -  ���� ������� ����� �� ��������� ��������
//  								������, �������� ����� ��������� ���������
//  								��������:
//  								true  -  ����� ������ ��������������� �����
//  										 ����� ��������
//  								false -  ����� ����� ������ �����������,
//  										 ��� ���� ����� ������ ���������������
#ifndef _USRDLL
//  										 ����� ������� ����� Channel_Start()
#else
//  										 ����� ������� �����
//  										 SQUALL_Channel_Start()
#endif
//  			  Position  	 -  ��������� �� ��������� c ������������
//  								��������� ��������� ������
//  			  Velocity  	 -  ��������� �� ������ �������� ���������
//  								��������� ������, � ������ ���� ��������
//  								������� �������� ������������� �� ����,
//  								�� ������ �������� ������ ���� ����� 0
//  			  Priority  	 -  ��������� ������������ ��������� ������,
//  								�������� ��������� ������ ������ � ��������
//  								�� 0 �� 65535
//  			  Volume		 -  ��������� ������������ ��������� ������,
//  								� ���������, �������� ��������� ������
//  								������ � �������� �� 0 �� 100
//  			  Frequency 	 -  ������� ������������� ��������� ������,
//  								�������� ��������� ������ ������ � ��������
//  								�� 100 �� 1000000000
//  			  MinDist   	 -  ����������� ��������� ���������� ���������
//  								������, �������� ��������� ������ ���� �
//  								�������� �� 0.01f �� 1000000000.0f
//  			  MaxDist   	 -  ������������ ��������� ���������� ���������
//  								������, �������� ��������� ������ ���� �
//  								�������� �� 0.01f �� 1000000000.0f
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//  			  ����� ���������, ����� ��������� �������� ��� ������
//  			  � ������ ��������� ������ ��������� �������� �������������
//  			  ���������� ��������� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Squall::SampleGroup_Play3DEx(int SampleGroupID, int Loop,
	int ChannelGroupID, int Start, float* Position, float* Velocity,
	int Priority, int Volume, int Frequency, float MinDist, float MaxDist)
#else
DLL_API int SQUALL_SampleGroup_Play3DEx(int SampleGroupID, int Loop,
	int ChannelGroupID, int Start, float* Position, float* Velocity,
	int Priority, int Volume, int Frequency, float MinDist, float MaxDist)
#endif
{
	// ����������
	context_t* context = 0;
	int SampleID = 0;
	int result = true;

	// �������� ������� ����� � �������
	if (api_GetNumDevice() == 0)
		result = SQUALL_ERROR_NO_SOUND;

#ifndef _USRDLL
	// ��������� ���������
	if (IsTrue(result)) {
		context = api_GetContext(this);
		if (!context)
			result = SQUALL_ERROR_UNINITIALIZED;
	}
#else
	context = &api._context;
#endif

	// ������������ ���������
	LockContext(context);

	// ���������� ����������
#if SQUALL_DEBUG
	api_LogTime("SQUALL_SampleGroup_Play3DEx(0x%X, %d, %d, %d, 0x%X, 0x%X, %d, %d, %d, %f, %f)",
		SampleGroupID,
		Loop,
		ChannelGroupID,
		Start,
		Position,
		Velocity,
		Priority,
		Volume,
		Frequency,
		MinDist,
		MaxDist);
#endif

	// �������� ����������
	if (IsBadReadPtr(Position, sizeof(float) * 3))
		Position = 0;
	if (IsBadReadPtr(Velocity, sizeof(float) * 3))
		Velocity = 0;

	// ���������� ����������
#if SQUALL_DEBUG
	// ������� �����
	if (Position) {
		api_Log("\t\t[in]Position->x = %f", Position[0]);
		api_Log("\t\t[in]Position->y = %f", Position[1]);
		api_Log("\t\t[in]Position->z = %f", Position[2]);
	}
	// �������� �����
	if (Velocity) {
		api_Log("\t\t[in]Velocity->x = %f", Velocity[0]);
		api_Log("\t\t[in]Velocity->y = %f", Velocity[1]);
		api_Log("\t\t[in]Velocity->z = %f", Velocity[2]);
	}
#endif

	// �������� ����������
	if (IsTrue(result))
		if (!Position)
			result = SQUALL_ERROR_INVALID_PARAM;

	// ������� ��������� �� ������
	if (IsTrue(result)) {
		SampleID = api_SampleGetFileGroup(SampleGroupID, 0);
		if (SampleID == 0)
			result = SQUALL_ERROR_SAMPLE_BAD;
	}

	// �������� ������
	result = CreateChannel3D(context,
			 	SampleID,
			 	Loop,
			 	ChannelGroupID,
			 	Start,
			 	Position,
			 	Velocity,
			 	Priority,
			 	Volume,
			 	Frequency,
			 	MinDist,
			 	MaxDist);

	// ���������� ����������
#if SQUALL_DEBUG
	if (IsFalse(result))
		api_Log("\t\terror = %s", ErrorTable[-result]);
	else
		api_Log("\t\tresult = 0x%X", result);
#endif

	// ������������ ��������
	UnlockContext(context);
	return result;
}
