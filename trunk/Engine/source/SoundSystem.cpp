#include "Isilme.h"

// SoundSystem

SoundSystem::~SoundSystem()
{
}

// HGESoundSystem

void HGESoundSystem::SetUseSound(bool use)
{
	mUseSound = use;
	if (!mMusicChanel)
		return;

	if (mUseSound)
	{
		mHGE->Channel_Resume(mMusicChanel);
	}
	else
	{
		mHGE->Channel_Pause(mMusicChanel);
	}
}

void HGESoundSystem::SetBackGroundMusic(std::string file)
{
	mMusic = mHGE->Effect_Load(file.data());
	mMusicChanel = mHGE->Effect_PlayEx(mMusic, 100, 0, 1.0f, true);
	if (!mUseSound)
		mHGE->Channel_Pause(mMusicChanel);
}

void HGESoundSystem::PlayEffect(HEFFECT effect)
{
	if (mUseSound)
	{
		mHGE->Effect_Play(effect);
	}
}

bool HGESoundSystem::IsUseSound()
{
	return mUseSound;
}

HGESoundSystem::HGESoundSystem(HGE*	hge)
{
	mHGE = hge;
	mUseSound = true;
	mMusic = 0;
	mMusicChanel = 0;
}

HGESoundSystem::~HGESoundSystem()
{
	if (mMusic)
		mHGE->Music_Free(mMusic);
}