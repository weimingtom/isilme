//-----------------------------------------------------------------------------
// ������������ ���� �������� ������� "�����" ������ 1.48
// �������     :
// ����������� : ������������ ����� (�����) E-Mail AT_Marat@list.net
//-----------------------------------------------------------------------------
#ifndef _SQUALL_H_INCLUDED_
#define _SQUALL_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#define IsTrue(r) (r >= 0) ? true : false
#define IsFalse(r) (r < 0) ? true : false

// ������ ������
#define  SQUALL_ERROR_NO_SOUND               -1    // � ������� ��� ��������� ����������
#define  SQUALL_ERROR_MEMORY                 -2    // ������ ��������� ������
#define  SQUALL_ERROR_UNINITIALIZED          -3    // ����� �� ���������������
#define  SQUALL_ERROR_INVALID_PARAM          -4    // ������ ��������� �� ��������
#define  SQUALL_ERROR_CREATE_WINDOW          -5    // ���������� ������� ������� ����
#define  SQUALL_ERROR_CREATE_DIRECT_SOUND    -6    // ������ ��� �������� DirectSound �������
#define  SQUALL_ERROR_CREATE_THREAD          -7    // ������ �������� ������
#define  SQUALL_ERROR_SET_LISTENER_PARAM     -8    // ������ ��������� ���������� ���������
#define  SQUALL_ERROR_GET_LISTENER_PARAM     -9    // ������ ��������� ���������� ���������
#define  SQUALL_ERROR_NO_FREE_CHANNEL        -10   // ������ ��� ���������� ������ ��� ���������������
#define  SQUALL_ERROR_CREATE_CHANNEL         -11   // ������ �������� 3� ������� ��������� ������
#define  SQUALL_ERROR_CHANNEL_NOT_FOUND      -12   // ������ �������� 3� ������� ��������� ������
#define  SQUALL_ERROR_SET_CHANNEL_PARAM      -13   // ������ ���������� ��������� ������
#define  SQUALL_ERROR_GET_CHANNEL_PARAM      -14   // ������ ��������� ������ ��������� ������
#define  SQUALL_ERROR_METHOD                 -15   // ������ ���������� ����� �� ��������������
#define  SQUALL_ERROR_ALGORITHM              -16   // ������ 3D �������� �� ���������������
#define  SQUALL_ERROR_NO_EAX                 -17   // ������ EAX �� ���������������
#define  SQUALL_ERROR_EAX_VERSION            -18   // ������ ������ EAX �� ���������������
#define  SQUALL_ERROR_SET_EAX_PARAM          -19   // ������ ��������� EAX ���������� ���������
#define  SQUALL_ERROR_GET_EAX_PARAM          -20   // ������ ��������� EAX ���������� ���������
#define  SQUALL_ERROR_NO_ZOOMFX              -21   // ������ ZOOMFX �� ��������������
#define  SQUALL_ERROR_SET_ZOOMFX_PARAM       -22   // ������ ��������� ZOOMFX ���������� ������
#define  SQUALL_ERROR_GET_ZOOMFX_PARAM       -23   // ������ ��������� ZOOMFX ���������� ������
#define  SQUALL_ERROR_UNKNOWN                -24   // ����������� ������
#define  SQUALL_ERROR_SAMPLE_INIT            -25   // ������ ������������� �������� ������
#define  SQUALL_ERROR_SAMPLE_BAD             -26   // ������ �����
#define  SQUALL_ERROR_SET_MIXER_PARAM        -27   // ������ ��������� ���������� �������
#define  SQUALL_ERROR_GET_MIXER_PARAM        -28   // ������ ��������� ���������� �������

// ��������� ���������
#define SQUALL_LISTENER_MODE_IMMEDIATE 0           // ��������� ��������������� ����������
#define SQUALL_LISTENER_MODE_DEFERRED  1           // ��������� ��������������� ������ ����� ������ ������ Listener_Update

// ������� ��������� ����������� ����� ��� ���������� ���������
#define SQUALL_ALG_3D_DEFAULT          0           // �������� �� ���������
#define SQUALL_ALG_3D_OFF              1           // 2D ��������
#define SQUALL_ALG_3D_FULL             2           // ����������� 3D ��������
#define SQUALL_ALG_3D_LIGHT            3           // ����������� 3D ��������

// �������� ������ ��� ������ � �������
typedef unsigned int (__cdecl* squall_callback_open_t)      (const char* Name);
typedef int          (__cdecl* squall_callback_read_t)      (unsigned int Handle, void* Buffer, int Size);
typedef int          (__cdecl* squall_callback_seek_t)      (unsigned int Handle, int Position, int SeekMode);
typedef void         (__cdecl* squall_callback_close_t)     (unsigned int Handle);

// �������� ������ ��� ������ � �������
typedef void*        (__cdecl* squall_callback_alloc_t)     (unsigned int Size);
typedef void         (__cdecl* squall_callback_free_t)      (void* Ptr);

// �������� ������ ��� ������ ������������
typedef void         (__cdecl* squall_callback_listener_t)     (void* UserData);
typedef int          (__cdecl* squall_callback_channel_t)      (int ChannelID, void* UserData);
typedef int          (__cdecl* squall_callback_end_channel_t)  (int ChannelID, void* UserData);

// ��������� ��� �������� �������� ���������
typedef struct squall_parameters_s
{
    void*   Window;                                // ���� � �������� ����� ����������� ���������
    int     Device;                                // ����� ���������� ���������������
    int     SampleRate;                            // ������� �������������
    int     BitPerSample;                          // ���������� ��� �� �������
    int     Channels;                              // ������������ ���������� �������
    int     UseHW2D;                               // ������������� ���������� ����������� ��� ���������� �������
    int     UseHW3D;                               // ������������� ���������� ����������� ��� �������� �������
    int     UseAlg;                                // ������������ ���������� ��������
    int     BufferSize;                            // ������ ���������� ������ � �������������
    int     ListenerMode;                          // ���������� ������� ����� ������� ����� ����������� ����������
    float   DistanceFactor;                        // ������ ���������
    float   RolloffFactor;                         // ������ ��������
    float   DopplerFactor;                         // ������ ��������
} squall_parameters_t;

// ��������� ����������� ��������� ����� �� ���������
typedef struct squall_sample_default_s
{
    int     SampleGroupID;                         // �������������� ������ � ������
    int     Priority;                              // ��������� ����� �� ���������
    int     Frequency;                             // ������� ����� �� ���������
    int     Volume;                                // ��������� ����� �� ���������
    int     Pan;                                   // �������� ����� �� ���������
    float   MinDist;                               // ����������� ������� ���������� �� ���������
    float   MaxDist;                               // ������������ ������� ���������� �� ���������
} squall_sample_default_t;

// ��������� ����������� ������� ��������� �������
typedef struct squall_channels_s
{
    int     Play;                                  // ���������� ����������������� ���������� �������
    int     Pause;                                 // ���������� ������� � ����� ���������� �������
    int     Prepare;                               // ���������� �������������� ���������� �������
    int     Play3D;                                // ���������� ����������������� ����������� �������
    int     Pause3D;                               // ���������� ������� � ����� ����������� �������
    int     Prepare3D;                             // ���������� �������������� ����������� �������
} squall_channels_t;

// ��������� ����������� ��������� ���������� ���������������
typedef struct squall_device_caps_s
{
    int     Flags;                                 // ����� ������������ �������� ����������
    int     HardwareChannels;                      // ���������� ���������� �������
    int     Hardware3DChannels;                    // ���������� ���������� 3D �������
} squall_device_caps_t;

// ����� ����������� ����������� ���������� ���������������
#define SQUALL_DEVICE_CAPS_HARDWARE    0x00000001  // ���������� ������������ ���������� ���������� �������
#define SQUALL_DEVICE_CAPS_HARDWARE_3D 0x00000002  // ���������� ������������ ���������� ���������� 3D �������
#define SQUALL_DEVICE_CAPS_EAX10       0x00000004  // ���������� ������������ EAX 1.0
#define SQUALL_DEVICE_CAPS_EAX20       0x00000008  // ���������� ������������ EAX 2.0
#define SQUALL_DEVICE_CAPS_EAX30       0x00000010  // ���������� ������������ EAX 3.0
#define SQUALL_DEVICE_CAPS_ZOOMFX      0x00000100  // ���������� ������������ ZOOMFX

// ����� ����������� ������������ ���������
#define SQUALL_SPEAKER_DEFAULT         0x00000000  // ��������� �� ���������
#define SQUALL_SPEAKER_HEADPHONE       0x00000001  // �������� (�������� ��������)
#define SQUALL_SPEAKER_MONO            0x00000002  // ���� ������� (1.0)
#define SQUALL_SPEAKER_STEREO          0x00000003  // ������ ������� (2.0)
#define SQUALL_SPEAKER_QUAD            0x00000004  // ������ ������� (4.0)
#define SQUALL_SPEAKER_SURROUND        0x00000005  // ������ ������� � ������� ������ �������� (4.1)
#define SQUALL_SPEAKER_5POINT1         0x00000006  // ���� ��������� ������� � ������� ������ �������� (5.1)

// ������ ������
#define SQUALL_CHANNEL_STATUS_NONE     0           // ������ ���
#define SQUALL_CHANNEL_STATUS_PLAY     1           // ����� � ������ ���������������
#define SQUALL_CHANNEL_STATUS_PAUSE    2           // ����� � ������ �����
#define SQUALL_CHANNEL_STATUS_PREPARED 3           // ����� � �������������� ���������

// ��������� ���������� EAX ���������
typedef union squall_eax_listener_s
{
   // ��������� EAX 1.0
   struct
   {
      unsigned long  Environment;
      float          Volume;
      float          DecayTime_sec;
      float          Damping;
   } eax1;
    
   // ��������� EAX 2.0
   struct 
   {
      long           Room;
      long           RoomHF;
      float          RoomRolloffFactor;
      float          DecayTime;
      float          DecayHFRatio;
      long           Reflections;
      float          ReflectionsDelay;
      long           Reverb;
      float          ReverbDelay;
      unsigned long  Environment;
      float          EnvironmentSize;
      float          EnvironmentDiffusion;
      float          AirAbsorptionHF;
      unsigned long  Flags;
   } eax2;

   // ��������� EAX 3.0
   struct
   {
      unsigned long  Environment;
      float          EnvironmentSize;
      float          EnvironmentDiffusion;
      long           Room;
      long           RoomHF;
      long           RoomLF;
      float          DecayTime;
      float          DecayHFRatio;
      float          DecayLFRatio;
      long           Reflections;
      float          ReflectionsDelay;
      float          ReflectionsPan[3];
      long           Reverb;
      float          ReverbDelay;
      float          ReverbPan[3];
      float          EchoTime;
      float          EchoDepth;
      float          ModulationTime;
      float          ModulationDepth;
      float          AirAbsorptionHF;
      float          HFReference;
      float          LFReference;
      float          RoomRolloffFactor;
      unsigned long  Flags;
   } eax3;
} squall_eax_listener_t;

// �������� ������ ��������� � EAX ������� � ������ 2.0
#define SQUALL_EAX_LISTENER_FLAGS_DECAYTIMESCALE          0x00000001
#define SQUALL_EAX_LISTENER_FLAGS_REFLECTIONSSCALE        0x00000002
#define SQUALL_EAX_LISTENER_FLAGS_REFLECTIONSDELAYSCALE   0x00000004
#define SQUALL_EAX_LISTENER_FLAGS_REVERBSCALE             0x00000008
#define SQUALL_EAX_LISTENER_FLAGS_REVERBDELAYSCALE        0x00000010
#define SQUALL_EAX_LISTENER_FLAGS_DECAYHFLIMIT            0x00000020

// �������� ������ ��������� � EAX ������� ������ 3.0
#define SQUALL_EAX_LISTENER_FLAGS_ECHOTIMESCALE           0x00000040
#define SQUALL_EAX_LISTENER_FLAGS_MODULATIONTIMESCALE     0x00000080

// �������� ������ ��������� � EAX ������� � ������ 2.0 �� ���������
#define SQUALL_EAX_LISTENER_FLAGS_DEFAULT                 ( SQUALL_EAX_LISTENER_FLAGS_DECAYTIMESCALE          |   \
                                                            SQUALL_EAX_LISTENER_FLAGS_REFLECTIONSSCALE        |   \
                                                            SQUALL_EAX_LISTENER_FLAGS_REFLECTIONSDELAYSCALE   |   \
                                                            SQUALL_EAX_LISTENER_FLAGS_REVERBSCALE             |   \
                                                            SQUALL_EAX_LISTENER_FLAGS_REVERBDELAYSCALE        |   \
                                                            SQUALL_EAX_LISTENER_FLAGS_DECAYHFLIMIT    )

// ������ ����������������� �������� EAX ���������
#define SQUALL_EAX_OFF              -1
#define SQUALL_EAX_GENERIC           0
#define SQUALL_EAX_PADDEDCELL        1
#define SQUALL_EAX_ROOM              2
#define SQUALL_EAX_BATHROOM          3
#define SQUALL_EAX_LIVINGROOM        4
#define SQUALL_EAX_STONEROOM         5
#define SQUALL_EAX_AUDITORIUM        6
#define SQUALL_EAX_CONCERTHALL       7
#define SQUALL_EAX_CAVE              8
#define SQUALL_EAX_ARENA             9
#define SQUALL_EAX_HANGAR           10
#define SQUALL_EAX_CARPETEDHALLWAY  11
#define SQUALL_EAX_HALLWAY          12
#define SQUALL_EAX_STONECORRIDOR    13
#define SQUALL_EAX_ALLEY            14
#define SQUALL_EAX_FOREST           15
#define SQUALL_EAX_CITY             16
#define SQUALL_EAX_MOUNTAINS        17
#define SQUALL_EAX_QUARRY           18
#define SQUALL_EAX_PLAIN            19
#define SQUALL_EAX_PARKINGLOT       20
#define SQUALL_EAX_SEWERPIPE        21
#define SQUALL_EAX_UNDERWATER       22
#define SQUALL_EAX_DRUGGED          23
#define SQUALL_EAX_DIZZY            24
#define SQUALL_EAX_PSYCHOTIC        25

// C�������� EAX ���������� ������
typedef union squall_eax_channel_s
{
    // EAX 1.0
    struct
    {
        float               Mix;
    } eax1;

    // EAX 2.0
    struct
    {
        long                Direct;
        long                DirectHF;
        long                Room;
        long                RoomHF;
        float               RoomRolloffFactor;
        long                Obstruction;
        float               ObstructionLFRatio;
        long                Occlusion;
        float               OcclusionLFRatio;
        float               OcclusionRoomRatio;
        long                OutsideVolumeHF;
        float               AirAbsorptionFactor;
        unsigned long       Flags;
    } eax2;
    
    //  EAX 3.0
    struct
    {
        long                Direct;
        long                DirectHF;
        long                Room;
        long                RoomHF;
        long                Obstruction;
        float               ObstructionLFRatio;
        long                Occlusion;
        float               OcclusionLFRatio;
        float               OcclusionRoomRatio;
        float               OcclusionDirectRatio;
        long                Exclusion;
        float               ExclusionLFRatio;
        long                OutsideVolumeHF;
        float               DopplerFactor;
        float               RolloffFactor;
        float               RoomRolloffFactor;
        float               AirAbsorptionFactor;
        unsigned long       Flags;
    } eax3;
} squall_eax_channel_t;

// �������� ������ ������ � EAX ������� � ������ 2.0
#define SQUALL_EAX_CHANNEL_FLAGS_DIRECTHFAUTO             0x00000001
#define SQUALL_EAX_CHANNEL_FLAGS_ROOMAUTO                 0x00000002
#define SQUALL_EAX_CHANNEL_FLAGS_ROOMHFAUTO               0x00000004
#define SQUALL_EAX_CHANNEL_FLAGS_DEFAULT                  (SQUALL_EAX_CHANNEL_FLAGS_DIRECTHFAUTO |   \
                                                            SQUALL_EAX_CHANNEL_FLAGS_ROOMAUTO     |   \
                                                            SQUALL_EAX_CHANNEL_FLAGS_ROOMHFAUTO   )
// ��������� ZOOMFX ���������� ��������� �����
typedef struct squall_zoomfx_channel_s
{
   float    Min[3];
   float    Max[3];
   float    Front[3];
   float    Top[3];
   long     MacroFX;
} squall_zoomfx_channel_t;

#ifndef _USRDLL
class Squall
{
   public:
#else
#define DLL_API __declspec(dllexport)
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//                 ������ ������������� / ������������
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// ������������� �������� ������� �����
// �� �����    :  SystemParam -  ��������� �� ��������� � �����������
//                               ��������� ��������� ��� �������������.
//                               ���� �������� ����� ����� 0 �� ��������
//                               ��������� ������� ��������� ������� �
//                               ���������� �����������:
//                               Window         = 0     (������� ���� ����)
//                               Device         = 0     (���������� �� ���������)
//                               SampleRate     = 44100
//                               BitPerSample   = 16
//                               Channels       = 16
//                               UseHW2D        = true  (������������)
//                               UseHW3D        = true  (������������)
//                               UseAlg         = 0     (�������� �� ���������)
//                               BufferSize     = 200
//                               ListenerMode   = 0     (����������� ����������)
//                               DistanceFactor = 1.0f
//                               RolloffFactor  = 1.0f
//                               DopplerFactor  = 1.0f
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Init(squall_parameters_t* SystemParam);
#else
DLL_API int SQUALL_Init(squall_parameters_t* SystemParam);
#endif

//-----------------------------------------------------------------------------
// ������������ ������� �������� �������� ��������
// �� �����    :  *
// �� ������   :  *
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   void Free(void);
#else
DLL_API void SQUALL_Free(void);
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//                  ������ ��� ���������� ����������
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// ���������/���������� ����� ���� �������� �������
// �� �����    :  Pause -  ���� ���������/���������� �����
//                         �������� ����� ��������� ��������� ��������
//                         true  - �������� �����
//                         false - ��������� �����
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Pause(int Pause);
#else
DLL_API int SQUALL_Pause(int Pause);
#endif

//-----------------------------------------------------------------------------
// ��������� ���� �������� �������
// �� �����    :  *
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Stop(void);
#else
DLL_API int SQUALL_Stop(void);
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//                    ������ ��� ��������� ���������
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// ��������� ������ ���������� ���������������
// �� �����    :  Num   -  ����� ������ ���������� ���������������, �������� 
//                         ��������� ������ ���� � �������� �� 0 �� ��������
#ifndef _USRDLL
//                         ����������� � ������� ������ GetNumDevice.
#else
//                         ����������� � ������� ������ SQUALL_GetNumDevice.
#endif
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int SetDevice(int Num);
#else
DLL_API int SQUALL_SetDevice(int Num);
#endif

//-----------------------------------------------------------------------------
// ��������� ������ �������� ���������� ���������������
// �� �����    :  *
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//                � ������ ��������� ������ ��������� �������� ����� ��������
//                ���������� ���������������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int GetDevice(void);
#else
DLL_API int SQUALL_GetDevice(void);
#endif

//-----------------------------------------------------------------------------
// ���������/���������� ������������� ���������� ����������� �����
// �� �����    :  UseHW2D  -  ���� ������������ ������������� ����������
//                            ����������� ���������� �������� �������,
//                            �������� ����� ��������� ��������� ��������:
//                            true   - ������������ ���������� �����������
//                            false  - �� ������������ ���������� �����������
//                UseHW3D  -  ���� ������������ ������������� ����������
//                            ����������� ����������� �������� �������
//                            �������� ����� ��������� ��������� ��������:
//                            true   - ������������ ���������� �����������
//                            false  - �� ������������ ���������� �����������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int SetHardwareAcceleration(int UseHW2D, int UseHW3D);
#else
DLL_API int SQUALL_SetHardwareAcceleration(int UseHW2D, int UseHW3D);
#endif

//-----------------------------------------------------------------------------
// ��������� ������� �������� ������������� ���������� ����������� �����
// �� �����    :  UseHW2D  -  ��������� �� ���������� � ������� ����� ���������
//                            ������� �������� ������������� ����������
//                            ����������� ��� ���������� �������� �������
//                UseHW3D  -  ��������� �� ���������� � ������� ����� ���������
//                            ������� �������� ������������� ����������
//                            ����������� ��� ����������� �������� �������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int GetHardwareAcceleration(int* UseHW2D, int* UseHW3D);
#else
DLL_API int SQUALL_GetHardwareAcceleration(int* UseHW2D, int* UseHW3D);
#endif

//-----------------------------------------------------------------------------
// ��������� ������ ���������
// �� �����    :  Mode  -  ������������� ������, �������� ����� ���������
//                         ��������� ��������:
//                         SQUALL_SPEAKER_DEFAULT   - ��������� �� ���������
//                         SQUALL_SPEAKER_HEADPHONE - �������� (�������� ��������)
//                         SQUALL_SPEAKER_MONO      - ���� ������� (1.0)
//                         SQUALL_SPEAKER_STEREO    - ������ ������� (2.0)
//                         SQUALL_SPEAKER_QUAD      - ������ ������� (4.0)
//                         SQUALL_SPEAKER_SURROUND  - ������ ������� � �������
//                                                    ������ �������� (4.1)
//                         SQUALL_SPEAKER_5POINT1   - ���� ��������� ������� �
//                                                    ������� ������ �������� (5.1)
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int SetSpeakerMode(int Mode);
#else
DLL_API int SQUALL_SetSpeakerMode(int Mode);
#endif

//-----------------------------------------------------------------------------
//	��������� �������� ������ ���������
//	�� �����    :  *
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//                � ������ ��������� ������ ��������� �������� ����� ��������
//                ������ ���������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int GetSpeakerMode(void);
#else
DLL_API int SQUALL_GetSpeakerMode(void);
#endif

//-----------------------------------------------------------------------------
// ��������� ��������� ������� ����������� �����
// �� �����    :  Algoritm -  ��� ������������ ��������� ������� �����
//                            �������� ����� ��������� ��������� ��������:
//                            SQUALL_ALG_3D_DEFAULT - �������� �� ���������
//                            SQUALL_ALG_3D_OFF     - 2D ��������
//                            SQUALL_ALG_3D_FULL    - ����������� 3D ��������
//                            SQUALL_ALG_3D_LIGHT   - ����������� 3D ��������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Set3DAlgorithm(int Algorithm);
#else
DLL_API int SQUALL_Set3DAlgorithm(int Algorithm);
#endif

//-----------------------------------------------------------------------------
// ��������� �������� ��������� ������� ����������� �����
// �� �����    :  *
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//                � ������ ��������� ������ ��������� �������� ����� ��������
//                ��������� ������� ����������� �����, ��������� �����
//                ��������� ��������� ��������:
//                SQUALL_ALG_3D_DEFAULT - �������� �� ���������
//                SQUALL_ALG_3D_OFF     - 2D ��������
//                SQUALL_ALG_3D_FULL    - ����������� 3D ��������
//                SQUALL_ALG_3D_LIGHT   - ����������� 3D ��������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Get3DAlgorithm(void);
#else
DLL_API int SQUALL_Get3DAlgorithm(void);
#endif

//-----------------------------------------------------------------------------
// ��������� ������ ������� ��������� ������ � ������������
// �� �����    :  BufferSize  -  ����� ������ ��������� ������, � ������������
//                               �������� ������ ������ � �������� �� 200
//                               �� 5000
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int SetBufferSize(int BufferSize);
#else
DLL_API int SQUALL_SetBufferSize(int BufferSize);
#endif

//-----------------------------------------------------------------------------
// ��������� �������� ������� ��������� ������ � ������������
// �� �����    :  *
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//                � ������ ��������� ������ ��������� �������� ������� ������
//                ��������� ������ � ������������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int GetBufferSize(void);
#else
DLL_API int SQUALL_GetBufferSize(void);
#endif

//-----------------------------------------------------------------------------
// ��������� ������� ������� ������ � �������
// �� �����    :  UserAlloc   -  ��������� �� ������� ����� ��������� ������
//                UserFree    -  ��������� �� ������� ����� ������������ ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Squall::SetMemoryCallbacks(squall_callback_alloc_t UserAlloc, squall_callback_free_t UserFree);
#else
DLL_API int SQUALL_SetMemoryCallbacks(squall_callback_alloc_t UserAlloc, squall_callback_free_t UserFree);
#endif

//-----------------------------------------------------------------------------
// ��������� ������� ������� ��� ������ � �������
// �� �����    :  UserOpen    -  ��������� �� ������� ����� �������� ������
//                UserSeek    -  ��������� �� ������� ����� ����������������
//                               � �������� �����
//                UserRead    -  ��������� �� ������� ����� ������ ������ ��
//                               ��������� �����
//                UserClose   -  ��������� �� ������� ����� �������� ���������
//                               �����
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Squall::SetFileCallbacks(squall_callback_open_t UserOpen, squall_callback_seek_t UserSeek, squall_callback_read_t UserRead, squall_callback_close_t UserClose);
#else
DLL_API int SQUALL_SetFileCallbacks(squall_callback_open_t UserOpen, squall_callback_seek_t UserSeek, squall_callback_read_t UserRead, squall_callback_close_t UserClose);
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//              ������ ��� ��������� ���������� � �������
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// ��������� ���������� ��������� ��������������� �����
// �� �����    :  *
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������.
//                � ������ ��������� ������ ��������� �������� ����������
//                ��������� ��������������� � �������. ���� � ������� ���
//                ��������� ��������������� ��������� ����� ����� 0.
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int GetNumDevice(void);
#else
DLL_API int SQUALL_GetNumDevice(void);
#endif

//-----------------------------------------------------------------------------
// ��������� ����� ���������� �� ��������� ������
// �� �����    :  Num      -  ����� ����������, �������� ��������� ������ ����
//                            � �������� �� 0 �� �������� ����������� � �������
#ifndef _USRDLL
//                            ������ GetNumDevice.
#else
//                            ������ SQUALL_GetNumDevice.
#endif
//                Buffer   -  ��������� �� ����� ���� ����� ��������� ���
//                            ���������� ���������������
//                Size     -  ������ ������������ ������ � ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int GetDeviceName(int Num, char* Buffer, int Size);
#else
DLL_API int SQUALL_GetDeviceName(int Num, char* Buffer, int Size);
#endif

//-----------------------------------------------------------------------------
// ��������� ������� ���������� ��������������� �� ��������� ������
// �� �����    :  Num   -  ����� ����������, �������� ��������� ������ ���� �
//                         �������� �� 0 �� �������� ����������� � �������
#ifndef _USRDLL
//                         ������ GetNumDevice.
#else
//                         ������ SQUALL_GetNumDevice.
#endif
//                Caps  -  ��������� �� ��������� � ������� ����� ���������
//                         �������� ���������� ���������������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int GetDeviceCaps(int Num, squall_device_caps_t* Caps);
#else
DLL_API int SQUALL_GetDeviceCaps(int Num, squall_device_caps_t* Caps);
#endif

//-----------------------------------------------------------------------------
// ��������� ������������ ������ EAX ����������
// �� �����    :  *
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//                � ������ ��������� ������ ��������� �������� �����������
//                ��������� ������ EAX
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int GetEAXVersion(void);
#else
DLL_API int SQUALL_GetEAXVersion(void);
#endif

//-----------------------------------------------------------------------------
// ��������� ���������� � �������
// �� �����    :  Info  -  ��������� �� ��������� � ������� ����� ���������
//                         ���������� � ��������� �������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int GetChannelsInfo(squall_channels_t* Info);
#else
DLL_API int SQUALL_GetChannelsInfo(squall_channels_t* Info);
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//                    ������ ��� ������ �� ����������
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// ��������� ����� ���������� ���������
// �� �����    :  Position -  ��������� �� ��������� � ������ ������������
//                            ������� ���������. � ������ ���� ������� ���������
//                            �������� �� �����, �� ������ �������� ������
//                            ��������� 0 
//                Front    -  ��������� �� ��������� � ����� �������� 
//                            ������������ ����������� ���������. � ������ ����
//                            ������ ������������ ����������� ��������� ��������
//                            �� �����, �� ������ �������� ������ ��������� 0
//                Top      -  ��������� �� ��������� � ����� ��������
//                            ������������� ����������� ���������. � ������ ����
//                            ������ ������������� ����������� �������� �� �����,
//                            �� ������ �������� ������ ��������� 0
//                Velocity -  ��������� �� ��������� � ����� ��������
//                            �������� ����������� ���������. � ������ ����
//                            �������� ����������� ��������� �������� �� �����,
//                            �� ������ �������� ������ ��������� 0.
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Listener_SetParameters(float* Position, float* Front, float* Top, float* Velocity);
#else
DLL_API int SQUALL_Listener_SetParameters(float* Position, float* Front, float* Top, float* Velocity);
#endif

//-----------------------------------------------------------------------------
// ��������� ������� ���������� ���������
// �� �����    :  Position -  ��������� �� ��������� � ������� ����� 
//                            ��������� ������� ���������� ���������. � ������
//                            ���� �������� ��������� ��������� �� ���������
//                            ����������, �� ������ �������� ������ ��������� 0.
//                Front    -  ��������� �� ��������� � ������� �����
//                            ��������� ������� ������ ������������ 
//                            ����������� ���������. � ������ ���� ������
//                            ������������ ����������� ��������� �� ���������
//                            ����������, �� ������ �������� ������ ��������� 0.
//                Top      -  ��������� �� ��������� � ������� �����
//                            ��������� ������� ������ ������������� 
//                            ����������� ���������. � ������ ���� ������
//                            ������������� ����������� ��������� �� ���������
//                            ����������, �� ������ �������� ������ ��������� 0.
//                Velocity -  ��������� �� ��������� � ������� �����
//                            ��������� ������� ������ �������� �����������
//                            ���������. � ������ ���� �������� �����������
//                            ��������� �� ��������� ����������, �� ������
//                            �������� ������ ��������� 0.
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Listener_GetParameters(float* Position, float* Front, float* Top, float* Velocity);
#else
DLL_API int SQUALL_Listener_GetParameters(float* Position, float* Front, float* Top, float* Velocity);
#endif

//-----------------------------------------------------------------------------
// ��������� ����� �������� ����������� ���������
// �� �����    :  Velocity -  ��������� �� ��������� � ����� �������� 
//                            �������� ����������� ���������.
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Listener_SetVelocity(float* Velocity);
#else
DLL_API int SQUALL_Listener_SetVelocity(float* Velocity);
#endif

//-----------------------------------------------------------------------------
// ��������� ������� �������� ����������� ���������
// �� �����    :  Velocity - ��������� �� ��������� � ������� �����
//                           ��������� ������� ������ �������� �����������
//                           ���������.
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Listener_GetVelocity(float* Velocity);
#else
DLL_API int SQUALL_Listener_GetVelocity(float* Velocity);
#endif

//-----------------------------------------------------------------------------
// ��������� ����� ������� ��������� � ������������
// �� �����    :  Position -  ��������� �� ��������� � ����� ��������
//                            �������� ����������� ���������.
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Listener_SetPosition(float* Position);
#else
DLL_API int SQUALL_Listener_SetPosition(float* Position);
#endif

//-----------------------------------------------------------------------------
// ��������� ������� ������� ��������� � ������������
// �� �����    :  Position -  ��������� �� ��������� � ������� �����
//                            ��������� ������� ������ �������� �����������
//                            ���������.
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Listener_GetPosition(float* Position);
#else
DLL_API int SQUALL_Listener_GetPosition(float* Position);
#endif

//-----------------------------------------------------------------------------
// ��������� ������ ������������ �������������� ���������
// �� �����    :  DistanceFactor -  ����� ����������� �������������� ���������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Listener_SetDistanceFactor(float DistanceFactor);
#else
DLL_API int SQUALL_Listener_SetDistanceFactor(float DistanceFactor);
#endif

//-----------------------------------------------------------------------------
// ��������� �������� ������������ �������������� ���������
// �� �����    :  DistanceFactor -  ��������� �� ���������� � ������� �����
//                                  ��������� ������� ����������� 
//                                  �������������� ���������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Listener_GetDistanceFactor(float* DistanceFactor);
#else
DLL_API int SQUALL_Listener_GetDistanceFactor(float* DistanceFactor);
#endif

//-----------------------------------------------------------------------------
// ��������� ������ ������������ ��������� ����� � ����������� �� ���������
// �� �����    :  RolloffFactor  -  ����� ����������� �������������� ���������
//                                  �����,  �������� ��������� ������ ����
//                                  � �������� �� 0.1f �� 10.0f
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Listener_SetRolloffFactor(float RolloffFactor);
#else
DLL_API int SQUALL_Listener_SetRolloffFactor(float RolloffFactor);
#endif

//-----------------------------------------------------------------------------
// ��������� �������� ������������ ��������� ����� � ����������� �� ���������
// �� �����    :  RolloffFactor  -  ��������� �� ���������� � ������� �����
//                                  ��������� ������� ����������� ��������������
//                                  ��������� �����
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Listener_GetRolloffFactor(float* RolloffFactor);
#else
DLL_API int SQUALL_Listener_GetRolloffFactor(float* RolloffFactor);
#endif

//-----------------------------------------------------------------------------
// ��������� ������ ������������ ������� ��������
// �� �����    :  DopplerFactor  -  ����� ����������� ������� ��������, ��������
//                                  ��������� ������ ���� � �������� �� 0.1f
//                                  �� 10.0f
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Listener_SetDopplerFactor(float DopplerFactor);
#else
DLL_API int SQUALL_Listener_SetDopplerFactor(float DopplerFactor);
#endif

//-----------------------------------------------------------------------------
// ��������� �������� ������������ ������� ��������
// �� �����    :  DopplerFactor  -  ��������� �� ���������� � ������� �����
//                                  ��������� ������� ����������� �������
//                                  ��������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Listener_GetDopplerFactor(float* DopplerFactor);
#else
DLL_API int SQUALL_Listener_GetDopplerFactor(float* DopplerFactor);
#endif

//-----------------------------------------------------------------------------
// ���������� ���������� ��������
// �� �����    :  *
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
// ����������  :  ������ ����� ����� ����� ��������� ������ � ��� ������ �����
//                ��������� �������� �� �������������� ���������� ����������
//                ��������. �� ���� ��� ������������� ��������� ���������
//                ��������� � ����� SQUALL_LISTENER_MODE_DEFERRED
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Listener_Update(void);
#else
DLL_API int SQUALL_Listener_Update(void);
#endif

//-----------------------------------------------------------------------------
// ��������� ����������������� �������� ���������
// �� �����    :  Preset   -  ����� ������������������ ��������
//                            �������� ����� ��������� ��������� ��������:
//                            SQUALL_EAX_OFF
//                            SQUALL_EAX_GENERIC
//                            SQUALL_EAX_PADDEDCELL
//                            SQUALL_EAX_ROOM
//                            SQUALL_EAX_BATHROOM
//                            SQUALL_EAX_LIVINGROOM
//                            SQUALL_EAX_STONEROOM
//                            SQUALL_EAX_AUDITORIUM
//                            SQUALL_EAX_CONCERTHALL
//                            SQUALL_EAX_CAVE
//                            SQUALL_EAX_ARENA
//                            SQUALL_EAX_HANGAR
//                            SQUALL_EAX_CARPETEDHALLWAY
//                            SQUALL_EAX_HALLWAY
//                            SQUALL_EAX_STONECORRIDOR
//                            SQUALL_EAX_ALLEY
//                            SQUALL_EAX_FOREST
//                            SQUALL_EAX_CITY
//                            SQUALL_EAX_MOUNTAINS
//                            SQUALL_EAX_QUARRY
//                            SQUALL_EAX_PLAIN
//                            SQUALL_EAX_PARKINGLOT
//                            SQUALL_EAX_SEWERPIPE
//                            SQUALL_EAX_UNDERWATER
//                            SQUALL_EAX_DRUGGED
//                            SQUALL_EAX_DIZZY
//                            SQUALL_EAX_PSYCHOTIC
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Listener_EAX_SetPreset(int Preset);
#else
DLL_API int SQUALL_Listener_EAX_SetPreset(int Preset);
#endif

//-----------------------------------------------------------------------------
// ��������� ����� EAX ���������� ���������
// �� �����    :  Version     -  ����� ������ EAX ����������
//                Properties  -  ��������� �� ��������� � ������ EAX �����������
//                               ���������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Listener_EAX_SetProperties(int Version, squall_eax_listener_t* Properties);
#else
DLL_API int SQUALL_Listener_EAX_SetProperties(int Version, squall_eax_listener_t* Properties);
#endif

//-----------------------------------------------------------------------------
// ��������� ������� EAX ���������� ���������
// �� �����    :  Version     -  ����� ������ EAX ����������
//                Properties  -  ��������� �� ��������� ���� ���� ���������
//                               ������� EAX ��������� ���������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Listener_EAX_GetProperties(int Version, squall_eax_listener_t* Properties);
#else
DLL_API int SQUALL_Listener_EAX_GetProperties(int Version, squall_eax_listener_t* Properties);
#endif

//-----------------------------------------------------------------------------
// ��������� ����������� ���������
// �� �����    :  Worker      -  ��������� �� ���������� ���������, � ������
//                               ���� �������� ����� 0, ���������� ����������
//                               ����� ������.
//                Param       -  ��������� �� ������ ������������, � ������
//                               ������ ������������ ���, �� ������ ��������
//                               ����� ��������� 0
//                UpdateTime  -  ���������� ������� ����� ������� �����
//                               �������� ���������� �������� ������ ������
//                               � �������� �� 1 �� 5000
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Listener_SetWorker(squall_callback_listener_t Worker, void* Param, unsigned int UpdateTime);
#else
DLL_API int SQUALL_Listener_SetWorker(squall_callback_listener_t Worker, void* Param, unsigned int UpdateTime);
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//                   ����� ������ ��� ������ � ��������
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// ������ ��������������� ��������������� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_Start(int ChannelID);
#else
DLL_API int SQUALL_Channel_Start(int ChannelID);
#endif

//-----------------------------------------------------------------------------
// ���������/���������� ����� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//                Pause       -  ���� ���������/���������� �����, �������� �����
//                               ��������� ��������� ��������:
//                               true  - �������� �����
//                               false - ��������� �����
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_Pause(int ChannelID, int Pause);
#else
DLL_API int SQUALL_Channel_Pause(int ChannelID, int Pause);
#endif

//-----------------------------------------------------------------------------
// ��������� ��������� ������ �� ��������������
// �� �����    :  ChannelID   -  ������������� ��������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_Stop(int ChannelID);
#else
DLL_API int SQUALL_Channel_Stop(int ChannelID);
#endif

//-----------------------------------------------------------------------------
// ��������� ������� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//                � ������ ��������� ������ ��������� �������� ������ ������,
//                ��������� ����� ��������� ��������� ��������:
//                SQUALL_CHANNEL_STATUS_NONE       -  ��������� ������ � �����
//                                                    ��������������� ���
//                SQUALL_CHANNEL_STATUS_PLAY       -  �������� �����
//                                                    ���������������
//                SQUALL_CHANNEL_STATUS_PAUSE      -  �������� ����� ���������
//                                                    � ������ �����
//                SQUALL_CHANNEL_STATUS_PREPARED   -  �������� �����
//                                                    �����������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_Status(int ChannelID);
#else
DLL_API int SQUALL_Channel_Status(int ChannelID);
#endif

//-----------------------------------------------------------------------------
// ��������� ������ ������ ��������� ��������� ������ � ���������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//                Volume      -  �������� ������ ��������� � ���������,
//                               �������� ���������� ������ ���� � ��������
//                               �� 0 �� 100
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_SetVolume(int ChannelID, int Volume);
#else
DLL_API int SQUALL_Channel_SetVolume(int ChannelID, int Volume);
#endif

//-----------------------------------------------------------------------------
// ��������� �������� ������ ��������� ��������� ������ � ���������
// �� �����    :  ChannelID   -  ������������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//                � ������ ��������� ������ ��������� �������� ������� ��������
//                ��������� ������ � ���������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_GetVolume(int ChannelID);
#else
DLL_API int SQUALL_Channel_GetVolume(int ChannelID);
#endif

//-----------------------------------------------------------------------------
// �������� ����� ������� ������������� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//                Frequency   -  ����� �������� ������� �������������, ��������
//                               ��������� ������ ���� � �������� �� 100 ����
//                               �� 1000000 ����
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_SetFrequency(int ChannelID, int Frequency);
#else
DLL_API int SQUALL_Channel_SetFrequency(int ChannelID, int Frequency);
#endif

//-----------------------------------------------------------------------------
// ��������� ������� ������� ������������� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//                � ������ ��������� ������ ��������� �������� ������� ��������
//                ������� ������������� ��������� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_GetFrequency(int ChannelID);
#else
DLL_API int SQUALL_Channel_GetFrequency(int ChannelID);
#endif

//-----------------------------------------------------------------------------
// ��������� ����� ������� ��������������� ��������� ������ � �������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//                Position    -  ����� �������� ������� ���������������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_SetPlayPosition(int ChannelID, int Position);
#else
DLL_API int SQUALL_Channel_SetPlayPosition(int ChannelID, int Position);
#endif

//-----------------------------------------------------------------------------
// ��������� ������� ������� ��������������� ��������� ������ � �������
// �� �����    :  ChannelID   -  ������������� ��������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//                � ������ ��������� ������ ��������� �������� ������� �������
//                ���������������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_GetPlayPosition(int ChannelID);
#else
DLL_API int SQUALL_Channel_GetPlayPosition(int ChannelID);
#endif

//-----------------------------------------------------------------------------
// ��������� ����� ������� ��������������� ��������� ������ � �������������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//                Position    -  ����� �������� ������� ���������������,
//                               � �������������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_SetPlayPositionMs(int ChannelID, int Position);
#else
DLL_API int SQUALL_Channel_SetPlayPositionMs(int ChannelID, int Position);
#endif

//-----------------------------------------------------------------------------
// ��������� ������� ������� ��������������� ��������� ������ � �������������
// �� �����    :  ChannelID   -  ������������� ��������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//                � ������ ��������� ������ ��������� �������� ������� �������
//                ���������������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_GetPlayPositionMs(int ChannelID);
#else
DLL_API int SQUALL_Channel_GetPlayPositionMs(int ChannelID);
#endif

//-----------------------------------------------------------------------------
// ��������� ����������� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//                Worker      -  ��������� �� ���������� ��������� ������
//                Param       -  ��������� �� ������ ������������, � ������
//                               ���� ������ ������������ ���, �������� �����
//                               ��������� 0
//                UpdateTime  -  ���������� ������� � ������������� �����
//                               ������� ����� �������� ����������, ��������
//                               ��������� ������ ���� � �������� �� 1 �� 5000
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_SetWorker(int ChannelID, squall_callback_channel_t Worker, void* Param, unsigned int UpdateTime);
#else
DLL_API int SQUALL_Channel_SetWorker(int ChannelID, squall_callback_channel_t Worker, void* Param, unsigned int UpdateTime);
#endif

//-----------------------------------------------------------------------------
// ��������� ����������� ��������� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//                Worker      -  ��������� �� ���������� ��������� ������
//                Param       -  ��������� �� ������ ������������, � ������
//                               ���� ������ ������������ ���, �������� �����
//                               ��������� 0
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Channel_SetEndWorker(int ChannelID, squall_callback_end_channel_t Worker, void* Param);
#else
DLL_API int SQUALL_Channel_SetEndWorker(int ChannelID, squall_callback_end_channel_t Worker, void* Param);
#endif

//-----------------------------------------------------------------------------
// ��������� ����� ������ ��������� ��������� ������ � �������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//                Start       -  ��������� ������� ���������, � ��������
//                End         -  �������� ������� ���������, � ��������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_SetFragment(int ChannelID, int Start, int End);
#else
DLL_API int SQUALL_Channel_SetFragment(int ChannelID, int Start, int End);
#endif

//-----------------------------------------------------------------------------
// ��������� ������� ������ ��������� ��������� ������ � �������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//                Start       -  ��������� �� ���������� � ������� �����
//                               ��������� ��������� ������� ��������� �
//                               ��������
//                End         -  ��������� �� ���������� � ������� �����
//                               ��������� �������� ������� ���������
//                               � ��������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_GetFragment(int ChannelID, int* Start, int* End);
#else
DLL_API int SQUALL_Channel_GetFragment(int ChannelID, int* Start, int* End);
#endif

//-----------------------------------------------------------------------------
// ��������� ����� ������ ��������� ��������� ������ � �������������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//                Start       -  ��������� ������� ���������, ������� �
//                               �������������
//                End         -  �������� ������� ���������, ������� �
//                               �������������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_SetFragmentMs(int ChannelID, int Start, int End);
#else
DLL_API int SQUALL_Channel_SetFragmentMs(int ChannelID, int Start, int End);
#endif

//-----------------------------------------------------------------------------
// ��������� ������� ������ ��������� ��������� ������ � �������������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//                Start       -  ��������� �� ���������� � ������� �����
//                               ��������� ��������� ������� ���������
//                               � �������������
//                End         -  ��������� �� ���������� � ������� �����
//                               ��������� �������� ������� ���������
//                               � �������������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_GetFragmentMs(int ChannelID, int* Start, int* End);
#else
DLL_API int SQUALL_Channel_GetFragmentMs(int ChannelID, int* Start, int* End);
#endif

//-----------------------------------------------------------------------------
// ��������� ����������������� �������� �������� ������ � �������
// �� �����    :  ChannelID   -  ������������� ��������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//                � ������ ��������� ������ ��������� �������� �����������������
//                �������� ������ � �������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_GetLength(int ChannelID);
#else
DLL_API int SQUALL_Channel_GetLength(int ChannelID);
#endif

//-----------------------------------------------------------------------------
// ��������� ����������������� �������� �������� ������ � �������������
// �� �����    :  ChannelID   -  ������������� ��������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//                � ������ ��������� ������ ��������� �������� �����������������
//                �������� ������ � ������������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_GetLengthMs(int ChannelID);
#else
DLL_API int SQUALL_Channel_GetLengthMs(int ChannelID);
#endif

//-----------------------------------------------------------------------------
// ��������� ������ ���������� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//                Priority    -  ����� ��������� ������, �������� ���������
//                               ������ ���� � �������� �� 0 (����� ������
//                               ���������) �� 65535 (����� ������ ���������)
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_SetPriority(int ChannelID, int Priority);
#else
DLL_API int SQUALL_Channel_SetPriority(int ChannelID, int Priority);
#endif

//-----------------------------------------------------------------------------
// ��������� �������� ���������� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//                � ������ ��������� ������ ��������� �������� ���������
//                ��������� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_GetPriority(int ChannelID);
#else
DLL_API int SQUALL_Channel_GetPriority(int ChannelID);
#endif

//-----------------------------------------------------------------------------
// ��������� �������� �������� ����� ������������� ��������������� ���������
// ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//                � ������ ��������� ������ ��������� �������� ������� ��������
//                ����� ������������� ��������������� ������, ��������� �����
//                ��������� ��������� ��������:
//                true  -  �������� ����� ��������������� ����������
//                false -  �������� ����� ��������������� ���� ���
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_GetLoop(int ChannelID);
#else
DLL_API int SQUALL_Channel_GetLoop(int ChannelID);
#endif

//-----------------------------------------------------------------------------
// ��������� ������ �������� ����� ������������� ��������������� ���������
// ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//                Loop        -  ���� ������������� ������, �������� ��������
//                               ����� ��������� ��������� ��������:
//                               true  -  ����������� ��������������� ���������
//                                        ������
//                               false -  ��������������� ��������� ������ ����
//                                        ���
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_SetLoop(int ChannelID, int Loop);
#else
DLL_API int SQUALL_Channel_SetLoop(int ChannelID, int Loop);
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//                ������ ��� ������ � ����������� ��������
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// ��������� ����� �������� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//                Pan         -  ����� �������� ��������, �������� ���������
//                               ������� ���� � �������� �� 0 (������������
//                               �������� ������ ������� �����) �� 100
//                               (������������ �������� ������ ������� ������)
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
// ����������  :  ������ ����� �� �������� � ������������ ��������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_SetPan(int ChannelID, int Pan);
#else
DLL_API int SQUALL_Channel_SetPan(int ChannelID, int Pan);
#endif

//-----------------------------------------------------------------------------
// ��������� ������� �������� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//                � ������ ��������� ������ ��������� �������� ������� ��������
//                �������� ������
// ����������  :  ������ ����� �� �������� � ������������ ��������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_GetPan(int ChannelID);
#else
DLL_API int SQUALL_Channel_GetPan(int ChannelID);
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//                ������ ��� ������ � ������������ ��������
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// ��������� ����� ���������� ������� ��������� ������ � ������������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//                Position    -  ��������� �� ��������� � ������ ������������
//                               ������ � ������������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
// ����������  :  ������ ����� �� �������� � ����������� ��������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_Set3DPosition(int ChannelID, float* Position);
#else
DLL_API int SQUALL_Channel_Set3DPosition(int ChannelID, float* Position);
#endif

//-----------------------------------------------------------------------------
// ��������� ������� ���������� ������� ��������� ������ � ������������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//                Position    -  ��������� �� ��������� � ������� �����
//                               ��������� ������� ���������� ������� ���������
//                               ������ � ������������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
// ����������  :  ������ ����� �� �������� � ����������� ��������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_Get3DPosition(int ChannelID, float* Position);
#else
DLL_API int SQUALL_Channel_Get3DPosition(int ChannelID, float* Position);
#endif

//-----------------------------------------------------------------------------
// ��������� ����� �������� ����������� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//                Velocity    -  ��������� �� ��������� � ����� ��������
//                               �������� ����������� ��������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
// ����������  :  ������ ����� �� �������� � ����������� ��������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_SetVelocity(int ChannelID, float* Velocity);
#else
DLL_API int SQUALL_Channel_SetVelocity(int ChannelID, float* Velocity);
#endif

//-----------------------------------------------------------------------------
// ��������� ������� �������� ����������� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//                Velocity    -  ��������� �� ��������� � ������� �����
//                               ��������� ������� �������� ������� ��������
//                               ��������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
// ����������  :  ������ ����� �� �������� � ����������� ��������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_GetVelocity(int ChannelID, float* Velocity);
#else
DLL_API int SQUALL_Channel_GetVelocity(int ChannelID, float* Velocity);
#endif

//-----------------------------------------------------------------------------
// ��������� ������ ������������ � ������������� ���������� ����������
// ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//                MinDist     -  ����� ����������� ���������� ����������
//                               �������� ��������� ������ ���� � ��������
//                               �� 0.01f �� 1000000000.0f
//                MaxDist     -  ����� ������������ ���������� ����������
//                               �������� ��������� ������ ���� � ��������
//                               �� 0.01f �� 1000000000.0f
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
// ����������  :  ������ ����� �� �������� � ����������� ��������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_SetMinMaxDistance(int ChannelID, float MinDist, float MaxDist);
#else
DLL_API int SQUALL_Channel_SetMinMaxDistance(int ChannelID, float MinDist, float MaxDist);
#endif

//-----------------------------------------------------------------------------
// ��������� �������� ������������ ��������� ���������� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//                MinDist     -  ��������� �� ���������� � ������� �����
//                               ��������� ������� ����������� ���������
//                               ����������
//                MinDist     -  ��������� �� ���������� � ������� �����
//                               ��������� ������� ������������ ���������
//                               ����������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
// ����������  :  ������ ����� �� �������� � ����������� ��������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_GetMinMaxDistance(int ChannelID, float* MinDist, float* MaxDist);
#else
DLL_API int SQUALL_Channel_GetMinMaxDistance(int ChannelID, float* MinDist, float* MaxDist);
#endif

//-----------------------------------------------------------------------------
// ��������� ���������� ������ ��������������� ��������� ������
// �� �����    :  ChannelID         -  ������������� ��������� ������
//                Orientation       -  ��������� �� ��������� � ��������
//                                     ����������� ����������� � �������� ������,
//                                     � ������ ���� �������� ������� �����������
//                                     �������� � ����������� ������ ��������
//                                     �� �����, �� ������ �������� ������
//                                     ��������� 0
//                InsideConeAngle   -  ���� ����������� ��������� ������, ��������
//                                     ��������� ������ ���� � �������� �� 1 ��
//                                     360 ��������, � ������ ���� ��������
//                                     ���� ����������� ��������� ������ ��������
//                                     �� �����, �� ������ �������� ������
//                                     ��������� 0
//                OutsideConeAngle  -  ���� �������� ��������� ������, ��������
//                                     ��������� ������ ���� � �������� �� 1 ��
//                                     360 ��������, � ������ ���� ��������
//                                     ���� �������� ��������� ������ ��������
//                                     �� �����, �� ������ �������� ������
//                                     ��������� 0
//                OutsideVolume     -  ������� ��������� ��������� �� ���������
//                                     �������� ������, � ��������� ��������
//                                     �������� ������ ���� � �������� �� 0
//                                     �� 100
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
// ����������  :  ������ ����� �� �������� � ����������� ��������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_SetConeParameters(int ChannelID, float* Orientation, int InsideConeAngle, int OutsideConeAngle, int OutsideVolume);
#else
DLL_API int SQUALL_Channel_SetConeParameters(int ChannelID, float* Orientation, int InsideConeAngle, int OutsideConeAngle, int OutsideVolume);
#endif

//-----------------------------------------------------------------------------
// ��������� ���������� ������ ��������������� ��������� ������
// �� �����    :  ChannelID         -  ������������� ��������� ������
//                Orientation       -  ��������� �� ��������� � ������� �����
//                                     ��������� ������� ������ �����������
//                                     �������� � ����������� ������, � ������
//                                     ���� �������� ������� �����������
//                                     � �������� ������, �������� �� �����,
//                                     �� ������ �������� ������ ��������� 0
//                InsideConeAngle   -  ��������� �� ���������� � ������� �����
//                                     ��������� ������� �������� ����� �����������
//                                     ������ � ��������, � ������ ���� ��������
//                                     ���� ����������� ������ �������� �� �����,
//                                     �� ������ �������� ������ ��������� 0
//                OutsideConeAngle  -  ��������� �� ���������� � ������� �����
//                                     ��������� ������� �������� ����� ��������
//                                     ������ � ��������, � ������ ���� ��������
//                                     ���� �������� ������ �������� �� �����,
//                                     �� ������ �������� ������ ��������� 0
//                OutsideVolume     -  ��������� �� ���������� � ������� �����
//                                     ��������� ������� �������� ������� ���������
//                                     ��������� �� ��������� �������� ������, �
//                                     ���������, � ������ ���� �������� ������
//                                     ��������� �� ��������� ������� ������
//                                     �������� �� �����, �� ������ ��������
//                                     ������ ��������� 0
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
// ����������  :  ������ ����� �� �������� � ����������� ��������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_GetConeParameters(int ChannelID, float* Orientation, int* InsideConeAngle, int* OutsideConeAngle, int* OutsideVolume);
#else
DLL_API int SQUALL_Channel_GetConeParameters(int ChannelID, float* Orientation, int* InsideConeAngle, int* OutsideConeAngle, int* OutsideVolume);
#endif

//-----------------------------------------------------------------------------
// ��������� ����� EAX ���������� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//                Version     -  ����� ������ EAX, �������� ���������� � �����
//                               ������� ���������� EAX ��������� ������.
//                Properties  -  ��������� �� ��������� ����������� ���������
//                               EAX ������, ��������� ������ ���� � �������
//                               ��������� ���������� Version
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
// ����������  :  ������ ����� �� �������� � ����������� ��������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_EAX_SetProperties(int ChannelID, int Version, squall_eax_channel_t* Property);
#else
DLL_API int SQUALL_Channel_EAX_SetProperties(int ChannelID, int Version, squall_eax_channel_t* Property);
#endif

//-----------------------------------------------------------------------------
// ��������� ������� EAX ���������� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//                Version     -  ����� ������ EAX, �������� ���������� � �����
//                               ������� �������� EAX ��������� ������.
//                Properties  -  ��������� �� ��������� ���� ����� ���������
//                               ������� ��������� EAX ������, ��������� �����
//                               ��������� ����������� � ������� ���������
//                               ���������� Version
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
// ����������  :  ������ ����� �� �������� � ����������� ��������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_EAX_GetProperties(int ChannelID, int Version, squall_eax_channel_t* Property);
#else
DLL_API int SQUALL_Channel_EAX_GetProperties(int ChannelID, int Version, squall_eax_channel_t* Property);
#endif

//-----------------------------------------------------------------------------
// ��������� ����� ZOOMFX ���������� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//                Properties  -  ��������� �� ��������� ����������� ���������
//                               ZOOMFX ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
// ����������  :  ������ ����� �� �������� � ����������� ��������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_ZOOMFX_SetProperties(int ChannelID, squall_zoomfx_channel_t* Property);
#else
DLL_API int SQUALL_Channel_ZOOMFX_SetProperties(int ChannelID, squall_zoomfx_channel_t* Property);
#endif

//-----------------------------------------------------------------------------
// ��������� ������� ZOOMFX ���������� ��������� ������
// �� �����    :  ChannelID   -  ������������� ��������� ������
//                Properties  -  ��������� �� ��������� ���� ����� ���������
//                               ������� ��������� ZOOMFX ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
// ����������  :  ������ ����� �� �������� � ����������� ��������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_ZOOMFX_GetProperties(int ChannelID, squall_zoomfx_channel_t* Property);
#else
DLL_API int SQUALL_Channel_ZOOMFX_GetProperties(int ChannelID, squall_zoomfx_channel_t* Property);
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//                ������ ��� ������ � �������� �������
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// ���������/���������� ����� ������ �������
// �� �����    :  ChannelGroupID -  ������������� ������ �������
//                Pause          -  ���� ���������/���������� �����, ��������
//                                  ����� ��������� ��������� ��������:
//                                  true  -  �������� �����
//                                  false -  ��������� �����
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int ChannelGroup_Pause(int ChannelGroupID, int Pause);
#else
DLL_API int SQUALL_ChannelGroup_Pause(int ChannelGroupID, int Pause);
#endif

//-----------------------------------------------------------------------------
// ��������� ������ �������
// �� �����    :  ChannelGroupID -  ������������� ������ �������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int ChannelGroup_Stop(int ChannelGroupID);
#else
DLL_API int SQUALL_ChannelGroup_Stop(int ChannelGroupID);
#endif

//-----------------------------------------------------------------------------
// ��������� ������ ��������� ������ ������� � ���������
// �� �����    :  ChannelGroupID -  ������������� ������ �������
//                Volume         -  �������� ������ ���������, �������� ������
//                                  ������ � �������� �� 0 �� 100
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int ChannelGroup_SetVolume(int ChannelGroupID, int Volume);
#else
DLL_API int SQUALL_ChannelGroup_SetVolume(int ChannelGroupID, int Volume);
#endif

//-----------------------------------------------------------------------------
// ��������� ����� ������� ������������� ������ �������
// �� �����    :  ChannelGroupID -  ����� ������ �������
//                Frequency      -  ����� �������� ������� �������������,
//                                  �������� ��������� ������ ���� � ��������
//                                  �� 100 �� 1000000 ����
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int ChannelGroup_SetFrequency(int ChannelGroupID, int Frequency);
#else
DLL_API int SQUALL_ChannelGroup_SetFrequency(int ChannelGroupID, int Frequency);
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//                ������ ��� ������ � ��������
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// �������� ������ �� �����
// �� �����    :  FileName - ��������� �� ��� �����
//                MemFlag  - ���� ������������ ������������ �����, ��������
//                           ����� ��������� ��������� ��������:
//                           true  -   ��������� ������ ����� � ������
//                           false -   ���������� ������ ����� �� �����
//                Default  - ��������� �� ��������� ���������� ������ ��
//                           ���������, ���� �������� ����� 0, ���������
//                           ��������� ��������� ��������� ������ �� ���������:
//                           SampleGroupID - 0
//                           Priority      - 0
//                           Frequency     - 0
//                           Volume        - 100
//                           Pan           - 50
//                           MinDist       - 1.0f
//                           MaxDist       - 1000000000.0f
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//                � ������ ��������� ������ ��������� �������� �������������
//                ���������� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Sample_LoadFile(char *FileName, int MemFlag, squall_sample_default_t* Default);
#else
DLL_API int SQUALL_Sample_LoadFile(char *FileName, int MemFlag, squall_sample_default_t* Default);
#endif
//-----------------------------------------------------------------------------
// �������� ������ � ��������� �� ������
// �� ����� :  MemoryPtr   - ��������� �� ������ � ������� �����
//             MemorySize  - ������ ������ � ������� �����
//             NewMemory   - ���� ������������ ������ ���������� ������
//                           true -    �������� ������ � �����������, ��
//                                     ���� ��������� �������� ������ �
//                                     �������� ������ ��������� MemoryPtr.
//                                     ����� ���������� ������ ����� �������
//                           false -   ������������ ������������ ������, ��
//                                     ���� ������������ ������ ������ �������
//             Default     - ��������� �� ��������� ���������� ������ ��
//                           ���������, ���� �������� ����� 0, ���������
//                           ��������� ��������� ��������� ������ �� ���������:
//                           SampleGroupID - 0
//                           Priority      - 0
//                           Frequency     - 0
//                           Volume        - 100
//                           Pan           - 50
//                           MinDist       - 1.0f
//                           MaxDist       - 1000000000.0f
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//                � ������ ��������� ������ ��������� �������� �������������
//                ���������� ������
//-----------------------------------------------------------------------------

#ifndef _USRDLL
int Sample_LoadFromMemory(void *MemoryPtr, unsigned int MemorySize, int NewMemory, squall_sample_default_t* Default);
#else
DLL_API int SQUALL_Sample_LoadFromMemory(void *MemoryPtr, unsigned int MemorySize, int NewMemory, squall_sample_default_t* Default);
#endif

//-----------------------------------------------------------------------------
// ������������ ���� �������
// �� �����    :  *
// �� ������   :  *
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   void Sample_UnloadAll(void);
#else
DLL_API void SQUALL_Sample_UnloadAll(void);
#endif

//-----------------------------------------------------------------------------
// ������������ ���������� ������
// �� �����    :  SampleID -  ������������� ������
// �� ������   :  *
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   void Sample_Unload(int SampleID);
#else
DLL_API void SQUALL_Sample_Unload(int SampleID);
#endif

//-----------------------------------------------------------------------------
// ��������� ����������������� ������ ��������� ����� � ��������
// �� �����    :  SampleID -  ������������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//                � ������ ��������� ������ ��������� �������� �����������������
//                ������ � ��������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Sample_GetFileLength(int SampleID);
#else
DLL_API int SQUALL_Sample_GetFileLength(int SampleID);
#endif

//-----------------------------------------------------------------------------
// ��������� ����������������� ������ ��������� ����� � �������������
// �� �����    :  SampleID -  ������������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//                � ������ ��������� ������ ��������� �������� �����������������
//                ������ � ������������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Sample_GetFileLengthMs(int SampleID);
#else
DLL_API int SQUALL_Sample_GetFileLengthMs(int SampleID);
#endif

//-----------------------------------------------------------------------------
// ��������� ������� ������������� ������ ��������� �����
// �� �����    :  SampleID -  ������������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//                � ������ ��������� ������ ��������� �������� �������
//                �������������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Sample_GetFileFrequency(int SampleID);
#else
DLL_API int SQUALL_Sample_GetFileFrequency(int SampleID);
#endif

//-----------------------------------------------------------------------------
// ��������� ����� ���������� ������ �� ���������
// �� �����    :  SampleID -  ������������� ������
//                Default  -  ��������� �� ��������� � ������ ����������� ������
//                            �� ���������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Sample_SetDefault(int SampleID, squall_sample_default_t* Default);
#else
DLL_API int SQUALL_Sample_SetDefault(int SampleID, squall_sample_default_t* Default);
#endif

//-----------------------------------------------------------------------------
// ��������� ������� ���������� ������ �� ���������
// �� �����    :  SampleID -  ������������� ������
//                Default  -  ��������� �� ��������� � ������� ����� ���������
//                            ������� ��������� ������ �� ���������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Sample_GetDefault(int SampleID, squall_sample_default_t* Default);
#else
DLL_API int SQUALL_Sample_GetDefault(int SampleID, squall_sample_default_t* Default);
#endif

//-----------------------------------------------------------------------------
// �������� � ��������������� ����������� ������ �� ���������� ������, ��������
// �� ��������� ������ �� ���������
// �� �����    :  SampleID       -  ������������� ������
//                Loop           -  ���� ������������� ���������������, ��������
//                                  ����� ��������� ��������� ��������:
//                                  true  -  �������������� ����� � �����
//                                           ����������
//                                  false -  ������������� ����� ���� ���
//                ChannelGroupID -  �������������� ������������ ������ � ������
//                                  �������, ���� �������� ��������� ����� 0
//                                  ������ �������� ����� �� ����������� ������
//                                  �������.
//                Start          -  ���� ������� ����� �� ��������� ��������
//                                  ������, �������� ����� ��������� ���������
//                                  ��������:
//                                  true  -  ����� ������ ��������������� �����
//                                           ����� ��������
//                                  false -  ����� ����� ������ �����������,
//                                           ��� ���� ����� ������ ���������������
#ifndef _USRDLL
//                                           ����� ������� ����� Channel_Start()
#else
//                                           ����� ������� �����
//                                           SQUALL_Channel_Start()
#endif
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//                � ������ ��������� ������ ��������� �������� �������������
//                ���������� ��������� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Sample_Play(int SampleID, int Loop, int ChannelGroupID, int Start);
#else
DLL_API int SQUALL_Sample_Play(int SampleID, int Loop, int Group, int Start);
#endif

//-----------------------------------------------------------------------------
// �������� � ��������������� ����������� ������ �� ���������� ������, ��������
// �� ��������� ������ �� ���������
// �� �����    :  SampleID       -  ������������� ������
//                Loop           -  ���� ������������� ���������������, ��������
//                                  ����� ��������� ��������� ��������:
//                                  true  -  �������������� ����� � �����
//                                           ����������
//                                  false -  ������������� ����� ���� ���
//                ChannelGroupID -  �������������� ������������ ������ � ������
//                                  �������, ���� �������� ��������� ����� 0
//                                  ������ �������� ����� �� ����������� ������
//                                  �������.
//                Start          -  ���� ������� ����� �� ��������� ��������
//                                  ������, �������� ����� ��������� ���������
//                                  ��������:
//                                  true  -  ����� ������ ��������������� �����
//                                           ����� ��������
//                                  false -  ����� ����� ������ �����������,
//                                           ��� ���� ����� ������ ���������������
#ifndef _USRDLL
//                                           ����� ������� ����� Channel_Start()
#else
//                                           ����� ������� �����
//                                           SQUALL_Channel_Start()
#endif
//                Priority       -  ��������� ������������ ��������� ������,
//                                  �������� ��������� ������ ������ � ��������
//                                  �� 0 �� 65535
//                Volume         -  ��������� ������������ ��������� ������,
//                                  � ���������, �������� ��������� ������
//                                  ������ � �������� �� 0 �� 100
//                Frequency      -  ������� ������������� ��������� ������,
//                                  �������� ��������� ������ ������ � ��������
//                                  �� 100 �� 1000000000
//                Pan            -  �������� ������������ ��������� ������,
//                                  �������� ��������� ������ ������ � ��������
//                                  �� 0 �� 100
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//                � ������ ��������� ������ ��������� �������� �������������
//                ���������� ��������� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Sample_PlayEx(int SampleID, int Loop, int Group, int Start, int Priority, int Volume, int Frequency, int Pan);
#else
DLL_API int SQUALL_Sample_PlayEx(int SampleID, int Loop, int Group, int Start, int Priority, int Volume, int Frequency, int Pan);
#endif

//-----------------------------------------------------------------------------
// �������� � ��������������� ������������ (�����������) ��������� ������ ��
// ��������� ������, �������� �� ��������� ������ �� ���������
// �� �����    :  SampleID       -  ������������� ������
//                Loop           -  ���� ������������� ���������������, ��������
//                                  ����� ��������� ��������� ��������:
//                                  true  -  �������������� ����� � �����
//                                           ����������
//                                  false -  ������������� ����� ���� ���
//                ChannelGroupID -  �������������� ������������ ������ � ������
//                                  �������, ���� �������� ��������� ����� 0
//                                  ������ �������� ����� �� ����������� ������
//                                  �������.
//                Start          -  ���� ������� ����� �� ��������� ��������
//                                  ������, �������� ����� ��������� ���������
//                                  ��������:
//                                  true  -  ����� ������ ��������������� �����
//                                           ����� ��������
//                                  false -  ����� ����� ������ �����������,
//                                           ��� ���� ����� ������ ���������������
#ifndef _USRDLL
//                                           ����� ������� ����� Channel_Start()
#else
//                                           ����� ������� �����
//                                           SQUALL_Channel_Start()
#endif
//                Position       -  ��������� �� ��������� c ������������
//                                  ��������� ��������� ������
//                Velocity       -  ��������� �� ������ �������� ���������
//                                  ��������� ������, � ������ ���� ��������
//                                  ������� �������� ������������� �� ����,
//                                  �� ������ �������� ������ ���� ����� 0
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//                � ������ ��������� ������ ��������� �������� �������������
//                ���������� ��������� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Sample_Play3D(int SampleID, int Loop, int Group, int Start, float* Position, float* Velocity);
#else
DLL_API int SQUALL_Sample_Play3D(int SampleID, int Loop, int Group, int Start, float* Position, float* Velocity);
#endif

//-----------------------------------------------------------------------------
// �������� � ��������������� ������������ (�����������) ��������� ������ ��
// ��������� ������
// �� �����    :  SampleID       -  ������������� ������
//                Loop           -  ���� ������������� ���������������, ��������
//                                  ����� ��������� ��������� ��������:
//                                  true  -  �������������� ����� � �����
//                                           ����������
//                                  false -  ������������� ����� ���� ���
//                ChannelGroupID -  �������������� ������������ ������ � ������
//                                  �������, ���� �������� ��������� ����� 0
//                                  ������ �������� ����� �� ����������� ������
//                                  �������.
//                Start          -  ���� ������� ����� �� ��������� ��������
//                                  ������, �������� ����� ��������� ���������
//                                  ��������:
//                                  true  -  ����� ������ ��������������� �����
//                                           ����� ��������
//                                  false -  ����� ����� ������ �����������,
//                                           ��� ���� ����� ������ ���������������
#ifndef _USRDLL
//                                           ����� ������� ����� Channel_Start()
#else
//                                           ����� ������� �����
//                                           SQUALL_Channel_Start()
#endif
//                Position       -  ��������� �� ��������� c ������������
//                                  ��������� ��������� ������
//                Velocity       -  ��������� �� ������ �������� ���������
//                                  ��������� ������, � ������ ���� ��������
//                                  ������� �������� ������������� �� ����,
//                                  �� ������ �������� ������ ���� ����� 0
//                Priority       -  ��������� ������������ ��������� ������,
//                                  �������� ��������� ������ ������ � ��������
//                                  �� 0 �� 65535
//                Volume         -  ��������� ������������ ��������� ������,
//                                  � ���������, �������� ��������� ������
//                                  ������ � �������� �� 0 �� 100
//                Frequency      -  ������� ������������� ��������� ������,
//                                  �������� ��������� ������ ������ � ��������
//                                  �� 100 �� 1000000000
//                MinDist        -  ����������� ��������� ���������� ���������
//                                  ������, �������� ��������� ������ ���� �
//                                  �������� �� 0.01f �� 1000000000.0f
//                MaxDist        -  ������������ ��������� ���������� ���������
//                                  ������, �������� ��������� ������ ���� �
//                                  �������� �� 0.01f �� 1000000000.0f
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//                � ������ ��������� ������ ��������� �������� �������������
//                ���������� ��������� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Sample_Play3DEx(int SampleID, int Loop, int Group, int Start, float* Position, float* Velocity, int Priority, int Volume, int Frequency, float MinDist, float MaxDist);
#else
DLL_API int SQUALL_Sample_Play3DEx(int SampleID, int Loop, int Group, int Start, float* Position, float* Velocity, int Priority, int Volume, int Frequency, float MinDist, float MaxDist);
#endif

//-----------------------------------------------------------------------------
// ���������/���������� ����� ���� ������� ������������ �������� �����
// �� �����    :  SampleID -  ��������� �� ������ �����
//                Pause    -  ���� ���������/���������� �����, �������� �����
//                            ��������� ��������� ��������:
//                            true   - �������� �����
//                            false  - ��������� �����
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Sample_Pause(int SampleID, int Pause);
#else
DLL_API int SQUALL_Sample_Pause(int SampleID, int Pause);
#endif

//-----------------------------------------------------------------------------
// ��������� ���� �������� ������� ������������ ��������� �����
// �� �����    :  SampleID -  ������������� ������
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Sample_Stop(int SampleID);
#else
DLL_API int SQUALL_Sample_Stop(int SampleID);
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//                ������ ��� ������ � �������� �������
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// �������� � ��������������� ���������� ������ �� ������ �������, ��������
// �� ��������� ������ �� ���������
// �� �����    :  SampleGroupID  -  ������������� ������ �������
//                Loop           -  ���� ������������� ���������������, ��������
//                                  ����� ��������� ��������� ��������:
//                                  true  -  �������������� ����� � �����
//                                           ����������
//                                  false -  ������������� ����� ���� ���
//                ChannelGroupID -  �������������� ������������ ������ � ������
//                                  �������, ���� �������� ��������� ����� 0
//                                  ������ �������� ����� �� ����������� ������
//                                  �������.
//                Start          -  ���� ������� ����� �� ��������� ��������
//                                  ������, �������� ����� ��������� ���������
//                                  ��������:
//                                  true  -  ����� ������ ��������������� �����
//                                           ����� ��������
//                                  false -  ����� ����� ������ �����������,
//                                           ��� ���� ����� ������ ���������������
#ifndef _USRDLL
//                                           ����� ������� ����� Channel_Start()
#else
//                                           ����� ������� �����
//                                           SQUALL_Channel_Start()
#endif
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//                � ������ ��������� ������ ��������� �������� �������������
//                ���������� ��������� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int SampleGroup_Play(int SoundGroupID, int Loop, int Group, int Start);
#else
DLL_API int SQUALL_SampleGroup_Play(int SoundGroupID, int Loop, int Group, int Start);
#endif

//-----------------------------------------------------------------------------
// �������� � ��������������� ���������� ������ �� ������ �������
// �� �����    :  SampleGroupID  -  ������������� ������ �������
//                Loop           -  ���� ������������� ���������������, ��������
//                                  ����� ��������� ��������� ��������:
//                                  true  -  �������������� ����� � �����
//                                           ����������
//                                  false -  ������������� ����� ���� ���
//                ChannelGroupID -  �������������� ������������ ������ � ������
//                                  �������, ���� �������� ��������� ����� 0
//                                  ������ �������� ����� �� ����������� ������
//                                  �������.
//                Start          -  ���� ������� ����� �� ��������� ��������
//                                  ������, �������� ����� ��������� ���������
//                                  ��������:
//                                  true  -  ����� ������ ��������������� �����
//                                           ����� ��������
//                                  false -  ����� ����� ������ �����������,
//                                           ��� ���� ����� ������ ���������������
#ifndef _USRDLL
//                                           ����� ������� ����� Channel_Start()
#else
//                                           ����� ������� �����
//                                           SQUALL_Channel_Start()
#endif
//                Priority       -  ��������� ������������ ��������� ������,
//                                  �������� ��������� ������ ������ � ��������
//                                  �� 0 �� 65535
//                Volume         -  ��������� ������������ ��������� ������,
//                                  � ���������, �������� ��������� ������
//                                  ������ � �������� �� 0 �� 100
//                Frequency      -  ������� ������������� ��������� ������,
//                                  �������� ��������� ������ ������ � ��������
//                                  �� 100 �� 1000000000
//                Pan            -  �������� ������������ ��������� ������,
//                                  �������� ��������� ������ ������ � ��������
//                                  �� 0 �� 100
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//                � ������ ��������� ������ ��������� �������� �������������
//                ���������� ��������� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int SampleGroup_PlayEx(int SoundGroupID, int Loop, int Group, int Start, int Priority, int Volume, int Frequency, int Pan);
#else
DLL_API int SQUALL_SampleGroup_PlayEx(int SoundGroupID, int Loop, int Group, int Start, int Priority, int Volume, int Frequency, int Pan);
#endif

//-----------------------------------------------------------------------------
// �������� � ��������������� ������������ (�����������) ��������� ������ ��
// �������� ������ �������, �������� �� ��������� ������ �� ���������
// �� �����    :  SampleGroupID  -  ������������� ������ �������
//                Loop           -  ���� ������������� ���������������, ��������
//                                  ����� ��������� ��������� ��������:
//                                  true  -  �������������� ����� � �����
//                                           ����������
//                                  false -  ������������� ����� ���� ���
//                ChannelGroupID -  �������������� ������������ ������ � ������
//                                  �������, ���� �������� ��������� ����� 0
//                                  ������ �������� ����� �� ����������� ������
//                                  �������.
//                Start          -  ���� ������� ����� �� ��������� ��������
//                                  ������, �������� ����� ��������� ���������
//                                  ��������:
//                                  true  -  ����� ������ ��������������� �����
//                                           ����� ��������
//                                  false -  ����� ����� ������ �����������,
//                                           ��� ���� ����� ������ ���������������
#ifndef _USRDLL
//                                           ����� ������� ����� Channel_Start()
#else
//                                           ����� ������� �����
//                                           SQUALL_Channel_Start()
#endif
//                Position       -  ��������� �� ��������� c ������������
//                                  ��������� ��������� ������
//                Velocity       -  ��������� �� ������ �������� ���������
//                                  ��������� ������, � ������ ���� ��������
//                                  ������� �������� ������������� �� ����,
//                                  �� ������ �������� ������ ���� ����� 0
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//                � ������ ��������� ������ ��������� �������� �������������
//                ���������� ��������� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int SampleGroup_Play3D(int SoundGroupID, int Loop, int Group, int Start, float* Position, float* Velocity);
#else
DLL_API int SQUALL_SampleGroup_Play3D(int SoundGroupID, int Loop, int Group, int Start, float* Position, float* Velocity);
#endif

//-----------------------------------------------------------------------------
// �������� � ��������������� ������������ (�����������) ��������� ������ ��
// �������� ������ �������
// �� �����    :  SampleGroupID  -  ������������� ������ �������
//                Loop           -  ���� ������������� ���������������, ��������
//                                  ����� ��������� ��������� ��������:
//                                  true  -  �������������� ����� � �����
//                                           ����������
//                                  false -  ������������� ����� ���� ���
//                ChannelGroupID -  �������������� ������������ ������ � ������
//                                  �������, ���� �������� ��������� ����� 0
//                                  ������ �������� ����� �� ����������� ������
//                                  �������.
//                Start          -  ���� ������� ����� �� ��������� ��������
//                                  ������, �������� ����� ��������� ���������
//                                  ��������:
//                                  true  -  ����� ������ ��������������� �����
//                                           ����� ��������
//                                  false -  ����� ����� ������ �����������,
//                                           ��� ���� ����� ������ ���������������
#ifndef _USRDLL
//                                           ����� ������� ����� Channel_Start()
#else
//                                           ����� ������� �����
//                                           SQUALL_Channel_Start()
#endif
//                Position       -  ��������� �� ��������� c ������������
//                                  ��������� ��������� ������
//                Velocity       -  ��������� �� ������ �������� ���������
//                                  ��������� ������, � ������ ���� ��������
//                                  ������� �������� ������������� �� ����,
//                                  �� ������ �������� ������ ���� ����� 0
//                Priority       -  ��������� ������������ ��������� ������,
//                                  �������� ��������� ������ ������ � ��������
//                                  �� 0 �� 65535
//                Volume         -  ��������� ������������ ��������� ������,
//                                  � ���������, �������� ��������� ������
//                                  ������ � �������� �� 0 �� 100
//                Frequency      -  ������� ������������� ��������� ������,
//                                  �������� ��������� ������ ������ � ��������
//                                  �� 100 �� 1000000000
//                MinDist        -  ����������� ��������� ���������� ���������
//                                  ������, �������� ��������� ������ ���� �
//                                  �������� �� 0.01f �� 1000000000.0f
//                MaxDist        -  ������������ ��������� ���������� ���������
//                                  ������, �������� ��������� ������ ���� �
//                                  �������� �� 0.01f �� 1000000000.0f
// �� ������   :  ����������, ���� ������������ ��������� ������ ���� ����� 0,
//                ����� ���������, ����� ��������� �������� ��� ������
//                � ������ ��������� ������ ��������� �������� �������������
//                ���������� ��������� ������
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int SampleGroup_Play3DEx(int SoundGroupID, int Loop, int Group, int Start, float* Position, float* Velocity, int Priority, int Volume, int Frequency, float MinDist, float MaxDist);
};
#else
DLL_API int SQUALL_SampleGroup_Play3DEx(int SoundGroupID, int Loop, int Group, int Start, float* Position, float* Velocity, int Priority, int Volume, int Frequency, float MinDist, float MaxDist);
#endif

#ifdef __cplusplus
}
#endif
#endif
