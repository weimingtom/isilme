#include "ZombieLand.h"
#include "ZombieLand/Behaviour/Player.h"
#include "ZombieLand/Action/Move.h"
#include "ZombieLand/Action/Wind.h"
#include "ZombieLand/Items/Weapon.h"
#include "ZombieLand/Item.h"
#include <LuaBind/luabind/luabind.hpp>

namespace behaviour
{
	int func_index = 0;
	luabind::object func;

	Player::Player(PlayerDef* def) : Creature(def)
	{
		//GetShotAction()->SetSound("../Data/Sounds/Weapons/Gun.wav");
		//SetHealth(25);
		GetMoveAction()->SetSound("../Data/Sounds/Walk.wav");
		GetMoveBackAction()->SetSound("../Data/Sounds/Walk.wav");

		isReloading = false;
		mCurrentWeapon = 0;
		mCurrentSpell = 0;

		ItemPtr spell = items::CreateItem("HealSpell");
		GetInventory()->AddItem(spell);
		spell = items::CreateItem("WindSpell");
		GetInventory()->AddItem(spell);
		spell = items::CreateItem("ShildSpell");
		GetInventory()->AddItem(spell);
		NextSpell();
	}

	Player::~Player()
	{
	}

	void	Player::NextWeapon()
	{
		if (GetInventory()->GetItemsCount() == 0)
			return;

		mCurrentWeapon++;
		
		if (mCurrentWeapon >= GetInventory()->GetItemsCount())
			mCurrentWeapon = 0;

		ItemPtr item = GetInventory()->GetItem(mCurrentWeapon);
		if (item->GetSlot() == Item::Weapon)
			GetInventory()->Equip(item);
		else
			NextWeapon();
	}

	void	Player::NextSpell()
	{
		if (GetInventory()->GetItemsCount() == 0)
			return;

		mCurrentSpell++;
		
		if (mCurrentSpell >= GetInventory()->GetItemsCount())
			mCurrentSpell = 0;

		ItemPtr item = GetInventory()->GetItem(mCurrentSpell);
		if (item->GetSlot() == Item::Spell)
			GetInventory()->Equip(item);
		else
			NextSpell();
	}

	void	Player::SwitchActivator()
	{
		ActivatorPtr a = Activator::GetActivatorFor(GetActor());
		if (a == 0)
			return;
		a->UseBy(boost::shared_dynamic_cast<Creature>(GetActor()->GetBehaviour()));
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

		// Прицеливание
		if (inputSystem->GetPadState(0, gamepad::RightShoulder) || inputSystem->GetKeyState(HGEK_SPACE))
			SetTarget();
		else
			ClearTarget();

		// Активатор
		if (inputSystem->IsKeyDown(HGEK_K) || inputSystem->GetPadState(0, gamepad::GamepadA))
		{
			SwitchActivator();
		}
	}

	BehaviourPtr PlayerDef::Create()
	{
		return BehaviourPtr(new Player(this));
	}

};