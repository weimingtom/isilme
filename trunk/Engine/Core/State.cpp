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
#include "State.h"
#include "Level.h"

State::State()
{
	mCamera = CameraPtr(new Camera());
	isPaused = false;
	mGUI = gcn::GuiPtr(new gcn::Gui());
	mPausePrev = true;
	isTransporate = true;
	isClosed = false;
	mLevel = LevelPtr(new Level());


	// Init GUI
	imageLoader = new gcn::HGEImageLoader();

	gcn::Image::setImageLoader(imageLoader);
	graphics = gcn::GraphicsPtr(new gcn::HGEGraphics());
	input = new gcn::HGEInput();
    
	mGUI->SetGraphics(graphics);
	mGUI->SetInput(input);
}

void	State::SetLevel(LevelPtr level)
{
	mLevel = level;
}

bool	State::IsPaused()
{
	return isPaused;
}

void	State::SetPaused(bool pause)
{
	isPaused = pause;
}

void	State::SetGUI(gcn::GuiPtr gui)
{
	mGUI = gui;
}

gcn::GuiPtr State::GetGUI()
{
	return mGUI;
}

void State::Start()
{
	isClosed = false;
	OnStart();
}
void State::Close()
{
	isClosed = true;
}

bool State::Update(float elapsedTime)
{
	if (mGUI->GetTop())
		mGUI->Logic();

	if (!isPaused)
	{
		mLevel->Update(elapsedTime);
	}

	if (mCamera)
		mCamera->Update(elapsedTime);

	OnUpdate(elapsedTime);
	return !isClosed;
}
bool State::Draw(float elapsedTime)
{
	
	return false;
}

State::~State() 
{
}

bool State::IsTransporate()
{
	return isTransporate;
}

void State::SetTransporate(bool value)
{
	isTransporate = value;
}
bool State::GetPausePrev()
{
	return mPausePrev;
}
void State::SetPausePrev(bool value)
{
	mPausePrev = value;
}
void State::OnUpdate(float elapsedTime)
{
}
void State::OnStart() 
{
	isClosed = false;
}
void State::OnResume() 
{
}
void State::OnDraw()
{
}
LevelPtr State::GetLevel()
{
	return mLevel;
}

CameraPtr State::GetCamera()
{
	return mCamera;
}

void State::SetCamera(CameraPtr camera)
{
	mCamera = camera;
}