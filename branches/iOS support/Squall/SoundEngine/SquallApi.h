//-----------------------------------------------------------------------------
// �������� ���� ��������� ��������� "�����"
// �������     : AntiTank
// ����������� : ������������ ����� (�����)
//-----------------------------------------------------------------------------
#ifndef _SQUALL_API_H_INCLUDED_
#define _SQUALL_API_H_INCLUDED_

#include <dsound.h>
#include "Eax.h"
#include "ExternFunction.h"
#include "Squall.h"
#include "SoundFile.h"
#include "Context.h"

/////////////////////////////////////////////////
// �������
/////////////////////////////////////////////////
#define DEVICE_NAME_LEN 256 					   // ������������ ������ ������ � ������ ���������� ���������������

/////////////////////////////////////////////////
// ��������� ���������� ���������������
/////////////////////////////////////////////////
typedef struct device_s {
	LPGUID _id; 				   // ������������� ���������� ���������������
	DSCAPS _caps;   			   // ���������� �� ����������
	char _name[DEVICE_NAME_LEN]; // ��� ���������� ���������������
	int _alg[4];				// ������ �������������� 3D ����������
	int _eax[EAX_NUM + 1];  	  // ���������� � ��������� EAX �����������
	int _zoomfx;				// ���������� � ��������� ZOOMFX
} device_t;

////////////////////////////////////////////////
// C�������� ������ ��������� ���������������
////////////////////////////////////////////////
typedef struct device_list_s {
	int _capacity;  			// ������� ������ �������
	int _size;  				// ������� ���������� ��������� � �������
	device_s** _array;  			   // ��������� �� ������
} device_list_t;

////////////////////////////////////////////////
// ��������� ��� �������� �������� ������
////////////////////////////////////////////////
typedef struct sample_s {
	unsigned char _count;   			  // ������� ��� ���������� ������
	CSoundFile* _file;  				// ��������� �� �������� ������
	squall_sample_default_t _def;   				// ��������� �� ���������
} sample_t;

////////////////////////////////////////////////
// C�������� ������ ����������
////////////////////////////////////////////////
typedef struct context_list_s {
	int _capacity;  			// ������� ������ �������
	int _size;  				// ���������� ��������� � ������
	context_t** _array; 				// ��������� �� ������ � �������
} context_list_t;

////////////////////////////////////////////////
// C�������� ������ �������� ������
////////////////////////////////////////////////
typedef struct sample_list_s {
	int _capacity;  			// ������� ������ �������
	int _size;  				// ���������� ��������� � ������
	sample_t** _array;  			   // ��������� �� ������ � �������
} sample_list_t;

////////////////////////////////////////////////
// C�������� ���� ������
////////////////////////////////////////////////
typedef struct squall_api_s {
	device_list_t _deviceList;  		  // ������ ��������� ���������������
#ifndef _USRDLL
	context_list_t _contextList;		   // ������ ����������
#else
	context_t _context;
#endif
	sample_list_t _sampleList;  		  // ������ �������
	HANDLE _sample_mutex;   	   // ������ ��� ������ �������
	int _log_init;  			// ���� ������������� ����
	HANDLE _log_mutex;  		   // ������ ��� �����
	unsigned int _log_start_time;   	 // ����� ������� ����
	char _log_file_name[1024];   // ��� ��� �����

	// ��������� �� ������� �������
	extern_open_t _open;				  // ������� ������� �������� �����
	extern_read_t _read;				  // ������� ������� ������ �����
	extern_seek_t _seek;				  // ������� ������� ���������������� � �����
	extern_close_t _close;  			   // ������� ������� �������� �����
	extern_malloc_t _malloc;				// ������� ������� ��������� ������
	extern_free_t _free;				  // ������� ������� ������������ ������
} squall_api_t;

extern squall_api_s api;

////////////////////////////////////////////////
// ������� ������
////////////////////////////////////////////////
void* api_malloc(   						 // ��������� ������
unsigned int size);

void api_free(  							// ������������ ������
void* ptr);

void api_Startup(); 						// ������������� ����

void api_Shutdown();						// ��������������� ����

// ������ � ������������ ���������������
LPGUID api_GetDeviceID( 					  // ��������� �������������� ���������� ���������������
int device);

int api_GetNumDevice(); 				   // ��������� ���������� ��������� ���������������

char* api_GetDeviceName(					 // ��������� ����� ���������� ���������������
int device);

device_t* api_GetDevice(						 // ��������� ������� ���������� ���������������
int device);

// ������ � �����������
context_t* api_CreateContext(   				  // �������� ���������
void* id);

context_t* api_GetContext(  					  // ��������� ���������
void* id);

void api_ReleaseContext(					// ������������ ���������
void* id);

// ������ � ��������
int api_SampleLoadFile( 				   // �������� ������ �� �����
const char* filename, int mem_flag, squall_sample_default_t* def);

int api_CreateSampleFromMemory( 		   // �������� ������ �� ������
void* ptr, unsigned int size, int new_mem, squall_sample_default_t* def);

void api_SampleUnload(  					// �������� ������
int id);

void api_SampleUnloadAll(); 				// �������� ���� �������

CSoundFile* api_SampleGetFile(  				   // ��������� ��������� �� �������� ����
int id);

int api_SampleGetFileGroup( 			   // ��������� ��������� �� ������ ������
int id, unsigned int num);

int api_SampleSetDefault(   			   // ��������� ���������� ������ �� ���������
int id, squall_sample_default_t* def);

int api_SampleGetDefault(   			   // ��������� ���������� ������ �� ���������
int id, squall_sample_default_t* def);

// ������ � ��� ������
void api_Log(   							// ������ ������ � �����
const char* string, ...);

void api_LogTime(   						// ������ ������ � ����� � ��������
const char* string, ...);

// ������ � ��������� ��������� ������
void api_SetFileCallbacks(  				// ��������� ������� ������� ������ � �������
extern_open_t ext_open, extern_read_t ext_read, extern_seek_t ext_seek,
	extern_close_t ext_close);

void api_SetMemoryCallbacks(				// ��������� ������� ������� ������ � �������
extern_malloc_t ext_malloc, extern_free_t ext_free);
#endif