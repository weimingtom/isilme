/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** Core functions implementation: audio routines
** Alternative sound engine Squall
*/


#include "hge_impl.h"
#include "squall.h"


HEFFECT CALL HGE_Impl::Effect_Load(const char *filename, DWORD size)
{
	return SQUALL_Sample_LoadFile((char*)filename, 1, 0);
return 0;
}

HCHANNEL CALL HGE_Impl::Effect_Play(HEFFECT eff)
{
	return SQUALL_Sample_Play(eff, 0, 0, 1);
return 0;
}

HCHANNEL CALL HGE_Impl::Effect_PlayEx(HEFFECT eff, int volume, int pan, float pitch, bool loop)
{
	return SQUALL_Sample_PlayEx(eff, loop, 0, 1, 1, volume, 0, pan);
return 0;
}


void CALL HGE_Impl::Effect_Free(HEFFECT eff)
{
	SQUALL_Sample_Unload(eff);
}


HMUSIC CALL HGE_Impl::Music_Load(const char *filename, DWORD size)
{
return 0;
}

HCHANNEL CALL HGE_Impl::Music_Play(HMUSIC mus, bool loop, int volume, int order, int row)
{
return 0;
}

void CALL HGE_Impl::Music_Free(HMUSIC mus)
{

}

void CALL HGE_Impl::Music_SetAmplification(HMUSIC music, int ampl)
{

}

int CALL HGE_Impl::Music_GetAmplification(HMUSIC music)
{
return -1;
}

int CALL HGE_Impl::Music_GetLength(HMUSIC music)
{
return -1;
}

void CALL HGE_Impl::Music_SetPos(HMUSIC music, int order, int row)
{
}

bool CALL HGE_Impl::Music_GetPos(HMUSIC music, int *order, int *row)
{
return false;
}

void CALL HGE_Impl::Music_SetInstrVolume(HMUSIC music, int instr, int volume)
{
}

int CALL HGE_Impl::Music_GetInstrVolume(HMUSIC music, int instr)
{
return -1;
}

void CALL HGE_Impl::Music_SetChannelVolume(HMUSIC music, int channel, int volume)
{
	
}

int CALL HGE_Impl::Music_GetChannelVolume(HMUSIC music, int channel)
{
return -1;
}

HSTREAM CALL HGE_Impl::Stream_Load(const char *filename, DWORD size)
{
return 0;
}

void CALL HGE_Impl::Stream_Free(HSTREAM stream)
{
}

HCHANNEL CALL HGE_Impl::Stream_Play(HSTREAM stream, bool loop, int volume)
{
return 0;
}

void CALL HGE_Impl::Channel_SetPanning(HCHANNEL chn, int pan)
{
	SQUALL_Channel_SetPan(chn,pan);
}

void CALL HGE_Impl::Channel_SetVolume(HCHANNEL chn, int volume)
{
	SQUALL_Channel_SetVolume(chn,volume);
}

void CALL HGE_Impl::Channel_SetPitch(HCHANNEL chn, float pitch)
{
}

void CALL HGE_Impl::Channel_Pause(HCHANNEL chn)
{
	SQUALL_Channel_Pause(chn, 1);
}

void CALL HGE_Impl::Channel_Resume(HCHANNEL chn)
{
	SQUALL_Channel_Pause(chn, 0);
}

void CALL HGE_Impl::Channel_Stop(HCHANNEL chn)
{
	SQUALL_Channel_Stop(chn);
}

void CALL HGE_Impl::Channel_PauseAll()
{
	SQUALL_Pause(1);
}

void CALL HGE_Impl::Channel_ResumeAll()
{
	SQUALL_Pause(0);
}

void CALL HGE_Impl::Channel_StopAll()
{
	SQUALL_Stop();
}

bool CALL HGE_Impl::Channel_IsPlaying(HCHANNEL chn)
{
	return SQUALL_Channel_Status(chn) == SQUALL_CHANNEL_STATUS_PLAY;
return false;
}

float CALL HGE_Impl::Channel_GetLength(HCHANNEL chn) 
{
	return SQUALL_Channel_GetLengthMs(chn) / 1000.0;
return -1;
}

float CALL HGE_Impl::Channel_GetPos(HCHANNEL chn) 
{
	return SQUALL_Channel_GetPlayPositionMs(chn);
return -1;
}

void CALL HGE_Impl::Channel_SetPos(HCHANNEL chn, float fSeconds) 
{
	SQUALL_Channel_SetPlayPositionMs(chn, fSeconds * 1000);
}

void CALL HGE_Impl::Channel_SlideTo(HCHANNEL channel, float time, int volume, int pan, float pitch)
{
}

bool CALL HGE_Impl::Channel_IsSliding(HCHANNEL channel)
{
return false;
}


//////// Implementation ////////


bool HGE_Impl::_SoundInit()
{
	squall_parameters_t parameters;
	parameters.Window = this->System_GetState(HGE_HWND);
	if (SQUALL_Init(0) < 0)
	{
		SQUALL_Free();
		return false;
	}
	return true;
}

void HGE_Impl::_SoundDone()
{
	SQUALL_Free();
}

void HGE_Impl::_SetMusVolume(int vol)
{

}

void HGE_Impl::_SetStreamVolume(int vol)
{

}

void HGE_Impl::_SetFXVolume(int vol)
{

}