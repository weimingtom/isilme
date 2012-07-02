//  Copyright (C) 2010-2012 VSTU
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
#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "Definitions.h"

/// @class SoundSystem
/// Звуковая подсистема.
/// Звуковая подсистема позволяет использовать в игре звуковые файлы
class ISILME_API SoundSystem
{
public:
	virtual ~SoundSystem();

	/// Включить или выключить звук в игре.
	/// При выключении звука фоновая музыка ставится на паузу, 
	/// а все остальные каналы останавливаются. 
	/// Звуковые эффекты при выключенном звуке не проигрываются.
	/// @param use bool 
	virtual void SetUseSound(bool use) = 0;

	/// Проверить. включен ли звук
	virtual bool IsUseSound() = 0;

	/// Установить фоновый звук
	/// Фоновый звук устанавливается в любом случае, даже если звук в игре выключен
	/// При выключенном звуке фоновый канал будет автоматически поставлен на паузу.
	/// @param file std::string путь к звуковому файлу
	virtual void SetBackGroundMusic(std::string file) = 0;

	/// Проиграть определенный эффект
	/// @param effect HEFFECT дескриптор звукового эффекта
	virtual HCHANNEL PlayEffect(HEFFECT effect, bool loop = false, int volume = 100, int pan = 0, float pitch = 1.0f) = 0;

	virtual void StopChannel(HCHANNEL channel) = 0;
};

/// @class IsilmeExport
/// Реализация звуковой подсистемы для HGE
class ISILME_API HGESoundSystem : public SoundSystem
{
public:
	HGESoundSystem(HGE* hge);
	virtual ~HGESoundSystem();

	virtual void SetUseSound(bool use);
	virtual void SetBackGroundMusic(std::string file);
	virtual HCHANNEL PlayEffect(HEFFECT effect, bool loop, int volume, int pan, float pitch);
	virtual bool IsUseSound();
	virtual void StopChannel(HCHANNEL channel);
protected:
	HGE*			mHGE;
	bool			mUseSound;
	HEFFECT			mMusic;
	HCHANNEL		mMusicChanel;
};

#endif