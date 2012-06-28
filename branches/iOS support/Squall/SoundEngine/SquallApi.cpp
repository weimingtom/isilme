//-----------------------------------------------------------------------------
// ���� ��������� ��������� "�����"
// �������     : AntiTank
// ����������� : ������������ ����� (�����)
//-----------------------------------------------------------------------------
// ���������
#include <stdio.h>
#include "ZoomFX.h"
#include "SquallApi.h"
#include "DirectSound.h"
#include "HiddenWindow.h"
#include "Context.h"

/////////////////////////////////////////////////
// �������
/////////////////////////////////////////////////
#define DEVICE_GROWBY      4
#define CONTEXT_GROWBY     8
#define SAMPLE_GROWBY      128
#define SAMPLES_IN_GROUP   256

/////////////////////////////////////////////////
// ���������� ����������
/////////////////////////////////////////////////
int api_init = 0;   		   // ���� ������������� ����
squall_api_t api;   					// ���� ������
int api_temp[256];  		   // ������������� ����� ��� ������ ������ ������

//-----------------------------------------------------------------------------
// ������� �����
// �� �����    :  filename - ��������� �� ��� �����
// �� ������   :  ������� �����, ���� �������� ���� -1 ������ ��������� ������
//-----------------------------------------------------------------------------
unsigned int api_open(const char* filename)
{
	return (unsigned int) CreateFile(filename,
						  	GENERIC_READ,
						  	FILE_SHARE_READ,
						  	NULL,
						  	OPEN_EXISTING,
						  	0,
						  	NULL);
}

//-----------------------------------------------------------------------------
// ������ ������ �� �����
// �� �����    :  handler  -  ������� �����
//  			  buffer   -  ��������� �� ����� � ������� ����� ������ ������
//  			  size     -  ���������� �������� ������
// �� ������   :  ���������� ����������� ������
//-----------------------------------------------------------------------------
int api_read(unsigned int handler, void* buffer, int size)
{
	unsigned long read;
	ReadFile((void *) handler, buffer, size, & read, 0);
	return read;
}

//-----------------------------------------------------------------------------
// ���������������� � �����
// �� �����    :  handler  -  ������� �����
//  			  position -  ����� ������� � �����
//  			  mode     -  ����� ����������������
// �� ������   :  ����� ������� � �����
//-----------------------------------------------------------------------------
int api_seek(unsigned int handler, int position, int mode)
{
	return SetFilePointer((void *) handler, position, 0, mode);
}

//-----------------------------------------------------------------------------
// ������� ��������� �����
// �� �����    :  handler  -  ������� �����
// �� ������   :  *
//-----------------------------------------------------------------------------
void api_close(unsigned int handler)
{
	CloseHandle((void *) handler);
}

//-----------------------------------------------------------------------------
// ��������� ������
// �� �����    :  size  - ���������� ���������� ������
// �� ������   :  ��������� �� ���������� ������, ���� �������� ����� 0 ������
//  			  ��������� ������ �� ����������
//-----------------------------------------------------------------------------
void* api_malloc(unsigned int size)
{
	// �������� ������� ����������
	if (size == 0)
		return 0;

	// ��������� ������
	return GlobalAlloc(GPTR, size);
}

//-----------------------------------------------------------------------------
// ������������ ������
// �� �����    :  ptr   - ��������� �� ��������� ���� ������
// �� ������   :  *
//-----------------------------------------------------------------------------
void api_free(void* ptr)
{
	// �������� ����������
	if (ptr != 0)
		GlobalFree(ptr);
}


//-----------------------------------------------------------------------------
// C������� ������ ��������� ���������������
// �� �����    :
// �� ������   :
//-----------------------------------------------------------------------------
void device_GrowArray(void)
{
	device_t** newlist;

	// ���������� �������
	api._deviceList._capacity += DEVICE_GROWBY;

	// ��������� ������ �������
	newlist = (device_t * *)
		malloc(api._deviceList._capacity * sizeof(device_t *));

	// ���������� ������ �������
	memset(newlist, 0, api._deviceList._capacity * sizeof(device_t *));

	// ����������� ������� ������� � �����
	if (api._deviceList._size > 0)
		memcpy(newlist,
			api._deviceList._array,
			api._deviceList._size * sizeof(device_t *));

	// ������������ ������� �������
	free(api._deviceList._array);

	// ������� ����� ������ � ����
	api._deviceList._array = newlist;
}

#ifndef _USRDLL
//-----------------------------------------------------------------------------
// C������� ������ ��������� ���������������
// �� �����    :
// �� ������   :
//-----------------------------------------------------------------------------
void context_GrowArray(void)
{
	context_t** newlist;

	// ���������� �������
	api._contextList._capacity += CONTEXT_GROWBY;

	// ��������� ������ �������
	newlist = (context_t * *)
		malloc(api._contextList._capacity * sizeof(context_t *));

	// ���������� ������ �������
	memset(newlist, 0, api._contextList._capacity * sizeof(context_t *));

	// ����������� ������� ������� � �����
	if (api._contextList._size > 0)
		memcpy(newlist,
			api._contextList._array,
			api._contextList._size * sizeof(context_t *));

	// ������������ ������� �������
	free(api._contextList._array);

	// ������� ����� ������ � ����
	api._contextList._array = newlist;
}
#endif
//-----------------------------------------------------------------------------
// C������� ������ �������
// �� �����    :
// �� ������   :
//-----------------------------------------------------------------------------
void sample_GrowArray(void)
{
	sample_t** newlist;

	// ���������� �������
	api._sampleList._capacity += SAMPLE_GROWBY;

	// ��������� ������ �������
	newlist = (sample_t * *)
		malloc(api._sampleList._capacity * sizeof(sample_t *));

	// ���������� ������ �������
	memset(newlist, 0, api._sampleList._capacity * sizeof(sample_t *));

	// ����������� ������� ������� � �����
	if (api._sampleList._size > 0)
		memcpy(newlist,
			api._sampleList._array,
			api._sampleList._size * sizeof(sample_t *));

	// ������������ ������� �������
	free(api._sampleList._array);

	// ������� ����� ������ � ����
	api._sampleList._array = newlist;
}

//-----------------------------------------------------------------------------
// ��������� ��������� ������ ������ ���������
// �� �����    :  Id	- ������������� ����������
//  			  Desc  - ��� ����������
//  			  Mod      - ��� ����� � ���������
//  			  Data  - ��������� �� ������ ��������� ���������
// �� ������   :  TRUE  - ���������� ������������
//  			  FALSE - ��������� ������������
//-----------------------------------------------------------------------------
BOOL CALLBACK api_DirectSoundEnumerate(LPGUID Id, LPSTR Desc, LPSTR Mod,
	HWND hWnd)
{
	int i;
	LPDIRECTSOUND direct;
	LPDIRECTSOUNDBUFFER primary;
	LPDIRECTSOUND3DLISTENER listener;
	device_t* device;

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
		if (api._deviceList._size == api._deviceList._capacity)
			device_GrowArray();

		// �������� ����� ������ ��� ����� ����������
		device = (device_t *) malloc(sizeof(device_t));
		memset(device, 0, sizeof(device_t));

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
			i = api._deviceList._size++;
			api._deviceList._array[i] = device;
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
int api_CreateDeviceList(void)
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
	DirectSoundEnumerate((LPDSENUMCALLBACK) api_DirectSoundEnumerate, hWnd);

	// �������� �������� ����
	ReleaseHiddenWindow(hWnd);

	return true;
}

//-----------------------------------------------------------------------------
// ��������� ���������� ��������� ���������������
// �� �����    :  
// �� ������   :  
//-----------------------------------------------------------------------------
int api_GetNumDevice(void)
{
	// ������������� ����
	api_Startup();

	// ������ ���������� ��������� ���������������
	return api._deviceList._size;
}

//-----------------------------------------------------------------------------
// ��������� ����� ���������� ���������������
// �� �����    :  
// �� ������   :  
//-----------------------------------------------------------------------------
char* api_GetDeviceName(int device)
{
	// ������������� ����
	api_Startup();

	// ����� ���������� ���� ?
	if (device >= api._deviceList._size)
		return 0;

	// ������ ���
	return api._deviceList._array[device]->_name;
}

//-----------------------------------------------------------------------------
// ��������� �������������� ���������� ���������������
// �� �����    :  
// �� ������   :  
//-----------------------------------------------------------------------------
LPGUID api_GetDeviceID(int device)
{
	// ������������� ����
	api_Startup();

	// ����� ���������� ���� ?
	if (device >= api._deviceList._size)
		return NULL;

	// ������ �������������
	return api._deviceList._array[device]->_id;
}

//-----------------------------------------------------------------------------
// ��������� �������������� ���������� ���������������
// �� �����    :  
// �� ������   :  
//-----------------------------------------------------------------------------
device_t* api_GetDevice(int device)
{
	// ������������� ����
	api_Startup();

	// ����� ���������� ���� ?
	if (device >= api._deviceList._size)
		return 0;

	// ������ �������������
	return api._deviceList._array[device];
}
#ifndef _USRDLL
//-----------------------------------------------------------------------------
// ��������� ���������
// �� �����    :  
// �� ������   :  
//-----------------------------------------------------------------------------
context_t* api_GetContext(void* id)
{
	// ������������� ����
	api_Startup();

	for (int i = 0; i < api._contextList._size; i++)
		if (api._contextList._array[i] != 0)
			if (api._contextList._array[i]->_id == id)
				return api._contextList._array[i];
	return 0;
}
//-----------------------------------------------------------------------------
// �������� ���������
// �� �����    :  
// �� ������   :  
//-----------------------------------------------------------------------------
context_t* api_CreateContext(void* id)
{
	int i;
	context_t* context;

	// ������������� ����
	api_Startup();

	// ����� ���������� ���� ��� ���������� ?
	if (api._contextList._size == api._contextList._capacity)
		context_GrowArray();

	// �������� ����� ������ ��� ����� ����������
	context = (context_t *) malloc(sizeof(context_t));
	memset(context, 0, sizeof(context_t));

	// �������� �������������
	context->_id = id;

	// ��������� ������ �������� � ������
	i = api._contextList._size++;
	api._contextList._array[i] = context;
	return context;
}

//-----------------------------------------------------------------------------
// �������� ���������
// �� �����    :  
// �� ������   :  
//-----------------------------------------------------------------------------
void api_ReleaseContext(void* id)
{
	// ����� ������� ���������
	for (int i = 0; i < api._contextList._size; i++) {
		// ������ �������� ?
		if (api._contextList._array[i]->_id == id) {
			// ��������� ��������
			free(api._contextList._array[i]);
			// ������� ������
			api._contextList._array[i] = 0;
			api._contextList._size--;
			return;
		}
	}
}
#endif

//-----------------------------------------------------------------------------
// ������������� ����� ������
//	�� ����� :	filename - ��������� �� ��� �����
//	�� ������:	*
//-----------------------------------------------------------------------------
void LogInit(char* filename)
{
	// ����������
	FILE* file = 0;

	// �������� �� �������������
	if (api._log_init)
		return;

	// �������� �������
	while (api._log_mutex == 0)
		api._log_mutex = CreateMutex(0, 0, 0);

	// ���������� ������� � ��� �����
	WaitForSingleObject(api._log_mutex, INFINITE);

	// ��������� ���������� �������
	api._log_start_time = timeGetTime();

	// ����������� ����� �����
	strcpy(api._log_file_name, filename);

	// �������� ��� �����
	file = fopen(api._log_file_name, "wb");

	// ������� ����
	fclose(file);

	// ��� ���� ���������������
	api._log_init = true;

	// ������������ ������
	ReleaseMutex(api._log_mutex);
}

//-----------------------------------------------------------------------------
// ������������ ����� ������
//	�� ����� :	*
//	�� ������:	*
//-----------------------------------------------------------------------------
void LogFree(void)
{
	// ���� ������������� �� ���� ������
	if (!api._log_init)
		return;

	// ���������� ������� � ��� �����
	WaitForSingleObject(api._log_mutex, INFINITE);

	// ��� ������
	api._log_init = false;

	// ������� ����� �����
	memset(api._log_file_name, 0, sizeof(api._log_file_name));

	// ������������ ������
	ReleaseMutex(api._log_mutex);

	// ������������ �������
	CloseHandle(api._log_mutex);
}

//-----------------------------------------------------------------------------
// ������ ������ � �����
//	�� ����� :	��������� �� ������
//	�� ������:	*
//-----------------------------------------------------------------------------
void api_Log(const char* string, ...)
{
	va_list ap;
	FILE* file;
	char temp[1024];

	// ������������� ����
	api_Startup();

	// �������� ����������
	if ((!api._log_init) || (!string))
		return;

	// ���������� �������
	WaitForSingleObject(api._log_mutex, INFINITE);

	temp[0] = 0;

	// ������������ ������
	va_start(ap, string);
	vsprintf(temp, string, ap);
	va_end(ap);

	file = fopen(api._log_file_name, "ab+");
	fprintf(file, "%s\n", temp);
	fflush(file);
	fclose(file);

	// ��������������� �������
	ReleaseMutex(api._log_mutex);
}

//-----------------------------------------------------------------------------
// ������ ������ � ����� � ����������� �������
//	�� ����� :	��������� �� ������
//	�� ������:	*
//-----------------------------------------------------------------------------
void api_LogTime(const char* string, ...)
{
	va_list ap;
	FILE* file;
	char temp[1024];
	unsigned int   hour, min, sec, millisec;

	// ������������� ����
	api_Startup();

	// �������� ����������
	if ((!api._log_init) || (!string))
		return;

	// ���������� �������
	WaitForSingleObject(api._log_mutex, INFINITE);

	// �������� ������ ��� ������ � ��������
	millisec = timeGetTime() - api._log_start_time;
	hour = millisec / 3600000;
	millisec -= hour * 3600000;
	min = millisec / 60000;
	millisec -= min * 60000;
	sec = millisec / 1000;
	millisec -= sec * 1000;

	temp[0] = 0;

	// ������������ ������
	va_start(ap, string);
	vsprintf(temp, string, ap);
	va_end(ap);

	file = fopen(api._log_file_name, "ab+");
	fprintf(file,
		"[%.2d:%.2d:%.2d.%.3d]\t%s\n",
		hour,
		min,
		sec,
		millisec,
		temp);
	fflush(file);
	fclose(file);

	// ��������������� �������
	ReleaseMutex(api._log_mutex);
}

//-----------------------------------------------------------------------------
// ������������� ���������� ����� �� ���������
// �� �����    :  in	- ��������� �� ������� ��������� ����� �� ���������
//  			  out   - ��������� �� �������� ��������� ����� �� ���������
// �� ������   :  *
//-----------------------------------------------------------------------------
void InitSoundDefault(squall_sample_default_t* in,
	squall_sample_default_t* out, unsigned int frequency)
{
	// �������� ������� ������� ����������
	if (in) {
		// ��������� ���������
		memcpy(out, in, sizeof(squall_sample_default_t));

		// �������� ������� �������������
		if (out->Frequency == 0)
			out->Frequency = frequency;
		else if (out->Frequency < 100)
			out->Frequency = 100;
		else if (out->Frequency > 100000)
			out->Frequency = 100000;

		// �������� ���������
		if (out->Volume > 100)
			out->Volume = 100;

		// �������� ��������
		if (out->Pan > 100)
			out->Pan = 50;

		// �������� ����������� ���������� ����������
		if (out->MinDist <= 0.0f)
			out->MinDist = DS3D_DEFAULTMINDISTANCE;

		// �������� ������������ ���������� ����������
		if (out->MaxDist <= 0.0f)
			out->MaxDist = DS3D_DEFAULTMAXDISTANCE;
	} else {
		// �������� ���� ��������� �� ���������
		out->SampleGroupID = 0;
		out->Frequency = frequency;
		out->Volume = 100;
		out->Pan = 50;
		out->Priority = 0;
		out->MinDist = DS3D_DEFAULTMINDISTANCE;
		out->MaxDist = DS3D_DEFAULTMAXDISTANCE;
	}
}

//-----------------------------------------------------------------------------
// ������������ ������� � ������ ������
// �� �����    :  *
// �� ������   :  *
//-----------------------------------------------------------------------------
void SampleLock(void)
{
	WaitForSingleObject(api._sample_mutex, INFINITE);
}

//-----------------------------------------------------------------------------
// ��������������� ������� � ������ ������
// �� �����    :  *
// �� ������   :  *
//-----------------------------------------------------------------------------
void SampleUnlock(void)
{
	ReleaseMutex(api._sample_mutex);
}

//-----------------------------------------------------------------------------
// ��������� ��������� �� ������ ������
// �� �����    :  *
// �� ������   :  *
//-----------------------------------------------------------------------------
sample_t* GetSample(int id)
{
	unsigned char  count;
	int index;

	count = id >> 16;
	index = id & 0xFFFF;

	if (index >= api._sampleList._size)
		return 0;

	if (api._sampleList._array[index]->_count != count)
		return 0;

	if (!api._sampleList._array[index]->_file)
		return 0;

	return api._sampleList._array[index];
}

//-----------------------------------------------------------------------------
// �������� ������ �� �����
// �� �����    :  *
// �� ������   :  *
//-----------------------------------------------------------------------------
int api_SampleLoadFile(const char* filename, int mem_flag,
	squall_sample_default_t* def)
{
	int index, hole, equal;
	sample_t* sample;
	CSoundFile* new_sample;

	// ������������� ����
	api_Startup();

	// ����� ����� � �������� ������
	for (equal = -1, hole = -1, index = 0;
		index < api._sampleList._size;
		index++) {
		// ������� ���� ?
		if (api._sampleList._array[index]->_file != 0) {
			// �������� ������ ?
			if (equal == -1) {
				// ����� ������� ?
				if (strcmp(filename,
						api._sampleList._array[index]->_file->GetFileName()) ==
					0) {
					equal = index;
					if (hole != -1)
						break;
				}
			}
		} else {
			hole = index;
			if (equal != -1)
				break;
		}
	}

	// ���� ���������� ��������� ������ ���� ����� 65535 � ����� ��� �������� ������
	if ((hole == -1) && (api._sampleList._size >= 65535))
		return 0;

	// ����� ����� ���� ��� ���������� ?
	if (api._sampleList._size == api._sampleList._capacity)
		sample_GrowArray();

	// ����� ���� ?
	if (hole == -1) {
		// �������� ����� ������ ��� ����� �����
		sample = (sample_t *) malloc(sizeof(sample_t));
		memset(sample, 0, sizeof(sample_t));
		index = api._sampleList._size++;
		// ��������� ������ �������� � ������
		api._sampleList._array[index] = sample;
	} else {
		index = hole;
	}


	// �������� ���� ���� ?
	if (equal == -1) {
		// �������� ������ �����
		new_sample = new CSoundFile();

		// ���������� ������� �������� ������
		if (!new_sample->CreateSoundDataFromFile(filename, mem_flag)) {
			// ������ �������� ������ ��������� ��� ������� �������
			delete new_sample;  				   // �������� ��������� �����
			return 0;
		}
	} else {
		// �������� ������
		new_sample = api._sampleList._array[equal]->_file;
	}

	// ������� ����� �������
	api._sampleList._array[index]->_file = new_sample;
	// ���������� ������ �� ������
	api._sampleList._array[index]->_file->AddRef();

	// ��������� ��������� �� ���������
	InitSoundDefault(def,
		& api._sampleList._array[index]->_def,
		new_sample->GetFormat()->nSamplesPerSec);

	// ������� ������������� ������
	api._sampleList._array[index]->_count++;

	// ������ ������ ���������� ��������
	return index | api._sampleList._array[index]->_count << 16;
}

//-----------------------------------------------------------------------------
// �������� ������ �� ������
// �� �����    :  *
// �� ������   :  *
//-----------------------------------------------------------------------------
int api_CreateSampleFromMemory(void* ptr, unsigned int size, int new_mem,
	squall_sample_default_t* def)
{
	int index, hole;
	sample_t* sample;
	CSoundFile* new_sample;

	// ������������� ����
	api_Startup();

	// ����� ����� � �������� ������
	for (hole = -1, index = 0; index < api._sampleList._size; index++) {
		// ������� ���� ?
		if (api._sampleList._array[index]->_file == 0) {
			hole = index;
			break;
		}
	}

	// ���� ���������� ��������� ������ ���� ����� 65535 � ����� ��� �������� ������
	if ((hole == -1) && (api._sampleList._size >= 65535))
		return 0;

	// ����� ����� ���� ��� ���������� ?
	if (api._sampleList._size == api._sampleList._capacity)
		sample_GrowArray();

	// ����� ���� ?
	if (hole == -1) {
		// �������� ����� ������ ��� ����� �����
		sample = (sample_t *) malloc(sizeof(sample_t));
		memset(sample, 0, sizeof(sample_t));
		index = api._sampleList._size++;
		// ��������� ������ �������� � ������
		api._sampleList._array[index] = sample;
	} else {
		index = hole;
	}


	// �������� ������ �����
	new_sample = new CSoundFile();

	// ���������� ������� �������� ������
	if (!new_sample->CreateSoundDataFromMemory(ptr, size, new_mem)) {
		// ������ �������� ������ ��������� ��� ������� �������
		delete new_sample;  				   // �������� ��������� �����
		return 0;
	}

	// ������� ����� �������
	api._sampleList._array[index]->_file = new_sample;
	// ���������� ������ �� ������
	api._sampleList._array[index]->_file->AddRef();

	// ��������� ��������� �� ���������
	InitSoundDefault(def,
		& api._sampleList._array[index]->_def,
		new_sample->GetFormat()->nSamplesPerSec);

	// ������� ������������� ������
	api._sampleList._array[index]->_count++;

	// ������ ������ ���������� ��������
	return index | api._sampleList._array[index]->_count << 16;
}

//-----------------------------------------------------------------------------
// ������������ ������
// �� �����    :  id - ������������� �������������� ������
// �� ������   :  *
//-----------------------------------------------------------------------------
void api_SampleUnload(int id)
{
	sample_t* sample;

	// ��������� ������
	SampleLock();

	// �������� ������� ������
	sample = GetSample(id);
	if (sample) {
		// ������ ������ �� ����
		if (sample->_file->DecRef() == 0)
			delete sample->_file;

		// �������� �����
		sample->_file = 0;
	}

	// ������������ ������
	SampleUnlock();
}

//-----------------------------------------------------------------------------
// ������������ ���� �������
// �� �����    :  *
// �� ������   :  *
//-----------------------------------------------------------------------------
void api_SampleUnloadAll(void)
{
	// ��������� ������
	SampleLock();

	// �������� ���� ������ �� ���������
	for (int i = 0; i < api._sampleList._size; i++) {
		if (api._sampleList._array[i]->_file != 0)
			if (api._sampleList._array[i]->_file->DecRef() == 0)
				delete api._sampleList._array[i]->_file;
		api._sampleList._array[i]->_file = 0;
	}

	// ������������ ������
	SampleUnlock();
}

//-----------------------------------------------------------------------------
// ��������� ��������� �� ������ ������
// �� �����    :  id - ������������� �����
// �� ������   :  ��������� �� ������ �����, � ������ ������ 0
//-----------------------------------------------------------------------------
CSoundFile* api_SampleGetFile(int id)
{
	sample_t* sample;
	CSoundFile* file;

	// ��������� ������
	SampleLock();

	// �������� ������� ������
	sample = GetSample(id);
	if (!sample)
		file = 0;
	else
		file = sample->_file;

	// ������������ ������
	SampleUnlock();

	return file;
}

//-----------------------------------------------------------------------------
// ��������� ��������� �� ������ ������ �� ������
// �� �����    :  id	-  ������������� ������
//  			  num   -  ����� ����� � ������
// �� ������   :  ������������� ������
//-----------------------------------------------------------------------------
int api_SampleGetFileGroup(int id, unsigned int num)
{
	// ����������
	int index = 0;
	int count = 0;

	// ��������� ������
	SampleLock();

	// ����������� ������
	for (count = 0, index = 0; index < api._sampleList._size; index++) {
		// ������ �������
		if ((api._sampleList._array[index]->_file != 0) &&
			(api._sampleList._array[index]->_def.SampleGroupID == id)) {
			// �������� �� ������������
			if (count >= SAMPLES_IN_GROUP)
				break;
			api_temp[count] = index;
			count++;
		}
	}

	// ������� ��������� �����
	if (count != 0) {
		index = api_temp[rand() % count];
		index |= api._sampleList._array[index]->_count << 16;
	} else
		index = 0;

	// ������������ ������
	SampleUnlock();

	// ������ ������ ���������� ��������
	return index;
}

//-----------------------------------------------------------------------------
// ��������� ���������� ������ �� ���������
// �� �����    :  id	-  ������������� ������
//  			  def   -  ��������� �� ������ ������ �� ���������
// �� ������   :  ���������� ����������
//-----------------------------------------------------------------------------
int api_SampleSetDefault(int id, squall_sample_default_t* def)
{
	sample_t* sample;
	int ret = false;

	// ������������ �������
	SampleLock();

	// ��������� ��������� �� �����
	sample = GetSample(id);
	if (sample) {
		// ��������� ��������� �� ���������
		InitSoundDefault(def,
			& sample->_def,
			sample->_file->GetFormat()->nSamplesPerSec);
		ret = true;
	}

	// ������������ ������
	SampleUnlock();

	return ret;
}

//-----------------------------------------------------------------------------
// ��������� ���������� ������ �� ���������
// �� �����    :  id	-  ������������� ������
//  			  def   -  ��������� �� ������ ������ �� ���������
// �� ������   :  ���������� ����������
//-----------------------------------------------------------------------------
int api_SampleGetDefault(int id, squall_sample_default_t* def)
{
	sample_t* sample;
	int ret = false;

	// ������������ �������
	SampleLock();

	// ��������� ��������� �� �����
	sample = GetSample(id);
	if (sample) {
		// ��������� ��������� �� ���������
		memcpy(def, & sample->_def, sizeof(squall_sample_default_t));
		ret = true;
	}

	// ������������ ������
	SampleUnlock();

	return ret;
}

//-----------------------------------------------------------------------------
// ������������� ������ ����
// �� �����    :  *
// �� ������   :  *
//-----------------------------------------------------------------------------
void api_Startup(void)
{
	// ���� ���������������� ?
	if (api_init == 0) {
		// ���������� ���� � ������
		memset(&api, 0, sizeof(api));

		// ��������� ������� ��� ������ � ������� � �������
		api._open = api_open;
		api._read = api_read;
		api._seek = api_seek;
		api._close = api_close;
		api._malloc = api_malloc;
		api._free = api_free;

		// ���������� ����������
#if SQUALL_DEBUG

		// ��������� ������� ����������
		char LogFileName[4096];
		GetCurrentDirectory(sizeof(LogFileName), LogFileName);

		// �������� ���� ������
		strcat(LogFileName, "\\Squall.log");

		// ������������� ����� ������
		LogInit(LogFileName);
#endif
		// �������� ������ ��������� ���������������
		device_GrowArray();

		// �������� ������ ����������
#ifndef _USRDLL
		context_GrowArray();
#endif

		// �������� ������� ��� ������� ���������
		while (api._sample_mutex == 0)
			api._sample_mutex = CreateMutex(0, 0, 0);

		// ����������� ������ � ���������
		SampleLock();

		// �������� ������ �������
		sample_GrowArray();

		// ������������ ������ � ���������
		SampleUnlock();

		// �������� ������ ��������� ���������������
		api_CreateDeviceList();

		// ���� ����������������
		api_init = 1;

		// ���������� ����������
#if SQUALL_DEBUG

		// ����������
		device_t* dev;

		// �������� ������ �� ����������� ���������������
		for (int i = 0; i < api_GetNumDevice(); i++) {
			dev = api_GetDevice(i);
			api_Log("[���������� �%d] %s", i, dev->_name);

			if (dev->_caps.dwFlags & DSCAPS_CERTIFIED)
				api_Log("���������� �������������� � ��������������� Microsoft");
			if (dev->_caps.dwFlags & DSCAPS_EMULDRIVER)
				api_Log("�� ����� DirectX ��������");

			api_Log("\t[���������� �����������]");
			if (dev->_caps.dwFlags & DSCAPS_CONTINUOUSRATE) {
				api_Log("\t- ��������� �������������� ������� �������������, ��� ��������� �������,\n\t  �� %d �� %d",
					dev->_caps.dwMinSecondarySampleRate,
					dev->_caps.dwMaxSecondarySampleRate);
			}

			api_Log("\t- ��������� �������������� ��������� ���� ��������:");
			api_Log("\t\t��� ������  8 ��� 16 ��� ���� ������ ");
			api_Log("\t\t���������   %s   %s    %s  %s",
				(dev->_caps.dwFlags & DSCAPS_PRIMARY8BIT) ? "�� " : "���",
				(dev->_caps.dwFlags & DSCAPS_PRIMARY16BIT) ? "�� " : "���",
				(dev->_caps.dwFlags & DSCAPS_PRIMARYMONO) ? "�� " : "���",
				(dev->_caps.dwFlags & DSCAPS_PRIMARYSTEREO) ? "�� " : "���");
			api_Log("\t\t���������   %s   %s    %s  %s",
				(dev->_caps.dwFlags & DSCAPS_SECONDARY8BIT) ? "�� " : "���",
				(dev->_caps.dwFlags & DSCAPS_SECONDARY16BIT) ? "�� " : "���",
				(dev->_caps.dwFlags & DSCAPS_SECONDARYMONO) ? "�� " : "���",
				(dev->_caps.dwFlags & DSCAPS_SECONDARYSTEREO) ? "�� " : "���");

			api_Log("\t- ��������� �������������� ��������� ���������� �������:");
			api_Log("\t\t          2D ���������� [�� ��� ��������] 3D ���������� [�� ��� �������]");
			api_Log("\t\t�����     %.2d            [%.2d]              %.2d            [%.2d]",
				dev->_caps.dwMaxHwMixingAllBuffers,
				dev->_caps.dwFreeHwMixingAllBuffers,
				dev->_caps.dwMaxHw3DAllBuffers,
				dev->_caps.dwFreeHw3DAllBuffers);
			api_Log("\t\t��������� %.2d            [%.2d]              %.2d            [%.2d]",
				dev->_caps.dwMaxHwMixingStaticBuffers,
				dev->_caps.dwFreeHwMixingStaticBuffers,
				dev->_caps.dwMaxHw3DStaticBuffers,
				dev->_caps.dwFreeHw3DStaticBuffers);
			api_Log("\t\t��������� %.2d            [%.2d]              %.2d            [%.2d]",
				dev->_caps.dwMaxHwMixingStreamingBuffers,
				dev->_caps.dwFreeHwMixingStreamingBuffers,
				dev->_caps.dwMaxHw3DStreamingBuffers,
				dev->_caps.dwFreeHw3DStreamingBuffers);

			api_Log("\t- ���������� ��������� �������         = %d",
				dev->_caps.dwPrimaryBuffers);
			api_Log("\t- ����� ���� ������ �� ����������      = %d",
				dev->_caps.dwTotalHwMemBytes);
			api_Log("\t- ����� ��������� ������ �� ���������� = %d",
				dev->_caps.dwFreeHwMemBytes);
			//  	 api_Log("\tdwMaxContigFreeHwMemBytes      = %d", cur->DeviceInfo.dwMaxContigFreeHwMemBytes);
			//  	 api_Log("\tdwUnlockTransferRateHwBuffers  = %d", cur->DeviceInfo.dwUnlockTransferRateHwBuffers);
			//  	 api_Log("\tdwPlayCpuOverheadSwBuffers     = %d", cur->DeviceInfo.dwPlayCpuOverheadSwBuffers);

			// ������� ���������� � �������� ����������� �����
			api_Log("\t- �������� ����������");
			for (int eax = 1; eax <= EAX_NUM; eax++)
				api_Log("\t\tEAX %d.0 %s",
					eax,
					dev->_eax[eax] ? "��������������" : "�� ��������������");

			// ZOOMFX
			api_Log("\t\tZOOMFX %s",
				dev->_zoomfx ? "��������������" : "�� ��������������");

			// ������� ������ �������������� 3D ����������
			api_Log("\t- �������������� 3D ���������");
			if (dev->_alg[1])
				api_Log("\t\tALG_3D_OFF");
			if (dev->_alg[2])
				api_Log("\t\tALG_3D_FULL");
			if (dev->_alg[3])
				api_Log("\t\tALG_3D_LIGTH");
		}
#endif
	}
}

//-----------------------------------------------------------------------------
// ������������ ������ ����
// �� �����    :  *
// �� ������   :  *
//-----------------------------------------------------------------------------
void api_Shutdown(void)
{
	int i;
	// ���� ���������������� ?
	if (api_init == 1) {
#ifndef _USRDLL
		// ��������� ���� ?
		if (api._contextList._size == 0) {
#endif
			// �������� ���� �������
			api_SampleUnloadAll();

			// �������� ������� ��� ���������� �������
			CloseHandle(api._sample_mutex);
			api._sample_mutex = 0;

			// �������� �������
			for (i = 0; i < api._sampleList._size; i++)
				free(api._sampleList._array[i]);

			// �������� ������� �������
			free(api._sampleList._array);

#ifndef _USRDLL
			// �������� ��������� ������ ����������
			for (i = 0; i < api._contextList._size; i++)
				free(api._contextList._array[i]);
			// �������� ������� ����������
			free(api._contextList._array);
#endif

			// �������� ��������� ������ ���������
			for (i = 0; i < api._deviceList._size; i++)
				free(api._deviceList._array[i]);

			// �������� ������� ���������
			free(api._deviceList._array);

			// ������������ ����� ������
			LogFree();

			// ������� ����
			memset(&api, 0, sizeof(api));

			// ���� ����������������
			api_init = 0;
#ifndef _USRDLL
		}
#endif
	}
}

//-----------------------------------------------------------------------------
// ��������� ������� ������� ������ � ������
// �� �����    :  ext_open    - ��������� �� ������� �������� �����
//  			  ext_read    - ��������� �� ������� ������ �����
//  			  ext_seek    - ��������� �� ������� ���������������� � �����
//  			  ext_close   - ��������� �� ������� �������� �����
// �� ������   :  ���������� ���������
//-----------------------------------------------------------------------------
void api_SetFileCallbacks(extern_open_t ext_open, extern_read_t ext_read,
	extern_seek_t ext_seek, extern_close_t ext_close)
{
	// ������������� ����
	api_Startup();

	// ��������� ������ � ������
	SampleLock();

	// ������� ��������� �� ������ ������ � �������
	api._open = ext_open;
	api._read = ext_read;
	api._seek = ext_seek;
	api._close = ext_close;

	// ������������ ������ � ������
	SampleUnlock();
}

//-----------------------------------------------------------------------------
// ��������� ������� ������� ������ � �������
// �� �����    :  ext_malloc  -  ��������� �� ������� ��������� ������
//  			  ext_free    -  ��������� �� ������� ������������ ������
// �� ������   :  ���������� ���������
//-----------------------------------------------------------------------------
void api_SetMemoryCallbacks(extern_malloc_t ext_malloc, extern_free_t ext_free)
{
	// ������������� ����
	api_Startup();

	// ��������� ������ � ������
	SampleLock();

	// ��������� ������ ��� ������ � �������
	api._malloc = ext_malloc;
	api._free = ext_free;

	// ������������ ������ � ������
	SampleUnlock();
}
