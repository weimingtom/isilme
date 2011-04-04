#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "Definitions.h"

/// @class SoundSystem
/// Звуковая подсистема.
/// Звуковая подсистема позволяет использовать в игре звуковые файлы
class IsilmeExport SoundSystem
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
	virtual void PlayEffect(HEFFECT effect) = 0;
};

/// @class IsilmeExport
/// Реализация звуковой подсистемы для HGE
class IsilmeExport HGESoundSystem : public SoundSystem
{
public:
	HGESoundSystem(HGE* hge);
	virtual ~HGESoundSystem();

	virtual void SetUseSound(bool use);
	virtual void SetBackGroundMusic(std::string file);
	virtual void PlayEffect(HEFFECT effect);
	virtual bool IsUseSound();
protected:
	HGE*			mHGE;
	bool			mUseSound;
	HEFFECT			mMusic;
	HCHANNEL		mMusicChanel;
};

#endif