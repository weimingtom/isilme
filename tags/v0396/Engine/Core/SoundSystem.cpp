﻿//  Copyright (C) 2010-2012 VSTU
//
//	This file is part of Isilme SDK.
//
//		Isilme SDK is free software: you can redistribute it and/or modify
//		it under the terms of the GNU Lesser General Public License as published by
//		the Free Software Foundation, either version 3 of the License, or
//		(at your option) any later version.
//
//		Isilme SDK is distributed in the hope that it will be useful,
//		but WITHOUT ANY WARRANTY; without even the implied warranty of
//		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//		GNU Lesser General Public License for more details.
//
//		You should have received a copy of the GNU Lesser General Public License
//		along with Isilme SDK.  If not, see <http://www.gnu.org/licenses/>.
//
//	Этот файл — часть Isilme SDK.
//
//		Isilme SDK - свободная программа: вы можете перераспространять ее и/или
//		изменять ее на условиях Меньшей стандартной общественной лицензии GNU в том виде,
//		в каком она была опубликована Фондом свободного программного обеспечения;
//		либо версии 3 лицензии, либо (по вашему выбору) любой более поздней
//		версии.
//
//		Isilme SDK распространяется в надежде, что она будет полезной,
//		но БЕЗО ВСЯКИХ ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА
//		или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Подробнее см. в Меньшей стандартной
//		общественной лицензии GNU.
//
//		Вы должны были получить копию Меньшей стандартной общественной лицензии GNU
//		вместе с этой программой. Если это не так, см.
//		<http://www.gnu.org/licenses/>.
#include "IsilmePCH.h"
#include "SoundSystem.h"

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

HCHANNEL HGESoundSystem::PlayEffect(HEFFECT effect, bool loop, int volume, int pan, float pitch)
{
	if (mUseSound)
	{
		return mHGE->Effect_PlayEx(effect, volume, pan, pitch, loop);
	}
	return 0;
}

void	HGESoundSystem::StopChannel(HCHANNEL channel)
{
	mHGE->Channel_Stop(channel);
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