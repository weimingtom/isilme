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
#include "InputSystem.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "State.h"
#include "StateManager.h"
#include "ScriptAPI.h"

Engine* Engine::mInstance = 0;

Engine::Engine() :
	mResourceManager(0),
	mInputSystem(0),
	mLua(0)
{
	// Инициализируем Lua
	mLua = luaL_newstate();
	luaL_openlibs(mLua);
	
	// Инициализируем подсистему ввода
	SetInputSystem(new HGEInputSystem(mHGE));

	// Запоминаем себя
	mInstance = this;

	// Регистрируем ScripAPI
	ScriptAPI::RegisterEngineAPI();

	
	gcn::Image::setImageLoader(new gcn::HGEImageLoader());
}

Engine::~Engine()
{
	lua_close(mLua);
	if (mHGE)
	{
		mHGE->Release();
		mHGE = 0;
	}

	if (mResourceManager)
	{
		delete mResourceManager;
		mResourceManager = 0;
	}
}

InputSystem* Engine::GetInputSystem()
{
	return mInputSystem;
}

void	Engine::SetInputSystem(InputSystem* inputSystem)
{
	mInputSystem = inputSystem;
}

lua_State*	Engine::GetLua()
{
	return mLua;
}

void Engine::ShowLogo()
{
#ifdef _WINDOWS
	Sleep(200);
#endif
    
	mLogo = new LogoState(new hgeSprite(mResourceManager->GetTexture("../Data/Textures/Logo.png"),0,0,954, 755));
	mStateManager->Push(StatePtr(mLogo));
	mHGE->System_Start();
    
#ifdef _WINDOWS
	Sleep(200);
#endif
}

ResourceManager* Engine::GetResourceManager()
{
	return mResourceManager;
}

void	Engine::SetResourceManager(ResourceManager* resourceManager)
{
	mResourceManager = resourceManager;
}

Engine*	Engine::GetSingleton()
{
	if (mInstance)
		return mInstance;

	mInstance = new Engine();
	return mInstance;
}

SoundSystem*	Engine::GetSoundSystem()
{
	return mSoundSystem;
}

void			Engine::SetSoundSystem(SoundSystem* soundSystem)
{
	mSoundSystem = soundSystem;
}

std::string Engine::GetWorkingDirectory()
{
	/// TODO: Сделать нормальное получение текущей директории и директории ресурсов
	return "";
}

std::string Engine::GetResourceDirectory()
{
	return "../Data";
}
