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
class IsilmeExport InputEvent
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
class IsilmeExport KeyEvent : public InputEvent
{
public:
	KeyEvent();
	virtual ~KeyEvent();

	int			key;
	int			chr;
};

/// @class MouseEvent
/// Структура описания события от мыши
class IsilmeExport MouseEvent : public InputEvent
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
class IsilmeExport InputSystem
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
class IsilmeExport HGEInputSystem : public InputSystem
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