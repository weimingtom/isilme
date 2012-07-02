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
#include "IsilmePCH.h"
#include "StateManager.h"
#include "State.h"
#include "Level.h"
#include "Renderer.h"

StateManager::StateManager() :
	mRenderer(0),
	mLua(0)
{
}

StateManager::~StateManager()
{
}

void		StateManager::Pop()
{
	mStates.pop_back();
}

void		StateManager::Push(StatePtr state)
{
	mStates.push_back(state);
	state->Start();
}

StatePtr		StateManager::GetState()
{
	return mStates.back();
}

LevelPtr		StateManager::GetLevel()
{
	return mStates.back()->GetLevel();
}

bool		StateManager::Update(float elapsedTime)
{
	if (!mStates.back()->Update(elapsedTime))
		mStates.pop_back();

	return mStates.size() == 0;
}

bool		StateManager::Draw(float elapsedTime)
{
	mRenderer->BeginScene();

	// Рисуем уровень
	mRenderer->Draw(mStates.back());

	// Рисуем интерфейс
	mStates.back()->GetGUI()->Draw();

	mRenderer->EndScene();
	
	return false;
}

Renderer*	StateManager::GetRenderer()
{
	return mRenderer;
}

void		StateManager::SetRenderer(Renderer* renderer)
{
	mRenderer = renderer;
}