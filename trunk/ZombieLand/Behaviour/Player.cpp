#include "ZombieLand.h"
#include "ZombieLand/Behaviour/Player.h"
#include "ZombieLand/Action/Move.h"
#include "ZombieLand/Action/Wind.h"
#include "ZombieLand/Items/Weapon.h"
#include "Engine/Inventory/Item.h"
#include <LuaBind/luabind/luabind.hpp>

int pw = 0;
int ps = 0;

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
		SetAttribute("Speed", 3);
		isReloading = false;
		mCurrentWeapon = 0;
		mCurrentSpell = 0;

		inventory::ItemPtr spell = FactoryManager::GetSingleton()->CreateItem("Heal");
		GetInventory()->AddItem(spell);
		spell = FactoryManager::GetSingleton()->CreateItem("Wind");
		GetInventory()->AddItem(spell);
		spell = FactoryManager::GetSingleton()->CreateItem("Shild");
		GetInventory()->AddItem(spell);
		NextSpell();
	}

	Player::~Player()
	{
	}

	void	Player::SavePoint()
	{
		mCheckPoint = GetActor()->GetPosition();
	}

	void	Player::Respawn()
	{
		SetActive(true);
		SetHealth(GetMaxHealth());
		GetActor()->SetPosition(mCheckPoint.x, mCheckPoint.y);
		GetActor()->GetBody()->SetActive(true);
	}

	void	Player::NextWeapon()
	{
		if (GetInventory()->GetItemsCount() == 0)
			return;

		mCurrentWeapon++;
		
		if (mCurrentWeapon >= GetInventory()->GetItemsCount())
			mCurrentWeapon = 0;

		inventory::ItemPtr item = GetInventory()->GetItem(mCurrentWeapon);
		if (item->GetSlot() == inventory::Item::Weapon)
		{
			GetInventory()->Equip(item);
			pw = 0;
		}
		else
		{
			if (pw < GetInventory()->GetItemsCount() + 3)
			{
				pw++;
				NextWeapon();
			}
		}
	}

	void	Player::NextSpell()
	{
		if (GetInventory()->GetItemsCount() == 0 || ps > GetInventory()->GetItemsCount() + 2)
			return;

		mCurrentSpell++;
		
		if (mCurrentSpell >= GetInventory()->GetItemsCount())
			mCurrentSpell = 0;

		inventory::ItemPtr item = GetInventory()->GetItem(mCurrentSpell);
		if (item->GetSlot() == inventory::Item::Spell)
		{
			GetInventory()->Equip(item);
			ps = 0;
		}
		else
		{
			ps++;
			NextSpell();
		}
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
			if ((*it)->GetBehaviour()->IsActive() && GetActor()->GetDistanceTo(*it) < 4.0f && (*it) != GetActor())
			{
				float f = GetActor()->GetAngleTo(*it);
				if (abs(f - GetActor()->GetAngle()) < min)
				{
					min = abs(GetActor()->GetAngleTo(*it) - GetActor()->GetAngle());
					mTarget = *it;
				}
			}
		}

		if (mTarget != 0)
		GetActor()->SetAngle(GetActor()->GetAngleTo(mTarget));
	}

	void	Player::Think(float elapsedTime)
	{
		Creature::Think(elapsedTime);

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
			if (GetMoveAction()->IsActive())
				GetMoveAction()->Stop();
		}
		else
		{
			GetMoveAction()->SetAngle(angle);
			if (!GetMoveAction()->IsActive())
				StartAction(GetMoveAction());
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
			SwitchActivator();
		}
	}

	BehaviourPtr PlayerDef::Create()
	{
		return BehaviourPtr(new Player(this));
	}

};