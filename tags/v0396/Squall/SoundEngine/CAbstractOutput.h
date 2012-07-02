//-----------------------------------------------------------------------------
//	����������� ����� �����
//	�������� ��������� ��������� �����
//	�����������	: ������������ ����� (�����)
//-----------------------------------------------------------------------------

#ifndef _CABSTRACT_OUTPUT_H_INCLUDED_
#define _CABSTRACT_OUTPUT_H_INCLUDED_

#include <Windows.h>

class CAbstractOutput {
protected:
	unsigned int _channels; 						// ���������� �������
	//   channel_t* _channelsArray;

public:
	// ����������� ����������
	CAbstractOutput()
	{
	};
	virtual ~CAbstractOutput()
	{
	};

	//�������
	//������� ������������� � ������������
	virtual int Init(HWND iWindow,  			   //  ������������� ��������� ���������.
		unsigned int iDevice, int iRate, int iBits, int iChannels) = 0;
	virtual void Free() = 0;						//  ������������ ��������� �������� ������� �������� ����������. 
	/*
	   //������� ���������� �������� ����������
	   virtual void Pause() = 0;					   // ���������/���������� ����� ��������������� ���� �������� �������.
	   virtual void Stop() = 0; 					   // ��������� ��������������� ���� �������� �������. 
	   //������� ��� ��������� ���������� ��������� ���������
	   virtual void SetDevice() = 0;//  ��������� ������ ���������� ���������������.
	   virtual void GetDevice() = 0;//  ��������� �������� ���������� ���������������.
	   virtual void SetHardwareAcceleration() = 0;// ���������/���������� ���������� ��������� �������� �������.
	   virtual void GetHardwareAcceleration () = 0;//��������� ������� �������� ���������� ��������� �������� �������.
	   virtual void SetSpeakerMode() = 0;// ��������� ������ ��������.
	   virtual void GetSpeakerMode() = 0;// ��������� �������� ������ ��������.
	   virtual void Set3DAlgorithm() = 0;// ��������� ��������� ��������� ����������� �����, � ������ ���������� ���������� ��������� ���������� �������� �������.
	   virtual void Get3DAlgorithm () = 0;//��������� �������� ������ ��������� ��������� ����������� �����, � ������ ���������� ���������� ��������� ���������� �������� �������.
	   virtual void SetBufferSize() = 0;// ��������� ������� ��������� ������.
	   virtual void GetBufferSize() = 0;// ��������� �������� ������� ��������� ������.
	   virtual void SetMemoryCallbacks () = 0;//��������� ������� ������� ������ � �������.
	   virtual void SetFileCallbacks() = 0;// ��������� ������� ������� ������ � �������. 
	*/
	//������� ��� ��������� ����������
	virtual int GetNumDevice() = 0; 				// ��������� ���������� ��������� ��������������� � �������.
	virtual char* GetDeviceName() = 0;  			// ��������� ����� ���������� ���������������.
	//   virtual void GetDeviceCaps() = 0;// ��������� ���������� � ������������ ���������� ���������������.
	//   virtual void GetEAXVersion() = 0;// ��������� ����������� ��������� ������ EAX.
	//   virtual void GetChannelsInfo() = 0;// ��������� ���������� � ��������� ���� �������� �������. 
	/*
	   // ���������
	   virtual void Listener_SetParameters() = 0;// ��������� �������� ���������� ���������.
	   virtual void Listener_GetParameters() = 0;//  ��������� ������� �������� ���������� ���������.
	   virtual void Listener_SetVelocity() = 0;// ��������� ����� �������� ����������� ���������.
	   virtual void Listener_GetVelocity() = 0;// ��������� ������� �������� ����������� ���������.
	   virtual void Listener_SetPosition() = 0;// ��������� ������ ��������� ��������� � ������������.
	   virtual void Listener_GetPosition () = 0;//��������� �������� ��������� ��������� � ������������.
	   virtual void Listener_SetDistanceFactor() = 0;// ��������� ������ ������������ �������������� ���������.
	   virtual void Listener_GetDistanceFactor () = 0;//��������� �������� ������������ �������������� ���������.
	   virtual void Listener_SetRolloffFactor () = 0;//��������� ������ ������������ ������� ��������.
	   virtual void Listener_GetRolloffFactor () = 0;//��������� �������� ������������ ������� ��������.
	   virtual void Listener_SetDopplerFactor() = 0;// ��������� ������ ������������ ������� ��������.
	   virtual void Listener_GetDopplerFactor() = 0;// ��������� �������� ������������ ������� ��������.
	   virtual void Listener_Update() = 0;// ���������� ���������� �������� ���������.
	   virtual void Listener_EAX_SetPreset() = 0;// ��������� ������������������ EAX ���������.
	   virtual void Listener_EAX_SetProperties() = 0;// ��������� ����� EAX ���������� ���������.
	   virtual void Listener_EAX_GetProperties() = 0;// ��������� ������� EAX ���������� ���������.
	   virtual void Listener_SetWorker() = 0;// ��������� ����������� ���������. 
	   //������
	   //����� ������� ��� ������ � ��������.
	   virtual void Channel_Start() = 0;// ������ ��������������� ����������� ������. 
	   virtual void Channel_Pause () = 0;// ���������/���������� ����� ��������� ������.
	   virtual void Channel_Stop () = 0;//��������� ��������������� ��������� ������.
	   virtual void Channel_Status () = 0;//��������� �������� ��������� ��������� ������.
	   virtual void Channel_SetVolume() = 0;// ��������� ����� ��������� ��������� ������.
	   virtual void Channel_GetVolume() = 0;// ��������� ������� ��������� ��������� ������.
	   virtual void Channel_SetFrequency() = 0;// ��������� ����� ������� ������������� ��������� ������.
	   virtual void Channel_GetFrequency() = 0;// ��������� ������� ������� ������������� ��������� ������.
	   virtual void Channel_SetPlayPosition() = 0;// ��������� ����� ������� ��������������� ��������� ������, � ��������.
	   virtual void Channel_GetPlayPosition () = 0;//��������� ������� ������� ��������������� ��������� ������, � ��������.
	   virtual void Channel_SetPlayPositionMs() = 0;// ��������� ����� ������� ��������������� ��������� ������, � �������������.
	   virtual void Channel_GetPlayPositionMs() = 0;// ��������� ������� ������� ��������������� ��������� ������, � �������������.
	   virtual void Channel_SetWorker() = 0;// ��������� ����������� ��������� ������.
	   virtual void Channel_SetFragment () = 0;//��������� ����� ������ ��������������� ������, �������� �������, � ��������.
	   virtual void Channel_GetFragment () = 0;//��������� ������� ������ ��������������� ������, �������� �������, � ��������.
	   virtual void Channel_SetFragmentMs () = 0;//��������� ����� ������ ��������������� ������, �������� �������, � �������������.
	   virtual void Channel_GetFragmentMs () = 0;//��������� ������� ������ ��������������� ������, �������� �������, � �������������.
	   virtual void Channel_GetLength () = 0;//��������� �������� ����������������� ������, ��������� ������, � ��������.
	   virtual void Channel_GetLengthMs() = 0;// ��������� �������� ����������������� ������, ��������� ������, � �������������.
	   virtual void Channel_SetPriority () = 0;//��������� ������ ���������� ��������� ������.
	   virtual void Channel_GetPriority() = 0;// ��������� �������� ���������� ��������� ������.
	   virtual void Channel_SetLoop() = 0;// ��������� ����������� ��������������� ��������� ������.
	   virtual void Channel_GetLoop() = 0;// ��������� ������� ����������� ��������������� ��������� ������. 
	   //������� ������ � ����������� ��������
	   virtual void Channel_SetPan() = 0;// ��������� ����� �������� ��������� ������.
	   virtual void Channel_GetPan () = 0;// ��������� ������� �������� ��������� ������. 
	   //������� ������ � ����������������� (�����������) ��������
	   virtual void Channel_Set3DPosition() = 0;// ��������� ����� ������� ��������� ������ � ������������.
	   virtual void Channel_Get3DPosition() = 0;//  ��������� ������� ������� ��������� ������ � ������������.
	   virtual void Channel_SetVelocity() = 0;// ��������� ����� �������� ����������� ��������� ������ � ������������.
	   virtual void Channel_GetVelocity() = 0;// ��������� ������� �������� ����������� ��������� ������ � ������������.
	   virtual void Channel_SetMinMaxDistance() = 0;// ��������� ����� �������� ������������ � ������������� ���������� ���������� ��������� ������.
	   virtual void Channel_GetMinMaxDistance () = 0;//��������� ������� �������� ������������ � ������������� ���������� ���������� ��������� ������.
	   virtual void Channel_SetConeParameters() = 0;// ��������� ����� ���������� ������ ��������������� ��������� ������.
	   virtual void Channel_GetConeParameters () = 0;//��������� ������� ���������� ������ ��������������� ��������� ������.
	   virtual void Channel_EAX_SetProperties () = 0;//��������� ����� EAX ���������� ��������� ������.
	   virtual void Channel_EAX_GetProperties () = 0;//��������� ������� EAX ���������� ��������� ������.
	   virtual void Channel_ZOOMFX_SetProperties() = 0;// ��������� ����� ZOOMFX ���������� ��������� ������.
	   virtual void Channel_ZOOMFX_GetProperties() = 0;// ��������� ������� ZOOMFX ���������� ��������� ������. 
	   /*
	   //������ �������
	   ChannelGroup_Pause () = 0;//���������/���������� ��������������� ������ �������� �������.
	   ChannelGroup_Stop () = 0;// ��������� ��������������� ������ �������� �������.
	   ChannelGroup_SetVolume() = 0;// ��������� ����� ��������� ������ �������� �������.
	   ChannelGroup_SetFrequency() = 0;// ��������� ����� ������� ������������� ������ �������� �������. 
	   //������
	   SQUALL_Sample_LoadFile () = 0;//�������� ������ �� �����.
	   SQUALL_Sample_UnloadAll () = 0;// �������� ���� ������� �� ��������� ���������.
	   SQUALL_Sample_Unload() = 0;// �������� ���������� ������ �� ��������� ���������.
	   SQUALL_Sample_GetFileLength () = 0;//��������� �������� ����������������� ������, � ��������.
	   SQUALL_Sample_GetFileLengthMs() = 0;// ��������� �������� ����������������� ������, � �������������.
	   SQUALL_Sample_GetFileFrequency() = 0;// ��������� �������� ������� ������������� ������.
	   SQUALL_Sample_SetDefault() = 0;// ��������� ����� ���������� ������ �� ���������.
	   SQUALL_Sample_GetDefault() = 0;// ��������� ������� ���������� ������ �� ���������.
	   SQUALL_Sample_Play () = 0;//�������� ����������� ��������� ������ �� ���������� ������, �������� �� ��������� ������ �� ���������.
	   SQUALL_Sample_PlayEx() = 0;// �������� ����������� ��������� ������ �� ���������� ������.
	   SQUALL_Sample_Play3D () = 0;//�������� ����������������� (�����������) ��������� ������ �� ���������� ������, �������� �� ��������� ������ �� ���������.
	   SQUALL_Sample_Play3DEx () = 0;//�������� ����������������� (�����������) ��������� ������ �� ���������� ������.
	   SQUALL_Sample_Pause () = 0;//���������/���������� ��������������� ���� �������� ������� ������������ ��������� �����.
	   SQUALL_Sample_Stop() = 0;// ��������� ���� �������� ������� ������������ ��������� �����. 
	   //������ �������
	   SQUALL_SampleGroup_Play() = 0;// �������� ����������� ��������� ������ �� ������ �������, �������� �� ��������� ������ �� ���������.
	   SQUALL_SampleGroup_PlayEx () = 0;// �������� ����������� ��������� ������ �� ������ �������.
	   SQUALL_SampleGroup_Play3D() = 0;// �������� ����������������� (�����������) ��������� ������ �� ������ �������, �������� �� ��������� ������ �� ���������.
	   SQUALL_SampleGroup_Play3DEx () = 0;//�������� ����������������� (�����������) ��������� ������ �� ������ �������. 
	   */
};
#endif