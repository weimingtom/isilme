/// ****************************** Module Header ******************************
/// @file  ZombieLand.h
///	Project:      Teddy Terror 
/// Copyright (c) Ofiel.
///
/// Модуль содержит описание констант, параметров и макросов, используемых игрой
/// ***************************************************************************


#ifndef TEDDY_TERROR_H
#define TEDDY_TERROR_H

#include <Engine/Isilme.h>
#include <Engine/Inventory/Inventory.h>
#include <Engine/Inventory/Item.h>

#include "Definitions.h"


#include "Configuration.h"

#include "ScriptAPI.h"

#include "ZombieLand/Graphics/Destroyable.h"

/// @class ZombieLand
/// Игра
class ZombieLand : public HGEGame
{
public:
	ZombieLand();
	virtual ~ZombieLand();

	/// Инициализация состояний игры
	virtual void Init();

	/// Состояние "Игра"
	state::PlayPtr		playState;

	/// Возвращает конфигурацию игры
	Configuration* GetConfguration();

	/// Применяет к игре измененные настройки
	void			ApplyConfiguration();

	static ZombieLand*		GetSingleton();
private:
	/// Настройки игры
	Configuration* mConfiguration;
};
#endif