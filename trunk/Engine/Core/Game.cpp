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
#include "Engine/Story/Story.h"
#include "Game.h"
#include "StateManager.h"
#include "InputSystem.h"
#include "SoundSystem.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "ScheduleManager.h"

// Game

Game::Game() :
	mScheduler(new ScheduleManager())
{
	mStory = story::StoryPtr(new story::Story());
	mStateManager = new StateManager();
	Game::mInstance = this;
	mUsePhisics = true;
}

Game::~Game()
{
	delete mStateManager;
}

Game* Game::GetSingleton()
{
	return mInstance;
}

StateManager*	Game::GetStateManager()
{
	return mStateManager;
}

story::StoryPtr	Game::GetStory()
{
	return mStory;
}

bool Game::GetUsePhisics()
{
	return mUsePhisics;
}

void Game::SetUsePhisics( bool value )
{
	mUsePhisics = value;
}

ScheduleManagerPtr Game::GetScheduler() const
{
	return mScheduler;
}

// HGEGame

Game*	Game::mInstance = 0;

HGEGame::HGEGame(HGE* hge)
{
	mHGE = hge;
	mHGE->System_SetState(HGE_FRAMEFUNC, FrameFunction);	// Функция во время кадра (Не знаю как перевести)
	mHGE->System_SetState(HGE_RENDERFUNC, RenderFunction);	// Функция рисования сцены

	
	InitEngine();
}
HGEGame::HGEGame()
{
	SetupHGE();
	InitEngine();
}

HGEGame::~HGEGame()
{
}

void	HGEGame::InitEngine()
{
	SetupGUI();

	// Инициализация компонентов движка
	Engine::GetSingleton()->SetInputSystem(new HGEInputSystem(mHGE));
	Engine::GetSingleton()->SetResourceManager(new HGEResourceManager(mHGE));
	Engine::GetSingleton()->SetSoundSystem(new HGESoundSystem(mHGE));
	Engine::GetSingleton()->mHGE = mHGE;

	// Инициализация менеджера состояний
	GetStateManager()->SetRenderer(new HGERenderer(mHGE));
}

void	HGEGame::SetupGUI()
{
}

void	HGEGame::SetupHGE()
{
	// Создаем HGE
	if (!(mHGE = hgeCreate(HGE_VERSION)))
	{
        LOG_E("HGE creation faild");
		return;
	}

	// Читаем прараметры
	mHGE->System_SetState(HGE_INIFILE, "HGE.ini");

	bool	windowed = mHGE->Ini_GetInt("VIDEO", "FullScreen", 1) == 0;
	char* res = mHGE->Ini_GetString("VIDEO", "Resolution", "800x600");
	int mWidth = 800;
	int mHeight = 600;
	sscanf(res, "%dx%d", &mWidth, &mHeight);
	int		color = mHGE->Ini_GetInt("VIDEO", "Color", 32);
	char*	windowTitle = mHGE->Ini_GetString("WINDOW", "Title", "");

	// Проводим настройку HGE
	mHGE->System_SetState(HGE_LOGFILE, "HGE.log");			// Лог
	mHGE->System_SetState(HGE_FRAMEFUNC, FrameFunction);	// Функция во время кадра (Не знаю как перевести)
	mHGE->System_SetState(HGE_RENDERFUNC, RenderFunction);	// Функция рисования сцены
	mHGE->System_SetState(HGE_TITLE, windowTitle);			// Заголовок окна
	mHGE->System_SetState(HGE_WINDOWED, windowed);			// Оконный режим
	mHGE->System_SetState(HGE_SCREENWIDTH, mWidth);			// Ширина окна
	mHGE->System_SetState(HGE_SCREENHEIGHT, mHeight);		// Высота окна
	mHGE->System_SetState(HGE_SCREENBPP, color);			// Глубина цвета
	mHGE->System_SetState(HGE_ZBUFFER, true);				// Использовать Z-буфер
	mHGE->System_SetState(HGE_HIDEMOUSE, false);			// Не прятать мышь

	// Инициализируем HGE
	if(!mHGE->System_Initiate())
	{
		mHGE->System_Shutdown();
		mHGE->Release();
		mHGE = NULL;
        LOG_E("HGE initialisation failed");
		return;
	}

}

void	HGEGame::Start()
{
	mHGE->System_Start();
}

bool	HGEGame::FrameFunction()
{
	HGE* hge = ((HGEGame*)mInstance)->mHGE;
	float elapsedTime = hge->Timer_GetDelta();
	bool result = mInstance->GetStateManager()->Update(elapsedTime);
	mInstance->GetScheduler()->Update(elapsedTime);
	return result;
}

bool	HGEGame::RenderFunction()
{
	HGE* hge = ((HGEGame*)mInstance)->mHGE;
	HGEGame::mInstance->GetStateManager()->Draw(hge->Timer_GetDelta());
	return true;
}
