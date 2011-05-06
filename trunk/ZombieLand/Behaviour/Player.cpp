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

		Vector2 p = inputSystem->GetMousePosition();
		p.x = ZombieLand::GetSingleton()->GetStateManager()->GetRenderer()->PixelToMeter(p.x) + GetLevel()->GetCamera()->x;
		p.y = ZombieLand::GetSingleton()->GetStateManager()->GetRenderer()->PixelToMeter(p.y) + GetLevel()->GetCamera()->y;

		RotateToPoint(p);

		if (inputSystem->IsKeyDown(HGEK_A))
		{
			GetActor()->SetAngle(GetActor()->GetAngle() + 0.1);
		}
		else if (inputSystem->IsKeyDown(HGEK_D))
		{
			GetActor()->SetAngle(GetActor()->GetAngle() - 0.1);
		}
		else if (inputSystem->IsKeyDown(HGEK_W))
		{
			StartAction(GetMoveAction());
		}
		else if (inputSystem->IsKeyUp(HGEK_W))
		{
			GetMoveAction()->Stop();
		}
		else if (inputSystem->IsKeyDown(HGEK_S))
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
		if (inputSystem->IsKeyDown(HGEK_2))
		{
			if (!(GetWindAction()->IsActive()) && GetEnergy() >= GetWindAction()->GetCost())
				StartAction(GetWindAction());
		}
		if (inputSystem->IsKeyDown(HGEK_3))
		{
			if (!(GetHealAction()->IsActive()) && GetEnergy() >= GetHealAction()->GetCost())
				StartAction(GetHealAction());

			lua_State* state = Engine::GetSingleton()->GetLua()->GetState();
			luaL_loadstring(state, "TestStory();");
			func_index = lua_gettop(state);

			func = luabind::object(luabind::from_stack(state, func_index));
		}
		if (inputSystem->IsKeyDown(HGEK_4))
		{
			lua_State* state = Engine::GetSingleton()->GetLua()->GetState();

			//luabind::object func(luabind::from_stack(state, func_index));
			try
			{
				luabind::call_function<void>(func);
				int a = 1;
			}
			catch (std::exception e)
			{
				int b = 0;
			}
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