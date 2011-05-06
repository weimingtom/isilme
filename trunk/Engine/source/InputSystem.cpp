#include "Isilme.h"

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