//  Copyright (C) 2010-2012 Alexander Alimov
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
#include "InputSystem.h"

// InputEvent

InputEvent::InputEvent()
{
}

InputEvent::~InputEvent()
{
}

// KeyEvent

KeyEvent::KeyEvent() 
{
	type = InputEvent::KeyEvent;
}

KeyEvent::~KeyEvent()
{
}

// MouseEvent

MouseEvent::MouseEvent()
{
	type = InputEvent::MouseEvent;
}

MouseEvent::~MouseEvent()
{
}

// InputSystem

InputSystem::~InputSystem()
{
}

// HGEInputSystem
HGEInputSystem::HGEInputSystem(HGE* hge)
{
	mHGE = hge;
}

HGEInputSystem::~HGEInputSystem()
{
}

int		HGEInputSystem::GetLeftTrigger(int pad)
{
	XINPUT_STATE state;
	if (XInputGetState(pad, &state) != ERROR_SUCCESS)
		return 0;
	return state.Gamepad.bLeftTrigger;
}

int		HGEInputSystem::GetRightTrigger(int pad)
{
	XINPUT_STATE state;
	if (XInputGetState(pad, &state) != ERROR_SUCCESS)
		return 0;
	return state.Gamepad.bRightTrigger;
}

bool	HGEInputSystem::GetPadState(int pad, gamepad::PadKey key)
{
	bool value;
	XINPUT_STATE state;
	if (XInputGetState(pad, &state) != ERROR_SUCCESS)
		return false;

	value = (state.Gamepad.wButtons & key) != 0;
	return value;
}

Vector2 HGEInputSystem::GetPadLeftStick(int pad)
{
	XINPUT_STATE state;
	XInputGetState(pad, &state);
	if (XInputGetState(pad, &state) != ERROR_SUCCESS)
		return Vector2(0.0f, 0.0f);
	return Vector2(state.Gamepad.sThumbLX, state.Gamepad.sThumbLY);
}

Vector2 HGEInputSystem::GetPadRightStick(int pad)
{
	XINPUT_STATE state;
	XInputGetState(pad, &state);
	if (XInputGetState(pad, &state) != ERROR_SUCCESS)
		return Vector2(0.0f, 0.0f);
	return Vector2(state.Gamepad.sThumbRX, state.Gamepad.sThumbRY);
}

void	HGEInputSystem::SetMousePosition(float x, float y)
{
	mHGE->Input_SetMousePos(x, y);
}

Vector2	HGEInputSystem::GetMousePosition()
{
	Vector2 v;
	mHGE->Input_GetMousePos(&v.x, &v.y);

	return v;
}

int		HGEInputSystem::GetChar()
{
	return mHGE->Input_GetChar();
}

int		HGEInputSystem::GetKey()
{
	return mHGE->Input_GetKey();
}

std::string HGEInputSystem::GetKeyName(int key)
{
	return std::string(mHGE->Input_GetKeyName(key));
}

bool	HGEInputSystem::GetKeyState(int key)
{
	return mHGE->Input_GetKeyState(key);
}

int		HGEInputSystem::GetMouseWheel()
{
	return mHGE->Input_GetMouseWheel();
}

bool	HGEInputSystem::IsKeyDown(int key)
{
	return mHGE->Input_KeyDown(key);
}

bool	HGEInputSystem::IsKeyUp(int key)
{
	return mHGE->Input_KeyUp(key);
}

bool	HGEInputSystem::IsMouseOver()
{
	return mHGE->Input_IsMouseOver();
}