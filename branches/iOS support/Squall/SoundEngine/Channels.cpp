//-----------------------------------------------------------------------------
//	������ �� ��������� ��������
//	�������� ��������� ��������� �����
//	�������		: AntiTank
//	�����������	: ������������ ����� (�����)
//-----------------------------------------------------------------------------

// ���������
#include <stdio.h>
#include <math.h>

#include "SoundFile.h"
#include "Channels.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//				��������� ��� ������ �� ��������� ��������
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// �������� ���������� ��������� ������ ��� ����������� �����
//	�� �����	:	DirectSound	-	��������� �� ������ DirectSound
//					format		-	��������� �� �������������� ������������ ������
//					size		-	������ �������� ������
//	�� ������	:	���������� �������� ���������� ��������� ������
//	����������	:	1.	��������� ������ ������� ���������������� �������� �����
//					2.	��������� ���������� ������ ������, ���� �������� ������
//						�� ����������������� ����� 2� ������, �� ��������� �������
//						����� ������ �� ������� ������, ����� ������� �������� 
//						����� � ��������.
//-----------------------------------------------------------------------------
int SSample::CreateSoundBuffer(LPDIRECTSOUND DirectSound,
	WAVEFORMATEX* format, DWORD size, DWORD BufferSize, int UseAcceleration)
{
	// ���������� ����������
	DSBUFFERDESC dsbd;
	WAVEFORMATEX wfx;
	DWORD SoundSize;

	// �������� ������� ������� ���������������
	if (DirectSound) {
		// ��������� ������
		memcpy(&wfx, format, sizeof(WAVEFORMATEX));
		wfx.nChannels = 2;						// ������ ������
		wfx.nBlockAlign = (wfx.nChannels * wfx.wBitsPerSample) >> 3;
		wfx.nAvgBytesPerSec = wfx.nBlockAlign * wfx.nSamplesPerSec;
		wfx.cbSize = 0;

		BufferSize = (wfx.nSamplesPerSec * BufferSize) / 1000;
		// ���������� ������� ���������� ��������� ������
		SoundSize = (BufferSize * wfx.nBlockAlign) << 1;

		// ��������� ������ ���������� ������
		ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
		dsbd.dwSize = sizeof(DSBUFFERDESC);
		dsbd.dwFlags = DSBCAPS_CTRLPAN |
			DSBCAPS_CTRLFREQUENCY |
			DSBCAPS_CTRLVOLUME |
			DSBCAPS_GLOBALFOCUS;
		dsbd.lpwfxFormat = &wfx;

		// ���� ������������� ���������� �����������
		if (!UseAcceleration) {
			dsbd.dwFlags |= DSBCAPS_LOCSOFTWARE;
		}

		// ���� ����� ��� �������� ����� ?
		if ((BufferSize << 1) > size) {
			// �������� ������ �����
			SoundSize = size * wfx.nBlockAlign;
			// �������� ����������� �����
			Status.DOUBLE_BUFFERING = 0;
			Status.BUFFER_LOOP = Status.SAMPLE_LOOP;
			dsbd.dwFlags |= DSBCAPS_STATIC;
		} else {
			// �������� ��������� �����
			Status.DOUBLE_BUFFERING = 1;
			Status.BUFFER_LOOP = 1;
		}
		// ������ ��������� ������
		dsbd.dwBufferBytes = SoundSize;

		// �������� ���������� ������
		if (DirectSound->CreateSoundBuffer(&dsbd, & DS_Buffer, NULL) != DS_OK)
			return false;

		// ���������� ���� � ������
		BytesInBuffer = SoundSize;

		// ���������� ������� � ������
		SamplesInBuffer = SoundSize / wfx.nBlockAlign;

		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
//	�������� ���������� ��������� ������ ��� ������������ �����
//	�� �����	:	DirectSound	-	��������� �� ������ DirectSound
//					format		-	��������� �� �������������� ������������ ������
//					size		-	������ �������� ������
//	�� ������	:	���������� �������� ���������� ��������� ������
//	����������	:	1.	��������� ������ ������� �������������� �������� �����
//					2.	��������� ���������� ������ ������, ���� �������� ������
//						�� ����������������� ����� 2� ������, �� ��������� �������
//						����� ������ �� ������� ������, ����� ������� �������� 
//						����� � ��������.
//-----------------------------------------------------------------------------
int SSample::Create3DSoundBuffer(LPDIRECTSOUND DirectSound,
	WAVEFORMATEX* format, DWORD size, DWORD BufferSize, DWORD Algorithm,
	DWORD UseEAX, int UseAcceleration)
{
	// ���������� ����������
	DSBUFFERDESC dsbd;
	WAVEFORMATEX wfx;
	DWORD SoundSize;

	// �������� ������� ������� ���������������
	if (DirectSound) {
		// ��������� ������
		memcpy(&wfx, format, sizeof(WAVEFORMATEX));
		wfx.nChannels = 1;						// ������ ����
		wfx.nBlockAlign = (wfx.nChannels * wfx.wBitsPerSample) >> 3;
		wfx.nAvgBytesPerSec = wfx.nBlockAlign * wfx.nSamplesPerSec;
		wfx.cbSize = 0;

		// ���������� ������� ������ � �������
		BufferSize = (wfx.nSamplesPerSec * BufferSize) / 1000;
		// ���������� ������� ������ � ������
		SoundSize = (BufferSize * wfx.nBlockAlign) << 1;

		// ���������� � ��������� ������ ��� ���������� ������
		ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
		dsbd.dwSize = sizeof(DSBUFFERDESC);
		dsbd.dwFlags = DSBCAPS_CTRLFREQUENCY |
			DSBCAPS_CTRLVOLUME |
			DSBCAPS_GLOBALFOCUS |
			DSBCAPS_CTRL3D |
			DSBCAPS_MUTE3DATMAXDISTANCE;
		dsbd.lpwfxFormat = &wfx;

		// ������������� ���������� �����������
		if (!UseAcceleration) {
			dsbd.dwFlags |= DSBCAPS_LOCSOFTWARE;
		}

		// ���� ����� ��� �������� ����� ?
		if ((BufferSize << 1) > size) {
			// �������� ������ �����
			SoundSize = size * wfx.nBlockAlign;
			// ������� ��������� �����
			Status.DOUBLE_BUFFERING = 0;
			Status.BUFFER_LOOP = Status.SAMPLE_LOOP;
			dsbd.dwFlags |= DSBCAPS_STATIC;
		} else {
			// ������� ��������� �����
			Status.DOUBLE_BUFFERING = 1;
			Status.BUFFER_LOOP = 1;
		}
		// ������ ��������� ������
		dsbd.dwBufferBytes = SoundSize;

		// ������ ������� ������ ����������� �����
		switch (Algorithm) {
		case 0x1:
			dsbd.guid3DAlgorithm = DS3DALG_NO_VIRTUALIZATION;
			break;

		case 0x2:
			dsbd.guid3DAlgorithm = DS3DALG_HRTF_FULL;
			break;

		case 0x3:
			dsbd.guid3DAlgorithm = DS3DALG_HRTF_LIGHT;
			break;

		default:
			dsbd.guid3DAlgorithm = DS3DALG_DEFAULT;
			break;
		}

		// �������� ���������� ������
		if (DirectSound->CreateSoundBuffer(&dsbd, & DS_Buffer, NULL) != DS_OK)
			return false;

		// �������� ���������� ��� ����������� �����
		if (DS_Buffer->QueryInterface(IID_IDirectSound3DBuffer,
					   	(VOID * *) &DS3D_Buffer) != DS_OK)
			return false;

		// ������� �������������� ��������� ����������� ������
		DS_PropSet = 0;
		if (DS_Buffer->QueryInterface(IID_IKsPropertySet,
					   	(void * *) &DS_PropSet) != DS_OK)
			DS_PropSet = 0;

		// ������� �������������� ��������� ����������� ������
		DS3D_PropSet = 0;
		if (UseEAX) {
			if (DS3D_Buffer->QueryInterface(IID_IKsPropertySet,
							 	(void * *) &DS3D_PropSet) != DS_OK)
				DS3D_PropSet = 0;
		}

		Param.ds3d.dwSize = sizeof(DS3DBUFFER);
		if (DS3D_Buffer->GetAllParameters(&Param.ds3d) != DS_OK)
			return false;

		// ���������� ���� � ������
		BytesInBuffer = SoundSize;

		// ���������� ������� � ������
		SamplesInBuffer = SoundSize / wfx.nBlockAlign;

		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
//	��������������� ���������� ��������� ������
//	�� �����	:	*
//	�� ������	:	���������� �������� ��������� ������
//-----------------------------------------------------------------------------
int SSample::DeleteSoundBuffer(void)
{
	// ������������ ��������������� ���������� ����������� ������
	if (DS3D_PropSet) {
		DS3D_PropSet->Release();
		DS3D_PropSet = 0;
	}

	// ������������ ���������� ����������� �����
	if (DS3D_Buffer) {
		DS3D_Buffer->Release();
		DS3D_Buffer = 0;
	}

	// ������������ ��������������� ����������
	if (DS_PropSet) {
		DS_PropSet->Release();
		DS_PropSet = 0;
	}

	// ��������� �����
	if (DS_Buffer) {
		DS_Buffer->Release();
		DS_Buffer = 0;
	}

	// ������� ����� ��� ������
	Status.STAGE = EMPTY;
	return true;
}

//-----------------------------------------------------------------------------
//	���������� ��������� ������
//	�� �����	:	half	- ����� ����������� ��������
//	�� ������	:	���������� ���������� �������� ��������
//-----------------------------------------------------------------------------
int SSample::FillSoundBuffer(char half)
{
	// ���������� ����������
	bool ok;
	DWORD cur_size, fill_size, block_size, lock_len, write_pos, write_len, read;
	void* lock_ptr;

	// �������� ������� ��������� ������
	ok = (DS_Buffer) ? true : false;
	if (ok) {
		// ��������� ������ ���������� ������
		cur_size = EndPtr - CurPtr;
		// ���� ���� ���������� ������ ���
		if (!cur_size && !Status.SAMPLE_LOOP) {
			// ��������� ����
			if (EndFlag == 1) {
				Stop();
				return true;
			}
			// ��������� �����, � ��������� ���������� ������� �����
			EndFlag = 1;
		}

		// ���������� ������ ������������ ������ �����
		write_pos = 0;
		write_len = BytesInBuffer;
		fill_size = SamplesInBuffer;

		// ���� � ������� ������������ ?
		if (Status.DOUBLE_BUFFERING) {
			write_len >>= 1;
			fill_size >>= 1;
			if (half)
				write_pos = write_len;
		} 

		// ������������ ��������� ������
		ok = (DS_Buffer->Lock(write_pos,
						 	write_len,
						 	& lock_ptr,
						 	& lock_len,
						 	NULL,
						 	NULL,
						 	0) == DS_OK) ?
			true :
			false;
		if (ok) {
			// �������� ������ �������
			char* ptr = (char*) lock_ptr;

			if (Status.SOUND_TYPE == TYPE_AMBIENT) {
				do {
					// ������ ���������� ������
					cur_size = EndPtr - CurPtr;
					// ���������� ���������� ����������
					block_size = (cur_size < fill_size) ?
						cur_size :
						fill_size;

					// ������ ��� ���� ?
					if (cur_size) {
						// �������� ������� 
						read = SoundFile->GetStereoData(ptr,
										  	CurPtr,
										  	block_size,
										  	Status.SAMPLE_LOOP);
						if (read) {
							ptr += read;
							CurPtr += block_size;
							fill_size -= block_size;
						} else {
							ok = false;
							break;
						}
					} else {
						// ���� �������� ?
						if (Status.SAMPLE_LOOP) {
							CurPtr = StartPtr;
						} else {
							// ���������� ������ �������
							read = SoundFile->GetStereoMute(ptr, fill_size);
							if (read) {
								ptr += read;
								fill_size = 0;
							} else {
								ok = false;
								break;
							}
						}
					}
				} while (fill_size);
			} else {
				do {
					// ������ ���������� ������
					cur_size = EndPtr - CurPtr;
					// ���������� ���������� ����������
					block_size = (cur_size < fill_size) ?
						cur_size :
						fill_size;

					// ������ ��� ���� ?
					if (cur_size) {
						// �������� ������� 
						read = SoundFile->GetMonoData(ptr,
										  	CurPtr,
										  	block_size,
										  	Status.SAMPLE_LOOP);
						if (read) {
							ptr += read;
							CurPtr += block_size;
							fill_size -= block_size;
						} else {
							ok = false;
							break;
						}
					} else {
						// ���� �������� ?
						if (Status.SAMPLE_LOOP) {
							CurPtr = StartPtr;
						} else {
							// ���������� ������ �������
							read = SoundFile->GetMonoMute(ptr, fill_size);
							if (read) {
								ptr += read;
								fill_size = 0;
							} else {
								ok = false;
								break;
							}
						}
					}
				} while (fill_size);
			}
		}
		if (ok) {
			// ��������������� ��������� ������
			ok = (DS_Buffer->Unlock(lock_ptr, lock_len, NULL, NULL) == DS_OK) ?
				true :
				false;
		}
	}
	// ������ ��������� ������
	return ok;
}

//-----------------------------------------------------------------------------
//	��������� ��������� ����� � ������������
//	�� �����	:	��������� �� ��������� � ������������ �����
//	�� ������	:	���������� ��������� ��������� �����
//-----------------------------------------------------------------------------
int SSample::Set3DParameters(D3DVECTOR* Position, D3DVECTOR* Velocity,
	D3DVECTOR* ConeOrientation, unsigned int InsideConeAngle,
	unsigned int OutsideConeAngle, long ConeOutsideVolume, float MinDist,
	float MaxDist, DWORD Deferred)
{
	bool change = false;
	// ������ �� ������
	if (!DS3D_Buffer)
		return false;

	// �������� ������� ���������
	if (Position) {
		// �������� ��������� ���������
		if ((Param.ds3d.vPosition.x != Position->x) ||
			(Param.ds3d.vPosition.y != Position->y) ||
			(Param.ds3d.vPosition.z != Position->z)) {
			// ������� ����� ��������
			Param.ds3d.vPosition.x = Position->x;
			Param.ds3d.vPosition.y = Position->y;
			Param.ds3d.vPosition.z = Position->z;
			change = true;
		}
	}

	// �������� ������� ���������
	if (Velocity) {
		// �������� ��������� ���������
		if ((Param.ds3d.vVelocity.x != Velocity->x) ||
			(Param.ds3d.vVelocity.y != Velocity->y) ||
			(Param.ds3d.vVelocity.z != Velocity->z)) {
			// ������� ����� ��������
			Param.ds3d.vVelocity.x = Velocity->x;
			Param.ds3d.vVelocity.y = Velocity->y;
			Param.ds3d.vVelocity.z = Velocity->z;
			change = true;
		}
	}

	// �������� ������� ���������
	if (ConeOrientation) {
		// �������� ��������� ���������
		if ((Param.ds3d.vConeOrientation.x != ConeOrientation->x) ||
			(Param.ds3d.vConeOrientation.y != ConeOrientation->y) ||
			(Param.ds3d.vConeOrientation.z != ConeOrientation->z)) {
			// ������� ����� ��������
			Param.ds3d.vConeOrientation.x = ConeOrientation->x;
			Param.ds3d.vConeOrientation.y = ConeOrientation->y;
			Param.ds3d.vConeOrientation.z = ConeOrientation->z;
			change = true;
		}
	}

	// �������� ������� ���������
	if (InsideConeAngle) {
		// �������� ��������� ���������
		if (Param.ds3d.dwInsideConeAngle != InsideConeAngle) {
			// ������� ����� ��������
			Param.ds3d.dwInsideConeAngle = InsideConeAngle;
			change = true;
		}
	}

	// �������� ������� ���������
	if (OutsideConeAngle) {
		// �������� ��������� ���������
		if (Param.ds3d.dwOutsideConeAngle != OutsideConeAngle) {
			// ������� ����� ��������
			Param.ds3d.dwOutsideConeAngle = OutsideConeAngle;
			change = true;
		}
	}

	// �������� ������� ���������
	if (ConeOutsideVolume) {
		// �������� ��������� ���������
		if (Param.ds3d.lConeOutsideVolume != ConeOutsideVolume) {
			// ������� ����� ��������
			Param.ds3d.lConeOutsideVolume = ConeOutsideVolume;
			change = true;
		}
	}

	// �������� ������� ���������
	if (MinDist) {
		// �������� ��������� ���������
		if (Param.ds3d.flMinDistance != MinDist) {
			// ������� ����� ��������
			Param.ds3d.flMinDistance = MinDist;
			change = true;
		}
	}

	// �������� ������� ���������
	if (MaxDist) {
		// �������� ��������� ���������
		if (Param.ds3d.flMaxDistance != MaxDist) {
			// ������� ����� ��������
			Param.ds3d.flMaxDistance = MaxDist;
			change = true;
		}
	}

	// �������� ������� ���������
	if (change) {
		// ��������� ��������� ����� � ������������
		if (DS3D_Buffer->SetAllParameters(&Param.ds3d, Deferred) != DS_OK)
			return false;
	}
	return true;
}

//-----------------------------------------------------------------------------
//	��������� ��������� ����� � ������������
//	�� �����	:	��������� �� ��������� � ������� ��������� ���������� �����
//	�� ������	:	���������� ��������� ��������� �����
//-----------------------------------------------------------------------------
int SSample::Get3DParameters(D3DVECTOR* Position, D3DVECTOR* Velocity,
	D3DVECTOR* ConeOrientation, int* InsideConeAngle, int* OutsideConeAngle,
	long* ConeOutsideVolume, float* MinDist, float* MaxDist)
{
	// ������ �� ������
	if (!DS3D_Buffer)
		return false;

	// ��������� ��������� ��������� �����
	if (Position) {
		Position->x = Param.ds3d.vPosition.x;
		Position->y = Param.ds3d.vPosition.y;
		Position->z = Param.ds3d.vPosition.z;
	}

	// ��������� �������� ��������� �����
	if (Velocity) {
		Velocity->x = Param.ds3d.vVelocity.x;
		Velocity->y = Param.ds3d.vVelocity.y;
		Velocity->z = Param.ds3d.vVelocity.z;
	}

	// ��������� ����������� ��������� �����
	if (ConeOrientation) {
		ConeOrientation->x = Param.ds3d.vConeOrientation.x;
		ConeOrientation->y = Param.ds3d.vConeOrientation.y;
		ConeOrientation->z = Param.ds3d.vConeOrientation.z;
	}

	// ��������� ���� ����������� ������
	if (InsideConeAngle)
		*InsideConeAngle = Param.ds3d.dwInsideConeAngle;

	// ��������� ���� �������� ������
	if (OutsideConeAngle)
		*OutsideConeAngle = Param.ds3d.dwOutsideConeAngle;

	// ��������� ����������� ��������� �� ��������� �������� ������
	if (ConeOutsideVolume)
		*ConeOutsideVolume = Param.ds3d.lConeOutsideVolume;

	// ��������� ����������� ��������� ����������
	if (MinDist)
		*MinDist = Param.ds3d.flMinDistance;

	// ��������� ������������ ��������� ����������
	if (MaxDist)
		*MaxDist = Param.ds3d.flMaxDistance;

	return true;
}

//-----------------------------------------------------------------------------
//	��������� ������� ��������� ������
//	�� �����	:	*
//	�� ������	:	*
//	����������	:	��������� ��������� ��������� ��������� ������
//-----------------------------------------------------------------------------
int SSample::GetStatus(void)
{
	// ��������� ����������
	bool Status_flag = false;
	DWORD Temp_Status = 0;

	// ������� ������ �������
	Status.STATUS_ERROR = 0;
	Status.BUFFER_PRESENT = 0;

	// �������� ������� ��������� ������
	if (!DS_Buffer) {
		Status.STATUS_ERROR = 1;
		return false;
	}

	// ������ ������� ?
	while (!Status_flag) {
		// ��������� �������
		if (DS_Buffer->GetStatus(&Temp_Status) != DS_OK) {
			Status.STATUS_ERROR = 1;
			return false;
		}

		// ����� ������� ?
		if (Temp_Status & DSBSTATUS_BUFFERLOST) {
			// ������������� ��������� ������
			while (DS_Buffer->Restore() == DSERR_BUFFERLOST) {
				Sleep(10);
			}

			// ���������� �������� ������ ������
		} else
			Status_flag = true;
	}
	// �������� ����� ����
	Status.BUFFER_PRESENT = 1;

	// ����� ��������������� ?
	if ((Status.STAGE != PAUSE) && (Status.STAGE != PREPARE)) {
		if (Temp_Status & DSBSTATUS_PLAYING)
			Status.STAGE = PLAY;
		else
			Status.STAGE = STOP;
	}
	return true;
}

//-----------------------------------------------------------------------------
//	���������� �����
//	�� �����	   :	x
//  			  y
//  			  z
//	�� ������   :	*
//	����������	:	������ ��������� ����������� �� ����������� �������� �������
//-----------------------------------------------------------------------------
int SSample::Update(float x, float y, float z)
{
	int ok;
	float direct;
	int Position;
	int Bank;
	// ��������� ������� ������
	if (!GetStatus())
		return false;

	// ���� ����� �����������
	ok = true;
	if (Status.STAGE == STOP) {
		DeleteSoundBuffer();
		return ok;
	}

	// �������� ������� ������
	if (Status.BUFFER_PRESENT) {
		// ����� � ������� ������������ ?
		if (Status.DOUBLE_BUFFERING) {
			// ����� ���������������� ?
			if (Status.STAGE == PLAY) {
				ok = GetDXPosition(&Position);
				if (ok) {
					Bank = (Position > BytesInBuffer / 2) ? 0 : 1;
					if (OldBank != Bank) {
						OldBank = Bank;
						ok = FillSoundBuffer(Bank);
					}
				}
			}
		}
	}

	if (DS3D_Buffer) {
		// ���������� ��������� �� ��������� �����
		direct = sqrtf(powf((x - Param.ds3d.vPosition.x), 2) +
				 	powf((y - Param.ds3d.vPosition.y), 2) +
				 	powf((z - Param.ds3d.vPosition.z), 2));

		// � ������ ���� ��������� �� ��������� ������ ��� ������������ ��������� ���������� ��������� � 0
		if (direct > Param.ds3d.flMaxDistance)
			DS_Buffer->SetVolume(-10000);
		else
			DS_Buffer->SetVolume(Param.Volume);
	}
	return ok;
}

//-----------------------------------------------------------------------------
//	���������� �����������
//	�� �����	:	*
//	�� ������	:	*
//	����������	:	������ ��������� ����������� �� ����������� �������� �������
//-----------------------------------------------------------------------------
void SSample::UpdateWorker(void)
{
	int CurTime;
	CurTime = timeGetTime();
	// ������ ������ ?
	if ((CurTime - OldChannelWorkerTime) > ChannelWorkerTime) {
		OldChannelWorkerTime = CurTime;
		// ����� ����������� ������
		if (ChannelWorker) {
			if (!ChannelWorker(ChannelID, UserData)) {
				DeleteSoundBuffer();
			}
		}
	}
}

//-----------------------------------------------------------------------------
//	������ ��������������� ��������� ������
//	�� �����	:	*
//	�� ������	:	���������� ������� ���������������
//-----------------------------------------------------------------------------
int SSample::Play(void)
{
	if (DS_Buffer) {
		// �������� ������� ������
		if (DS_Buffer->SetCurrentPosition(0) == DS_OK) {
			if (DS_Buffer->Play(0, 0, Status.BUFFER_LOOP) == DS_OK) {
				Status.STAGE = PLAY;
				return true;
			}
		}
	}
	return false;
}

//-----------------------------------------------------------------------------
//	��������� ��������������� �����
//	�� �����	:	*
//	�� ������	:	���������� ��������� ��������� ������
//-----------------------------------------------------------------------------
int SSample::Stop(void)
{
	if (DS_Buffer) {
		// �������� ������� ������
		DS_Buffer->SetVolume(-10000);

		if (DS_Buffer->Stop() == DS_OK) {
			// ����� ����������� ��������� ���������������
			if (ChannelEndWorker) {
				ChannelEndWorker(ChannelID, ChannelEndUserData);
			}

			Status.STAGE = STOP;
			ChannelID = 0;
			return true;
		}
	}


	return false;
}

//-----------------------------------------------------------------------------
//	��������� ������ ��������� ������
//	�� �����	:	volume	- �������� ���������������� ������ ���������
//	�� ������	:	���������� ��������� ������ ���������
//-----------------------------------------------------------------------------
int SSample::SetVolume(long volume)
{
	if (DS_Buffer) {
		// �������� ������� ������
		Param.Volume = volume;
		if (DS_Buffer->SetVolume(volume) == DS_OK)
			return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
//	��������� ������ ��������� ������
//	�� �����	:	volume	- ��������� �� ���������� � ������� ���������
//					�������� ������ ���������
//	�� ������	:	���������� ��������� ������ ���������
//-----------------------------------------------------------------------------
int SSample::GetVolume(long* volume)
{
	if (DS_Buffer) {
		// �������� ������� ������
		if (DS_Buffer->GetVolume(volume) == DS_OK)
			return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
//	��������� ����� ������� �������� ������
//	�� �����	:	Frequency	- ����� �������
//	�� ������	:	���������� ��������� ����� ������� �������� ������
//-----------------------------------------------------------------------------
int SSample::SetFrequency(int Frequency)
{
	if (DS_Buffer) {
		// ������ �� ������
		Param.Frequency = Frequency;
		if (DS_Buffer->SetFrequency(Frequency) == DS_OK)
			return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
//	��������� ������� ������� �������� ������
//	�� �����	:	Frequency	- ��������� �� ���������� � ������� �����
//								  ��������� ������� �������� �������� ������
//	�� ������	:	���������� ��������� ������� �������
//-----------------------------------------------------------------------------
int SSample::GetFrequency(int* Frequency)
{
	DWORD fr;
	if (DS_Buffer) {
		// ������ �� ������
		if (DS_Buffer->GetFrequency(&fr) == DS_OK) {
			*Frequency = fr;
			return true;
		}
	}
	return false;
}

//-----------------------------------------------------------------------------
//	��������� �������� �����
//	�� �����	:	Pan		- ����� �������� ��������
//	�� ������	:	���������� ��������� ��������
//-----------------------------------------------------------------------------
int SSample::SetPan(int Pan)
{
	if (DS_Buffer) {
		// ������ �� ������
		// ������������
		if (Pan > 100)
			Pan = 100;
		Param.Pan = Pan;
		if (DS_Buffer->SetPan((Pan * 200) - 10000) == DS_OK)
			return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
//	��������� ������� �������� �����
//	�� �����	:	Pan		- ��������� �� ���������� � ������� ����� ���������
//							  ������� �������� �������� �����
//	�� ������	:	���������� ��������� ������� ��������
//-----------------------------------------------------------------------------
int SSample::GetPan(int* Pan)
{
	long temp = 0;
	if (DS_Buffer) {
		if (DS_Buffer->GetPan(&temp) == DS_OK) {
			*Pan = (temp + 10000) / 200;
			return true;
		}
	}
	return false;
}

//-----------------------------------------------------------------------------
//	��������� ����� ������� ��������������� �����
//	�� �����	:	Position	- ����� �������� ������� ��������������� �����
//	�� ������	:	���������� ��������� ����� ������� ��������������� �����
//-----------------------------------------------------------------------------
int SSample::SetPlayPosition(int Position)
{
	int ret;
	ret = (DS_Buffer) ? true : false;
	if (ret) {
		// ���� ��������������� ?
		if (Status.STAGE == PLAY) {
			ret = (DS_Buffer->Stop() == DS_OK) ? true : false;
			if (ret)
				ret = (DS_Buffer->SetCurrentPosition(0) == DS_OK) ?
					true :
					false;
		} else {
			if (Status.STAGE == PAUSE)
				PausePtr = 0;
		}

		if (ret) {
			CurPtr = StartPtr + Position;
			ret = FillSoundBuffer(0);
			OldBank = 0;
		}

		if (ret) {
			if (Status.STAGE == PLAY) {
				ret = (DS_Buffer->Play(0, 0, Status.BUFFER_LOOP) == DS_OK) ?
					true :
					false;
			}
		}
	}
	return ret;
}

//-----------------------------------------------------------------------------
//	��������� ������� ������� ��������������� �����
//	�� �����	:	Position	- ��������� �� ���������� � ������� �����
//								  ��������� ������� �������� �������
//								  ��������������� �����
//	�� ������	:	���������� ��������� ������� ������� ���������������
//-----------------------------------------------------------------------------
int SSample::GetPlayPosition(int* Position)
{
	DWORD DXPosition;
	if (DS_Buffer) {
		if (Status.STAGE == PLAY) {
			if (DS_Buffer->GetCurrentPosition(&DXPosition, NULL) != DS_OK)
				return false;
		} else {
			if (Status.STAGE == PAUSE)
				DXPosition = PausePtr;
		}
		if (Status.DOUBLE_BUFFERING) {
			*Position = (CurPtr / SamplesInBuffer) * SamplesInBuffer +
				DXPosition /
				(BytesInBuffer / SamplesInBuffer);
			if (*Position >= MasterSize)
				*Position %= MasterSize;
		} else {
			*Position = DXPosition / (BytesInBuffer / SamplesInBuffer);
		}
	}
	return true;
}

//-----------------------------------------------------------------------------
//	��������� ������� ������� ��������������� �����
//	�� �����	:	Position	- ��������� �� ���������� � ������� �����
//								  ��������� ������� �������� �������
//								  ��������������� �����
//	�� ������	:	���������� ��������� ������� ������� ���������������
//-----------------------------------------------------------------------------
int SSample::GetDXPosition(int* Position)
{
	if (DS_Buffer) {
		if (DS_Buffer->GetCurrentPosition((unsigned long *) Position, NULL) ==
			DS_OK)
			return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
//	���������/���������� ����� ������
//	�� �����	:	Flag	- ���� ���������/���������� ���������������
//	�� ������	:	���������� ��������� ��������� �����
//-----------------------------------------------------------------------------
int SSample::Pause(int Flag)
{
	if (DS_Buffer) {
		if (Flag) {
			// ��������� �����
			if (Status.STAGE == PLAY) {
				if (DS_Buffer->GetCurrentPosition((unsigned long *) &PausePtr,
							   	NULL) == DS_OK) {
					if (DS_Buffer->Stop() == DS_OK) {
						Status.STAGE = PAUSE;
						return true;
					}
				}
			}
		} else {
			// ���������� �����
			if (Status.STAGE == PAUSE) {
				if (DS_Buffer->SetCurrentPosition(PausePtr) == DS_OK) {
					if (DS_Buffer->Play(0, 0, Status.BUFFER_LOOP) == DS_OK) {
						Status.STAGE = PLAY;
						return true;
					}
				}
			}
		}
	}
	return false;
}

//-----------------------------------------------------------------------------
//	��������� ������ ���������
//	�� �����	:	Start	- ��������� �������
//					End		- �������� �������
//	�� ������	:	���������� ���������
//-----------------------------------------------------------------------------
int SSample::SetFragment(int Start, int End)
{
	int ret;
	ret = (DS_Buffer) ? true : false;
	if (ret) {
		// �������� ������ �� �������
		if (Start > MasterSize)
			Start = MasterSize;
		if (End > MasterSize)
			End = MasterSize;

		// ���� �������� ����� 0
		ret = (Start != End) ? true : false;
		if (ret) {
			// �������� ����������
			if (Start > End) {
				// �������� ��������� �������
				StartPtr = End;
				EndPtr = Start;
			} else {
				StartPtr = Start;
				EndPtr = End;
			}
			// �������� ������ �������� ��������� �� ������� ������ ���������
			if ((CurPtr <= StartPtr) || (CurPtr >= EndPtr))
				ret = SetPlayPosition(0);
		}
	}
	return ret;
}





























