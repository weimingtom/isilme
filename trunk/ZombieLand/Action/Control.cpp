#include "ZombieLand.h"
#include "Control.h"
#include "ZombieLand/Behaviour/Creature.h"
#include "ZombieLand/Action/Move.h"
#include "ZombieLand/Action/Attack.h"


namespace action
{
Control::Control()
{
	SetDuration(Action::InfiniteDuration);
}

Control::~Control()
{
}

bool Control::DoneCondition()
{
	return false;
}

void Control::OnStart()
{
	mCreature = GetEntity()->As<behaviour::Creature>();
	if (!mCreature)
	{
		Stop();
	}
}

void Control::OnDone()
{
	mCreature.reset();
}

void Control::OnUpdate(float elapsedTime)
{
	InputSystem* inputSystem = Engine::GetSingleton()->GetInputSystem();

	// поворот за мышью
	Vector2 mouse = inputSystem->GetMousePosition();
	mouse *= 1.0f / 64.0f;
	mouse.x += GetLevel()->GetCamera()->x;
	mouse.y += GetLevel()->GetCamera()->y;

	float angleToMouse = GetActor()->GetAngleTo(mouse);
	GetActor()->SetAngle(angleToMouse);

	// Перемещение
	Vector2 direction(0.0f, 0.0f);
	float angle = 0.0f;
	bool isMove = false;
	if (inputSystem->GetKeyState(HGEK_D))
	{
		direction.x += 1.0f;
	}
	if (inputSystem->GetKeyState(HGEK_A))
	{
		direction.x -= 1.0f;
	}
	if (inputSystem->GetKeyState(HGEK_W))
	{
		direction.y -= 1.0f;
	}		
	if (inputSystem->GetKeyState(HGEK_S))
	{
		direction.y += 1.0f;
	}

	angle = GetActor()->GetAngleTo(GetActor()->GetPosition() + direction);

	if (direction.LengthSquared() < 0.5f)
	{
		if (mCreature->GetMoveAction()->IsActive())
			mCreature->GetMoveAction()->Stop();
	}
	else
	{
		mCreature->GetMoveAction()->SetAngle(angle);
		if (!mCreature->GetMoveAction()->IsActive())
			mCreature->StartAction(mCreature->GetMoveAction());
	}


	//Vector2 p = inputSystem->GetMousePosition();
	//p.x = ZombieLand::GetSingleton()->GetStateManager()->GetRenderer()->PixelToMeter(p.x) + GetLevel()->GetCamera()->x;
	//p.y = ZombieLand::GetSingleton()->GetStateManager()->GetRenderer()->PixelToMeter(p.y) + GetLevel()->GetCamera()->y;
	//RotateToPoint(p);
	// Перемещение
	//Vector2 p = inputSystem->GetPadLeftStick(0);
	//p *= 1.0f / MAXINT16;
	//p.y = -p.y;


	//if (p.LengthSquared() < 0.1f)
	//{
	//	if (inputSystem->GetKeyState(HGEK_D))
	//		p.x = 1.0f;
	//	if (inputSystem->GetKeyState(HGEK_A))
	//		p.x = -1.0f;
	//	if (inputSystem->GetKeyState(HGEK_S))
	//		p.y = 1.0f;
	//	if (inputSystem->GetKeyState(HGEK_W))
	//		p.y = -1.0f;
	//}
	//if (p.LengthSquared() > 0.1f)
	//{
	//	//p.Normalize();
	//	p += GetActor()->GetPosition();
	//	RotateToPoint(p);
	//	if (!GetMoveAction()->IsActive() && p.LengthSquared() > 0.5f)
	//		StartAction(GetMoveAction());
	//}
	//else
	//	if (GetMoveAction()->IsActive())
	//	GetMoveAction()->Stop();

	//// Прицеливание
	//if (inputSystem->GetPadState(0, gamepad::RightShoulder) || inputSystem->GetKeyState(HGEK_SPACE))
	//	SetTarget();
	//else
	//	ClearTarget();

	// Активатор
	if (inputSystem->IsKeyDown(HGEK_K) || inputSystem->GetPadState(0, gamepad::GamepadA))
	{
		mCreature->SwitchActivator();
	}
}

void Control::OnForceStop()
{
	OnDone();
}
};