//-----------------------------------------------------------------------------
//	������ �� ��������� ��������
//	�������� ��������� ��������� �����
//	�������		: AntiTank
//	�����������	: ������������ ����� (�����)
//-----------------------------------------------------------------------------
#ifndef _SSAMPLE_H_INCLUDED_
#define _SSAMPLE_H_INCLUDED_

// ���������
#include "Squall.h"
#include <dsound.h>	
#include "SoundFile.h"

//-----------------------------------------------------------------------------
//	�������
//-----------------------------------------------------------------------------
// ����� ��������� �����
enum { EMPTY = 0,   								   // ����� ����
PLAY,   										// ����� ���������������
STOP,   										// ����� ����������
PAUSE,  										// ����� � �����
PREPARE,
// ����� ����������� ��� ���������������
};

// ���� ������
enum { ERROR_NO_ERROR = 0,  						   // ��� ������
ERROR_BUFFER_LOST,  							// ����� ������
ERROR_READ_STATUS,  							// ������ ������ ������� �����
};

// ���� ������
enum { TYPE_POSITIONED = 1, 						   // ���� � ������� �����������
TYPE_AMBIENT									// ���������� ����
};

//-----------------------------------------------------------------------------
//	��������� ����������� ��������� ��������� ������
//-----------------------------------------------------------------------------
struct SSoundStatus {
	unsigned STAGE : 3; 				// ��������� ����� ������ ������� ��������� �����
	unsigned STATUS_ERROR : 3;  			   // ���� ������ ������ ������� ����� ������
	unsigned SOUND_TYPE : 2;				 // ��� ����� ������ ������� ����� ������
	unsigned SAMPLE_LOOP : 1;				   //	���� ������������ ��������������� �����
	// 0 - ���� �������� 1 ���
	//	1 - ���� ��������������� ����������
	unsigned BUFFER_LOOP : 1;   			  // ���� ������������ �������� ������
	// 0 - ���� �� ��������
	// 1 - ���� ��������
	unsigned DOUBLE_BUFFERING : 1;  			   // ���� ������� �����������
	// 0 - ����������� �����������
	// 1 - ����������� ������������
	unsigned BUFFER_PRESENT : 1;				 //	���� ������� ������ Direct X
	//	0 - ������ ���
	//	1 - ����� ���� 
};

// ��������� ��� �������� ������ ������
struct SChannelParam {
	DS3DBUFFER ds3d;				   // ��������� ����������� �����
	squall_eax_channel_t EAXBP; 				 // EAX ��������� ������
	squall_zoomfx_channel_t ZOOMFXBP;   			// ZOOMFX ��������� ������
	unsigned int Volume;				 // ��������� ������
	unsigned int Pan;   				 // �������� ������
	unsigned int Frequency; 			 // ������ ������
};

//-----------------------------------------------------------------------------
//	��������� ��������� ������
//-----------------------------------------------------------------------------
struct SSample {
	unsigned char _count;
	// ������ DirectSound
	LPDIRECTSOUNDBUFFER DS_Buffer;  			// ��������� �� ����� ���������������
	LPKSPROPERTYSET DS_PropSet; 			// ��������� �������������� ����������
	LPDIRECTSOUND3DBUFFER DS3D_Buffer;  		  // ��������� �� ��������� ����������� �����
	LPKSPROPERTYSET DS3D_PropSet;   		// ��������� �������������� ���������� 3D ������
	int SamplesInBuffer;		// ���������� ������� � ������
	int BytesInBuffer;  		// ���������� ���� � ������
	int SamplesPerSec;  		// ������� ������� � �������
	int OldBank;				// ���������� ����������� �������� ��������� ������
	int EndFlag;				// ���������� ��� ����������� �������� ����� �� �������
	int StartPtr;   			// ������ ���������
	int EndPtr; 				// ����� ���������
	int CurPtr; 				// ������� ������� ���������������
	int MasterSize; 			// ��������� ������ �������� ������ � ��������
	int PausePtr;   			// ������� ��� ����� �����
	int ChannelID;  			// ������������� ��������� ������
	int GroupID;				// ������ ������
	int Priority;   			// ��������� ������
	SSoundStatus Status;				 // ������ ��������� ������
	int SampleID;   			// ������������� �����
	CSoundFile* SoundFile;  			// ��������� �� ���� �� ������
	SChannelParam Param;				  // ��������� ������

	// ������ ��� �����������
	int ChannelWorkerTime;  	// ������ ������� ����� ������� ����� ���������� ����������
	int OldChannelWorkerTime;   // ���������� ����� ����� ��� ��������� �����
	int (*ChannelWorker)	(int, void*);   		// ��������� �� ���������� ��������� ������
	void* UserData; 			  // ������ ������������

	// ������ ��� ����������� ����� ���������������
	int (*ChannelEndWorker) (int, void*);   		// ��������� �� ���������� ��������� ������
	void* ChannelEndUserData;     // ������ ������������


	// ���������� ��������� ������
	int Update(float x, float y, float z);
	// ���������� �����������
	void UpdateWorker(void);
	// ������ �����
	int Play(void);
	// ��������� �����
	int Stop(void);
	// ��������� ���� ���������� ���������� ������
	int Set3DParameters(D3DVECTOR* Position, D3DVECTOR* Velocity,
		D3DVECTOR* ConeOrientation, unsigned int InsideConeAngle,
		unsigned int OutsideConeAngle, long ConeOutsideVolume, float MinDist,
		float MaxDist, DWORD Deferred);
	// ��������� ���� ���������� ���������� ������
	int Get3DParameters(D3DVECTOR* Position, D3DVECTOR* Velocity,
		D3DVECTOR* ConeOrientation, int* InsideConeAngle,
		int* OutsideConeAngle, long* ConeOutsideVolume, float* MinDist,
		float* MaxDist);
	// ��������� ���� �������� �����
	int FillSoundBuffer(char BankNum);
	// ��������� ��������� � ������� �����
	int GetStatus(void);
	// ������������� ��������� ��������� ������
	int RestoreBuffer(void);
	// �������� �������� ��������� ������
	int CreateSoundBuffer(LPDIRECTSOUND DirectSound, WAVEFORMATEX* format,
		DWORD Size, DWORD SamplesPerBuffer, int UseAcceleration);
	// �������� ����������� ��������� ������
	int Create3DSoundBuffer(LPDIRECTSOUND DirectSound, WAVEFORMATEX* format,
		DWORD Size, DWORD SamplesPerBuffer, DWORD Algorithm, DWORD UseEAX,
		int UseAcceleration);
	// �������� ��������� ������
	int DeleteSoundBuffer(void);
	// ��������� ������ ��������� ��� ������
	int SetVolume(long Volume);
	// ��������� ������ ��������� ��� ������
	int GetVolume(long* Volume);
	// ��������� ����� �������� �������� ������
	int SetFrequency(int Frequency);
	// ��������� ������� �������� ��������
	int GetFrequency(int* Frequency);
	// ��������� ����� ��������
	int SetPan(int Pan);
	// ��������� ������� ��������
	int GetPan(int* Pan);
	// ��������� ����� ������� ���������������
	int SetPlayPosition(int Position);	
	// ��������� ������� ������� ���������������
	int GetPlayPosition(int* Position);
	// ��������� ������� ������� � ��������� ������
	int GetDXPosition(int* Position);
	// ���������/���������� �����
	int Pause(int Flag);
	// ��������� ����� ������ ���������
	int SetFragment(int Start, int End);
};
#endif