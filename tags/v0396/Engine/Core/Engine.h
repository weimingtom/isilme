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
#ifndef ENGINE_H
#define ENGINE_H

#include "Definitions.h"
#include "LogoState.h"

/// @class Engine
/// Игровой движок, агрегирует в себе средства управления звуком, сценой, ресурсами.
/// В программе может существовать только один экзэмпляр игрового движка.
/// Все подсистемы необходимо инициализировать, либо использовать уже существующую реализацию
/// игры и компонентов, например HGEGame
class ISILME_API Engine
{
public:
	/// Возвращает состояние Lua
	/// @return Lua* 
	lua_State*					GetLua();

	/// Демонстрирует логотип
	/// @depricated
	void					ShowLogo();

	/// Возвращает менеджер ресурсов
	/// @return ResourceManager*
	ResourceManager*		GetResourceManager();
	
	/// Устанавливает менеджер ресурсов
	/// @param resourceManager ResourceManager*
	void					SetResourceManager(ResourceManager* resourceManager);

	/// @depricated 
	void					Start(State* startState);
	
	/// Возвращает единственный экзэмпляр движка
	/// @return Engine*
	static Engine*			GetSingleton();

	/// Возвращает подсистему ввода
	/// @return InputSystem*
	InputSystem*			GetInputSystem();

	/// Установить подсистему ввода
	/// Если ранее была установленна какая-либо иная подсистема ввода,
	/// она будет уничтожена.
	/// При уничтожении экзэмпляра движка, подсистема ввода также уничтожается
	/// @param inputSystem InputSystem* подсистема ввода
	void					SetInputSystem(InputSystem* inputSystem);

	/// @return SoundSystem*
	SoundSystem*			GetSoundSystem();

	/// Установить звуковую подсистему
	/// Если ранее была установленна какая-либо иная звуковая подсистема,
	/// она будет уничтожена.
	/// При уничтожении экзэмпляра движка, звуковая подсистема также уничтожается
	/// @param soundSystem SoundSystem* звуковая подсистема
	void					SetSoundSystem(SoundSystem* soundSystem);

	/// Возвращает рабочую директорию
	std::string				GetWorkingDirectory();

	/// Возвращает директорию ресурсов
	std::string				GetResourceDirectory();

	HGE* mHGE;
private:
	Engine();
	virtual ~Engine();

	/// @depricated
	State*					mLogo;

	ResourceManager*		mResourceManager;
	StateManager*			mStateManager;
	InputSystem*			mInputSystem;
	SoundSystem*			mSoundSystem;
	lua_State*					mLua;

	// Экземпляр движка
	static Engine* mInstance;
	hgeSprite* mOfielLogo;

};

#endif
