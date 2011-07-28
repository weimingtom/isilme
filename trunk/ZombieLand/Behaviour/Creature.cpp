#include "ZombieLand.h"
#include "ZombieLand/Behaviour/Creature.h"
#include "ZombieLand/Action/Move.h"
#include "ZombieLand/Action/Attack.h"
#include "ZombieLand/Action/UseItem.h"
#include "ZombieLand/Items/Weapon.h"
#include "ZombieLand/Item.h"

namespace behaviour
{
	Creature::Creature(CreatureDef* def) : Destroyable(def)
	{
		mMoveAction = action::MovePtr(new action::Move());
		mMoveAction->SetSpeed(3.0f);

		mMoveBack = action::MovePtr(new action::Move());
		mMoveBack->SetSpeed(-2.0f);

		mAttack = action::AttackPtr(new action::Attack());


		mEnergy = def->Energy;
		mMaxEnergy = def->MaxEnergy;
		mEnergyResoration = def->EnergyRestoration;

		mInventory = Inventory::New();
		mShotAction = action::UseItem::New(Item::Weapon, GetInventory());
		mReloadAction = action::UseItem::New(Item::Ammo, GetInventory());
		mSpellAction = action::UseItem::New(Item::Spell, GetInventory());
	}

	Creature::~Creature()
	{
	}

	ActionPtr	Creature::GetSpellAction()
	{
		return mSpellAction;
	}

	ActionPtr	Creature::GetReloadAction()
	{
		return mReloadAction;
	}

	InventoryPtr	Creature::GetInventory()
	{
		return mInventory;
	}

	void	Creature::SetMaxEnergy(float energy)
	{
		mMaxEnergy = energy;
	}

	float Creature::GetMaxEnergy()
	{
		return mMaxEnergy;
	}

	void	Creature::SetEnergy(float energy)
	{
		mEnergy = energy;
	}

	float	Creature::GetEnergy()
	{
		return mEnergy;
	}

	void	Creature::Think(float elapsedTime)
	{
		Destroyable::Think(elapsedTime);
		if (mEnergy < mMaxEnergy)
			mEnergy += mEnergyResoration * elapsedTime;
	}

	BehaviourPtr CreatureDef::Create()
	{
		return BehaviourPtr(new Creature(this));
	}

	void	CreatureDef::Parse(TiXmlElement* element)
	{
		DestroyableDef::Parse(element);
		Energy = 100.0f;
		MaxEnergy = 100.0f;
		EnergyRestoration = 2.0f;

		element->QueryFloatAttribute("Energy", &Energy);
		element->QueryFloatAttribute("MaxEnergy", &MaxEnergy);
		element->QueryFloatAttribute("EnergyRestoration", &EnergyRestoration);
	}

	action::MovePtr	Creature::GetMoveAction()
	{
		return mMoveAction;
	}

	ActionPtr	Creature::GetShotAction()
	{
		return mShotAction;
	}

	action::MovePtr	Creature::GetMoveBackAction()
	{
		return mMoveBack;
	}

	action::AttackPtr Creature::GetAttackAction()
	{
		return mAttack;
	}

	void Creature::RotateToPoint(Vector2 target)
	{
		Vector2 position = GetActor()->GetPosition();
		Vector2 d = target - position;

		float sina = d.y / d.Length();
		float cosa = d.x / d.Length();

		if (d.Length() < 0.2f)
			return;

		float a = asin(sina);

		if (sina >= 0.0f && cosa >= 0.0f)
		{
			GetActor()->SetAngle(a);
		}
		else if (sina >= 0.0f && cosa <= 0.0f)
		{
			GetActor()->SetAngle(3.14 - a);
		}
		else if (sina <= 0.0f && cosa <= 0.0f)
		{
			GetActor()->SetAngle(3.14f - a);
		}
		else 
		{
			GetActor()->SetAngle(a);
		}
	}

};