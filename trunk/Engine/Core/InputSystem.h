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
#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include <hge.h>
#include "Definitions.h"
#include "xinput.h"

namespace gamepad
{
	enum PadKey
	{
		DPadUp			= XINPUT_GAMEPAD_DPAD_UP,
		DPadDpwn		= XINPUT_GAMEPAD_DPAD_DOWN,
		DPadLeft		= XINPUT_GAMEPAD_DPAD_LEFT,       
		DPadRIght		= XINPUT_GAMEPAD_DPAD_RIGHT,
		Start			= XINPUT_GAMEPAD_START,
		Back			= XINPUT_GAMEPAD_BACK,
		LeftThumb		= XINPUT_GAMEPAD_LEFT_THUMB,       
		RightThumb		= XINPUT_GAMEPAD_RIGHT_THUMB,      
		LeftShoulder	= XINPUT_GAMEPAD_LEFT_SHOULDER,    
		RightShoulder	= XINPUT_GAMEPAD_RIGHT_SHOULDER,   
		GamepadA		= XINPUT_GAMEPAD_A,                
		GamepadB		= XINPUT_GAMEPAD_B,                
		GamepadX		= XINPUT_GAMEPAD_X,                
		GamepadY		= XINPUT_GAMEPAD_Y
	};
};

/// @class InputEvent
/// Структура с описанием базового события
class ISILME_API InputEvent
{
public:
	enum	EventType
	{
		KeyEvent,
		MouseEvent,
		Unknown
	};
	InputEvent();
	virtual ~InputEvent();
		
	EventType	type;
	int			flags;
};

/// @class KeyEvent
/// Структура с описанием события от клавиатуры
class ISILME_API KeyEvent : public InputEvent
{
public:
	KeyEvent();
	virtual ~KeyEvent();

	int			key;
	int			chr;
};

/// @class MouseEvent
/// Структура описания события от мыши
class ISILME_API MouseEvent : public InputEvent
{
public:
	MouseEvent();
	virtual ~MouseEvent();

	int			wheel;
	int			key;
};

/// @class InputSystem
/// Абстрактная система ввода. 
/// Для обеспечения кроссплатформенности, модифицируемости 
/// игра должна пользоваться только этим интерфейсом, а не его реализацией
/// Реализация создается один раз при инициализации движка.
class ISILME_API InputSystem
{
public:
	virtual ~InputSystem();

	/// Устанавливает курсор мыши в заданную позицию
	/// @param float x координата X
	/// @param float y координата Y
	virtual void		SetMousePosition(float x, float y) = 0;

	virtual int			GetChar() = 0;
	virtual int			GetKey() = 0;
	virtual std::string GetKeyName(int key) = 0;
	virtual bool		GetKeyState(int key) = 0;
	virtual Vector2		GetMousePosition() = 0;
	virtual int			GetMouseWheel() = 0;
	virtual bool		IsKeyDown(int key) = 0;
	virtual bool		IsKeyUp(int key) = 0;
	virtual bool		IsMouseOver() = 0;
	virtual bool		GetPadState(int pad, gamepad::PadKey key) = 0;
	virtual Vector2		GetPadLeftStick(int pad) = 0;
	virtual Vector2		GetPadRightStick(int pad) = 0;
	virtual int			GetLeftTrigger(int pad) = 0;
	virtual int			GetRightTrigger(int pad) = 0;
protected:
};

/// @class HGEInputSystem
/// Подсистема ввода использующая HGE.
/// По факту, класс дублирует HGE_Input_XXX функции и 
/// реализует интерфейс InputSystem.
class ISILME_API HGEInputSystem : public InputSystem
{
public:
	HGEInputSystem(HGE* hge);
	virtual ~HGEInputSystem();

	virtual void		SetMousePosition(float x, float y);
	virtual int			GetChar();
	virtual int			GetKey();
	virtual std::string GetKeyName(int key);
	virtual bool		GetKeyState(int key);
	virtual Vector2		GetMousePosition();
	virtual int			GetMouseWheel();
	virtual bool		IsKeyDown(int key);
	virtual bool		IsKeyUp(int key);
	virtual bool		IsMouseOver();
	virtual bool		GetPadState(int pad, gamepad::PadKey key);
	virtual Vector2		GetPadLeftStick(int pad);
	virtual Vector2		GetPadRightStick(int pad);
	virtual int			GetLeftTrigger(int pad);
	virtual int			GetRightTrigger(int pad);
protected:
	HGE*	mHGE;
};

#endif