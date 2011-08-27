#ifndef ZOMBIELAND_BEHAVIOUR_CREATURE_H
#define ZOMBIELAND_BEHAVIOUR_CREATURE_H

#include <Isilme.h>
#include "ZombieLand/Include/Definitions.h"
#include "Destroyable.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include <luabind/luabind.hpp>

namespace behaviour
{
	class CreatureDef : public DestroyableDef
	{
	public:
		virtual BehaviourPtr Create();

		virtual void Parse(TiXmlElement* element);

		float	Energy;
		float	MaxEnergy;
		float	EnergyRestoration;

		luabind::object OnThink;
	};

	class Creature : public Destroyable
	{
	public:
		Creature(CreatureDef* def);
		virtual ~Creature();

		action::MovePtr GetMoveAction();

		action::MovePtr GetMoveBackAction();

		/// Стрельба из активного оружия
		ActionPtr GetShotAction();

		/// Перезарядка активного оружия
		ActionPtr	GetReloadAction();

		ActionPtr	GetSpellAction();

		action::AttackPtr GetAttackAction();

		virtual void	Think(float elapsedTIme);

		void	RotateToPoint(Vector2 position);

		void	SetEnergy(float energy);

		float	GetEnergy();

		void	SetMaxEnergy(float energy);

		float	GetMaxEnergy();

		inventory::InventoryPtr	GetInventory();
	protected:
		action::MovePtr	mMoveAction;
		action::MovePtr	mMoveBack;
		ActionPtr	mShotAction;
		ActionPtr	mReloadAction;
		ActionPtr	mSpellAction;
		action::AttackPtr mAttack;
		inventory::InventoryPtr	mInventory;

		float	mEnergy;
		float	mMaxEnergy;
		float	mEnergyResoration;

		luabind::object	onThink; // onThink(me, elapsedTime)
	};

};
#endif