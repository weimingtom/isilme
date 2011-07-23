#include "ZombieLand.h"
#include "ZombieLand/Behaviour/Player.h"
#include "ZombieLand/Action/Shot.h"
#include "ZombieLand/Action/Move.h"
#include "ZombieLand/Action/Wind.h"
#include <LuaBind/luabind/luabind.hpp>

namespace behaviour
{
	int func_index = 0;
	luabind::object func;

	Player::Player(PlayerDef* def) : Creature(def)
	{
		GetShotAction()->SetSound("../Data/Sounds/Weapons/Gun.wav");
		//SetHealth(25);
		GetMoveAction()->SetSound("../Data/Sounds/Walk.wav");
		GetMoveBackAction()->SetSound("../Data/Sounds/Walk.wav");

		mHealAction = action::HealPtr(new action::Heal());
		mWindAction = action::WindPtr(new action::Wind());
		mShildAction = action::ShildPtr(new action::Shild());

	}

	Player::~Player()
	{
	}

	void	Player::ClearTarget()
	{
		mTarget.reset();
	}

	void	Player::SetTarget()
	{
		if (mTarget != 0)
		{
			if (mTarget->GetBehaviour()->IsActive())
			return;
		}

		float min = 1000;
		LayerPtr layer = GetActor()->GetLevel()->GetLayer("Zombies");
		for (EntityList::iterator it = layer->GetObjects()->begin(); it != layer->GetObjects()->end(); ++it)
		{
			if (abs(GetActor()->GetAngleTo(*it) - GetActor()->GetAngle()) < min && (*it)->GetBehaviour()->IsActive() && GetActor()->GetDistanceTo(*it) < 4.0f)
			{
				min = abs(GetActor()->GetAngleTo(*it) - GetActor()->GetAngle());
				mTarget = *it;
			}
		}

		if (mTarget != 0)
		GetActor()->SetAngle(GetActor()->GetAngleTo(mTarget));
	}

	action::ShildPtr Player::GetShildAction()
	{
		return mShildAction;
	}

	action::WindPtr Player::GetWindAction()
	{
		return mWindAction;
	}

	action::HealPtr Player::GetHealAction()
	{
		return mHealAction;
	}

	void	Player::Think(float elapsedTime)
	{
		Creature::Think(elapsedTime);

		InputSystem* inputSystem = Engine::GetSingleton()->GetInputSystem();

		//Vector2 p = inputSystem->GetMousePosition();
		//p.x = ZombieLand::GetSingleton()->GetStateManager()->GetRenderer()->PixelToMeter(p.x) + GetLevel()->GetCamera()->x;
		//p.y = ZombieLand::GetSingleton()->GetStateManager()->GetRenderer()->PixelToMeter(p.y) + GetLevel()->GetCamera()->y;
		//RotateToPoint(p);
		// Перемещение
		Vector2 p = inputSystem->GetPadLeftStick(0);
		p *= 1.0f / MAXINT16;
		p.y = -p.y;
		if (p.LengthSquared() < 0.1f)
		{
			if (inputSystem->GetKeyState(HGEK_D))
				p.x = 1.0f;
			if (inputSystem->GetKeyState(HGEK_A))
				p.x = -1.0f;
			if (inputSystem->GetKeyState(HGEK_S))
				p.y = 1.0f;
			if (inputSystem->GetKeyState(HGEK_W))
				p.y = -1.0f;
		}
		if (p.LengthSquared() > 0.1f)
		{
			//p.Normalize();
			p += GetActor()->GetPosition();
			RotateToPoint(p);
			if (!GetMoveAction()->IsActive() && p.LengthSquared() > 0.5f)
				StartAction(GetMoveAction());
		}
		else
			if (GetMoveAction()->IsActive())
			GetMoveAction()->Stop();

		// Стрельба
		if (inputSystem->GetPadState(0, gamepad::GamepadX) && !GetShotAction()->IsActive())
		{
			StartAction(GetShotAction());
		}

		// Прицеливание
		if (inputSystem->GetPadState(0, gamepad::RightShoulder) || inputSystem->GetKeyState(HGEK_SPACE))
			SetTarget();
		else
			ClearTarget();

		if (inputSystem->IsKeyDown(HGEK_S))
		{
			StartAction(GetMoveBackAction());
		}
		else if (inputSystem->IsKeyUp(HGEK_S))
		{
			GetMoveBackAction()->Stop();
		}
		if (inputSystem->IsKeyDown(HGEK_1))
		{
			if (!(GetShildAction()->IsActive()))
				StartAction(GetShildAction());
			else
				GetShildAction()->Stop();
		}
		if (inputSystem->IsKeyDown(HGEK_2) || inputSystem->GetPadState(0, gamepad::GamepadB))
		{
			if (!(GetWindAction()->IsActive()) && GetEnergy() >= GetWindAction()->GetCost())
				StartAction(GetWindAction());
		}
		if (inputSystem->IsKeyDown(HGEK_3))
		{
			if (!(GetHealAction()->IsActive()) && GetEnergy() >= GetHealAction()->GetCost())
				StartAction(GetHealAction());

			//lua_State* state = Engine::GetSingleton()->GetLua()->GetState();
			//luaL_loadstring(state, "TestStory();");
			//func_index = lua_gettop(state);

			//func = luabind::object(luabind::from_stack(state, func_index));
		}
		if (inputSystem->IsKeyDown(HGEK_4))
		{
			lua_State* state = Engine::GetSingleton()->GetLua()->GetState();

			//luabind::object func(luabind::from_stack(state, func_index));
			//try
			//{
			//	luabind::call_function<void>(func);
			//	int a = 1;
			//}
			//catch (std::exception e)
			//{
			//	int b = 0;
			//}
			//lua_pushvalue(state, func_index);
			//lua_pcall(state, 0, 0, 0);
			//luaL_dostring(Engine::GetSingleton()->GetLua()->GetState(), "TestEngineAPI();");
		}
	}

	BehaviourPtr PlayerDef::Create()
	{
		return BehaviourPtr(new Player(this));
	}

};